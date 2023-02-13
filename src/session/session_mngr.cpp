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


  void SessionManager::open( MgrCfg &cfg )
  {
  }


  void SessionManager::close()
  {
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

}  // namespace Iris::Session
