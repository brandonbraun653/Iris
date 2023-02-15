/******************************************************************************
 *  File Name:
 *    session_mngr.hpp
 *
 *  Description:
 *    Manager for the session layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_SESSION_MANAGER_HPP
#define IRIS_SESSION_MANAGER_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/src/session/session_types.hpp>
#include <Iris/src/session/session_sock.hpp>
#include <Iris/src/osal.hpp>

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class SessionManager
  {
  public:
    SessionManager();
    ~SessionManager();

    /**
     * @brief Initializes the session layer
     *
     * @param cfg  Configuration parameters for the session layer
     * @return Errno_t
     */
    Errno_t open( MgrCfg &cfg );

    /**
     * @brief Shuts down the session layer and all connections
     * @return void
     */
    void close();

    /**
     * @brief Processes all sockets in the session layer to pipe data around
     * @note This function should be called periodically
     */
    void process();

    /**
     * @brief Creates a new socket and adds it to the session layer for management
     *
     * @param cfg   Configuration parameters for the socket
     * @return Socket*
     */
    Socket *createSocket( const SockCfg &cfg );

    /**
     * @brief Destroys a socket and removes it from the manager
     *
     * @param socket  Socket to destroy
     * @return void
     */
    void destroySocket( Socket *socket );

    /**
     * @brief Gets the runtime metrics for the session layer
     *
     * @return const MgrStats&
     */
    const MgrStats &stats() const;

  private:
    MgrCfg                  mCfg;          /**< Configuration data for the session */
    MgrStats                mStats;        /**< Runtime stats of all managed connections */
    OSAL::MutexHandle_t     mMutex;        /**< Class lock */
    OSAL::SemaphoreHandle_t mErrorSmphr;   /**< Error notification semaphore */
    OSAL::SemaphoreHandle_t mTxReadySmphr; /**< Tx ready notification semaphore */
    OSAL::SemaphoreHandle_t mRxReadySmphr; /**< Rx ready notification semaphore */

    Physical::NotifyAPI asNotifyAPI();
    void notify_tx_ready( const SocketPort port );
    void notify_rx_ready( const SocketPort port, const size_t count );
    void notify_error( const SocketPort port, const Errno_t error );
  };
}    // namespace Iris::Session

#endif /* !IRIS_SESSION_MANAGER_HPP */
