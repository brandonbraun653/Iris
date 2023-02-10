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
#include <etl/delegate.h>

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
     * @brief Returns the main thread for the session layer
     * @note This thread will need to be started manually
     *
     * @return etl::delegate<void(void)>
     */
    etl::delegate<void( void )> mainThread();

    void open();

    void close();

    /**
     * @brief Gets the runtime metrics for the session layer
     *
     * @return const MgrStats&
     */
    const MgrStats &stats() const;

  private:
    /**
     * @brief Main thread for the session layer
     */
    void mainThreadImpl();

    MgrCfg     mCfg;
    MgrStats   mStats;
    SocketList mSockets;
  };
}    // namespace Iris::Session

#endif /* !IRIS_SESSION_MANAGER_HPP */
