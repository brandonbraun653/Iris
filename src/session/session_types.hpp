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
#include "iris_session_prj.hpp"
#include <cstdint>
#include <Iris/src/physical/physical_types.hpp>
#include <etl/forward_list.h>

/*-----------------------------------------------------------------------------
Literal Constants
-----------------------------------------------------------------------------*/
#ifndef IRIS_SESSION_MAX_CONNECTIONS
#define IRIS_SESSION_MAX_CONNECTIONS ( 4 )
#endif

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class Socket;
  class SessionManager;

  /*---------------------------------------------------------------------------
  Aliases
  ---------------------------------------------------------------------------*/
  using SocketList     = etl::iforward_list<Socket>;
  using SocketPool     = etl::ipool;
  using DfltSocketPool = etl::pool<Socket, IRIS_SESSION_MAX_CONNECTIONS>;
  using SocketPort     = uint16_t;

  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
  /**
   * @brief Resources to run a single socket
   */
  struct SockCfg
  {
    SocketPort             listenOn;  /**< Which port to listen on */
    Physical::FramePool    framePool; /**< Frame pool to use for this socket */
    Transport::PacketQueue txQueue;   /**< Queue for packet transmission */
    Transport::PacketQueue rxQueue;   /**< Queue for packet reception */
  };

  struct SockStats
  {
    uint32_t txPackets; /**< Number of packets transmitted */
    uint32_t rxPackets; /**< Number of packets received */
  };

  /**
   * @brief Resources for the session manager network stack
   */
  struct MgrCfg
  {
    Physical::NetifAPI netif;      /**< Network interface driver */
    SocketPool         socketPool; /**< Socket pool to use for this manager */
  };

}    // namespace Iris::Session

#endif /* !IRIS_SESSION_TYPES_HPP */
