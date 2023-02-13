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
#include <etl/queue_spsc_atomic.h>
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


  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class Packet
  {
  public:
    static constexpr size_t MAX_FRAME_CAPACITY = std::numeric_limits<QOSStatus>::digits;

    uint16_t            ttl;       /**< Packet expiry time in milliseconds */
    Priority            priority;  /**< Priority of the packet */
    QOS                 qos;       /**< Quality of service level */
    QOSStatus           qosStatus; /**< Achieved QOS of each frame */
    Physical::FrameList head;      /**< List head to all frames in the packet */

    Packet();
    ~Packet();

    void initialize( Physical::FramePool &pool );

    Errno_t addFrame( Physical::Frame &frame );

    void ackFrame( const size_t idx );

    /**
     * @brief Comparison operator for packet priority queue sorting
     *
     * @param lhs   The left hand side of the comparison
     * @param rhs   The right hand side of the comparison
     * @return bool
     */
    bool operator()( Packet const &lhs, Packet const &rhs ) const
    {
      return lhs.priority < rhs.priority;
    }
  };

  /*---------------------------------------------------------------------------
  Aliases
  ---------------------------------------------------------------------------*/
  using DfltTXQueue = etl::queue_spsc_atomic<Packet, IRIS_TRANSPORT_TX_PACKET_QUEUE_SIZE>;
  using DfltRXQueue = etl::queue_spsc_atomic<Packet, IRIS_TRANSPORT_RX_PACKET_QUEUE_SIZE>;
  using PacketQueue = etl::iqueue_spsc_atomic<Packet>;

}    // namespace Iris::Transport

#endif /* !IRIS_TRANSPORT_TYPES_HPP */
