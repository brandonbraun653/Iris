/******************************************************************************
 *  File Name:
 *    transport_packet.cpp
 *
 *  Description:
 *    Packet abstraction for the transport layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/transport>
#include <limits>

namespace Iris::Transport
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  Packet::Packet()
  {
  }


  Packet::~Packet()
  {
  }


  void Packet::initialize( Physical::FramePool &pool )
  {
    head.set_pool( pool );
    head.clear();
  }


  Errno_t Packet::addFrame( Physical::Frame &frame )
  {
    return -1;
  }


  void Packet::ackFrame( const size_t idx )
  {
  }

}    // namespace Iris::Transport
