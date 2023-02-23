/******************************************************************************
 *  File Name:
 *    session_mngr.cpp
 *
 *  Description:
 *    Session manager implementation
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/session>
#include <Iris/transport>
#include <Iris/physical>
#include <Iris/src/osal.hpp>

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  SessionManager::SessionManager()
  {
  }


  SessionManager::~SessionManager()
  {
  }


  Errno_t SessionManager::open( MgrCfg &cfg )
  {
    /*-------------------------------------------------------------------------
    Validate the configuration parameters
    -------------------------------------------------------------------------*/
    if ( !cfg.netif.open || !cfg.netif.close || !cfg.netif.get || !cfg.netif.put || !cfg.netif.process )
    {
      return -1;
    }

    /*-------------------------------------------------------------------------
    Create the semaphores and mutexes
    -------------------------------------------------------------------------*/
    mTxReadySmphr = OSAL::createSemaphore();
    mRxReadySmphr = OSAL::createSemaphore();
    mErrorSmphr   = OSAL::createSemaphore();
    mMutex        = OSAL::createMutex();

    if( !mTxReadySmphr || !mRxReadySmphr || !mErrorSmphr || !mMutex )
    {
      return -1;
    }

    /*-------------------------------------------------------------------------
    Accept the configuration and initialize memory pools
    -------------------------------------------------------------------------*/
    mCfg = cfg;
    mCfg.socketList->clear();
    mCfg.socketPool->release_all();

    /*-------------------------------------------------------------------------
    Open the physical layer and bind the notifier callbacks
    -------------------------------------------------------------------------*/
    return mCfg.netif.open( asNotifyAPI() );
  }


  void SessionManager::close()
  {
    /*-------------------------------------------------------------------------
    Close any open sockets
    -------------------------------------------------------------------------*/
    OSAL::lockMutex( mMutex, OSAL::BLOCK );
    for( auto &socket : *mCfg.socketList )
    {
      socket->close();
      mCfg.socketList->remove( socket );
      mCfg.socketPool->release( socket );
    }
    OSAL::unlockMutex( mMutex );

    /*-------------------------------------------------------------------------
    Destroy the semaphores and mutexes
    -------------------------------------------------------------------------*/
    OSAL::deleteSemaphore( mTxReadySmphr );
    OSAL::deleteSemaphore( mRxReadySmphr );
    OSAL::deleteSemaphore( mErrorSmphr );
    OSAL::deleteMutex( mMutex );
  }


  void SessionManager::process()
  {
  }


  Errno_t SessionManager::createSocket( const SockCfg &cfg )
  {
    /*-------------------------------------------------------------------------
    Validate input arguments
    -------------------------------------------------------------------------*/
    if( !cfg.framePool || !cfg.rxQueue || !cfg.txQueue )
    {
      return -1;
    }

    /*-------------------------------------------------------------------------
    Ensure there is enough room
    -------------------------------------------------------------------------*/
    OSAL::lockMutex( mMutex, OSAL::BLOCK );
    if ( mCfg.socketPool->full() || mCfg.socketList->full() )
    {
      OSAL::unlockMutex( mMutex );
      return -1;
    }

    /*-------------------------------------------------------------------------
    Instantiate the socket from the allocator pool
    -------------------------------------------------------------------------*/
    Socket * newSocket = mCfg.socketPool->allocate<Socket>();
    assert( newSocket );
    mCfg.socketList->push_front( newSocket );
    OSAL::unlockMutex( mMutex );

    return newSocket->open( cfg );
  }


  void SessionManager::destroySocket( Socket *socket )
  {
    assert( socket );

    OSAL::lockMutex( mMutex, OSAL::BLOCK );
    mCfg.socketList->remove( socket );
    mCfg.socketPool->release( socket );
    OSAL::unlockMutex( mMutex );
  }


  Socket *SessionManager::getSocket( const SocketPort port )
  {
    OSAL::lockMutex( mMutex, OSAL::BLOCK );
    for( const auto &socket : *mCfg.socketList )
    {
      if( socket->port() == port )
      {
        OSAL::unlockMutex( mMutex );
        return socket;
      }
    }

    OSAL::unlockMutex( mMutex );
    return nullptr;
  }


  void SessionManager::notify_tx_ready( const SocketPort port )
  {
  }


  void SessionManager::notify_rx_ready( const SocketPort port, const size_t num_frames )
  {
  }


  void SessionManager::notify_error( const SocketPort port, const Errno_t error )
  {
  }


  Physical::NotifyAPI SessionManager::asNotifyAPI()
  {
    auto d_tx_ready = etl::delegate<void( SocketPort )>::create<SessionManager, &SessionManager::notify_tx_ready>( *this );
    auto d_rx_ready =
        etl::delegate<void( SocketPort, size_t )>::create<SessionManager, &SessionManager::notify_rx_ready>( *this );
    auto d_error = etl::delegate<void( SocketPort, Errno_t )>::create<SessionManager, &SessionManager::notify_error>( *this );

    return { .onTXReady = d_tx_ready, .onRXReady = d_rx_ready, .onError = d_error };
  }
}    // namespace Iris::Session
