/******************************************************************************
 *  File Name:
 *    transport_types.hpp
 *
 *  Description:
 *    Transport Layer Types
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_TRANSPORT_TYPES_HPP
#define IRIS_TRANSPORT_TYPES_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdint>
#include <Iris/src/physical/physical_types.hpp>
#include <etl/priority_queue.h>
#include "iris_physical_prj.hpp"

/*-----------------------------------------------------------------------------
Literal Constants
-----------------------------------------------------------------------------*/
#ifndef IRIS_TRANSPORT_TX_PACKET_QUEUE_SIZE
#define IRIS_TRANSPORT_TX_PACKET_QUEUE_SIZE ( 32 )
#endif

#ifndef IRIS_TRANSPORT_RX_PACKET_QUEUE_SIZE
#define IRIS_TRANSPORT_RX_PACKET_QUEUE_SIZE ( 32 )
#endif

namespace Iris::Transport
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class Packet;

  /*---------------------------------------------------------------------------
  Aliases
  ---------------------------------------------------------------------------*/
  using DfltTXQueue = etl::priority_queue<Packet, IRIS_TRANSPORT_TX_PACKET_QUEUE_SIZE>;
  using DfltRXQueue = etl::priority_queue<Packet, IRIS_TRANSPORT_RX_PACKET_QUEUE_SIZE>;
  using PacketQueue = etl::ipriority_queue<Packet, etl::ivector<Packet>>;

  /**
   * @brief Bitfield representing a transfer state of a frame
   * @note One bit per-frame
   *
   * The meaning of these bits differ depending on the QOS level of the
   * associated packet. Generally though, if a bit is set, then that packet
   * has achieved the desired QOS level.
   */
  using QOSStatus = uint32_t;

  /*---------------------------------------------------------------------------
  Enumerations
  ---------------------------------------------------------------------------*/
  /**
   * @brief Quality of Service levels
   *
   * Signifies the level of reliability that a packet should have
   */
  enum class QOS : uint8_t
  {
    QOS_LEVEL_0, /**< At-Most-Once service */
    QOS_LEVEL_1, /**< At-Least-Once service */
    QOS_LEVEL_2, /**< Exactly-Once service */
    QOS_COUNT
  };

  /**
   * @brief Priority levels of a packet
   */
  enum class Priority : uint8_t
  {
    CRITICAL,
    HIGH,
    MEDIUM,
    LOW,
    PRIORITY_COUNT
  };

  // Alias priority packet queue
}    // namespace Iris::Transport

#endif /* !IRIS_TRANSPORT_TYPES_HPP */
