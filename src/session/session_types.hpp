/******************************************************************************
 *  File Name:
 *    session_types.hpp
 *
 *  Description:
 *    Types for the session layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_SESSION_TYPES_HPP
#define IRIS_SESSION_TYPES_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdint>
#include <Iris/src/physical/physical_types.hpp>

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  struct SockCfg
  {
    uint16_t      port;  /**< Which port to listen as */
    Phy::NetifAPI netif; /**< Network interface driver */
  };


  struct SockConn
  {
    uint16_t port;

  };

}  // namespace Iris::Session

#endif  /* !IRIS_SESSION_TYPES_HPP */
