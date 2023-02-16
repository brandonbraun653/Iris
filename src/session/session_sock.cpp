/******************************************************************************
 *  File Name:
 *    session_sock.cpp
 *
 *  Description:
 *    Socket implementation details
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/session>

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  Socket::Socket()
  {
  }

  Socket::~Socket()
  {
  }

  Errno_t Socket::open( const SockCfg &cfg )
  {
    return -1;
  }

  Errno_t Socket::accept( const size_t timeout )
  {
    return -1;
  }

  Errno_t Socket::connect( const SocketPort &conn, const size_t timeout )
  {
    return -1;
  }

  Errno_t Socket::close()
  {
    return -1;
  }

  size_t Socket::pendingMessages()
  {
    return 0;
  }

  size_t Socket::nextMessageSize()
  {
    return 0;
  }

  ssize_t Socket::read( void *const buffer, const size_t size )
  {
    return -1;
  }

  ssize_t Socket::write( const void *const buffer, const size_t size )
  {
    return -1;
  }

  Errno_t Socket::error()
  {
    return -1;
  }


  SocketPort Socket::port() const
  {
    return config.listenOn;
  }

  void Socket::accept_frame( const Physical::Frame &frame )
  {
  }

}    // namespace Iris::Session
