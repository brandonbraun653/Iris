/******************************************************************************
 *  File Name:
 *    transport_packet.hpp
 *
 *  Description:
 *    Packet abstraction for the transport layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_TRANSPORT_PACKET_HPP
#define IRIS_TRANSPORT_PACKET_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/src/transport/transport_types.hpp>

namespace Iris::Transport
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class Packet
  {
  public:
    uint16_t       ttl;      /**< Packet expiry time in milliseconds */
    Priority       priority; /**< Priority of the packet */
    QOS            qos;      /**< Quality of service level */
    Phy::FrameList head;     /**< List head to all frames in the packet */

    Packet();
    ~Packet();

    void initialize();

    void setFramePool( Phy::FramePool &pool );

    Errno_t addFrame( Phy::Frame &frame );

    void ackFrame( const size_t idx );

    /**
     * @brief Comparison operator for priority queue sorting
     *
     * @param lhs   The left hand side of the comparison
     * @param rhs   The right hand side of the comparison
     * @return bool
     */
    bool operator()( Packet const &lhs, Packet const &rhs ) const
    {
      return lhs.priority < rhs.priority;
    }

  private:
    uint32_t mFrameAckMask; /**< Bitmask of frames that have been acknowledged */
  };
}  // namespace Iris::Transport

#endif  /* !IRIS_TRANSPORT_PACKET_HPP */