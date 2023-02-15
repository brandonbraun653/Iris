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
    Create the semaphores and mutexes
    -------------------------------------------------------------------------*/
    mTxReadySmphr = OSAL::createSemaphore( 1, 0 );
    mRxReadySmphr = OSAL::createSemaphore( 1, 0 );
    mErrorSmphr   = OSAL::createSemaphore( 1, 0 );
    mMutex        = OSAL::createMutex();

    if( !mTxReadySmphr || !mRxReadySmphr || !mErrorSmphr || !mMutex )
    {
      return -1;
    }

    /*-------------------------------------------------------------------------
    Validate the configuration parameters
    -------------------------------------------------------------------------*/
    if ( !cfg.netif.open || !cfg.netif.close || !cfg.netif.get || !cfg.netif.put || !cfg.netif.process )
    {
      return -1;
    }

    cfg.socketList->clear();
    cfg.socketPool->release_all();

    /*-------------------------------------------------------------------------
    Open the physical layer and bind the notifier callbacks
    -------------------------------------------------------------------------*/
    return cfg.netif.open( asNotifyAPI() );
  }


  void SessionManager::close()
  {
    OSAL::deleteSemaphore( mTxReadySmphr );
    OSAL::deleteSemaphore( mRxReadySmphr );
    OSAL::deleteSemaphore( mErrorSmphr );
    OSAL::deleteMutex( mMutex );
  }


  void SessionManager::process()
  {
  }


  Socket *SessionManager::createSocket( const SockCfg &cfg )
  {
    return nullptr;
  }


  void SessionManager::destroySocket( Socket *socket )
  {
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
