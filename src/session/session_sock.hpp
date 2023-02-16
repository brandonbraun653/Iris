/******************************************************************************
 *  File Name:
 *    session_sock.hpp
 *
 *  Description:
 *    Main interface for the session layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_SESSION_HPP
#define IRIS_SESSION_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/src/session/session_types.hpp>
#include <Iris/src/transport/transport_types.hpp>
#include <Iris/src/types.hpp>
#include <cstddef>

namespace Iris::Session
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  class SessionManager;

  /*---------------------------------------------------------------------------
  Classes
  ---------------------------------------------------------------------------*/
  class Socket
  {
  public:
    Socket();
    ~Socket();

    /**
     * @brief Opens a socket for communication
     *
     * @param cfg     The configuration to use
     * @return Errno_t
     */
    Errno_t open( const SockCfg &cfg );

    /**
     * @brief Wait for a connection to be established
     *
     * @param timeout   How long to wait for a connection
     * @return Errno_t
     */
    Errno_t accept( const size_t timeout );

    /**
     * @brief Connects to a remote socket
     *
     * @param conn    The connection to make
     * @param timeout How long to wait for success
     * @return Errno_t
     */
    Errno_t connect( const SocketPort &conn, const size_t timeout );

    /**
     * @brief Closes the socket
     * @return Errno_t
     */
    Errno_t close();

    /**
     * @brief Gets the number of RX messages that are pending
     * @return size_t
     */
    size_t pendingMessages();

    /**
     * @brief Gets the size of the next message in the RX queue
     * @return size_t
     */
    size_t nextMessageSize();

    /**
     * @brief Reads a message from the RX queue
     * @note Sets the error code if the read fails
     *
     * @param buffer  The buffer to read into
     * @param size    The size of the buffer
     * @return ssize_t The number of bytes read or negative on error
     */
    ssize_t read( void *const buffer, const size_t size );

    /**
     * @brief Writes a message to the TX queue
     *
     * @param buffer    The buffer to write from
     * @param size      The size of the buffer
     * @return ssize_t  The number of bytes written or negative on error
     */
    ssize_t write( const void *const buffer, const size_t size );

    /**
     * @brief Gets the latest error code
     * @return Errno_t
     */
    Errno_t error();

    /**
     * @brief Gets the port number for this socket
     * @return SocketPort
     */
    SocketPort port() const;

  protected:
    friend class SessionManager;

    /**
     * @brief The main socket processing loop
     */
    void accept_frame( const Physical::Frame &frame );

  private:
    SockCfg config; /**< The configuration for this socket */
  };
}  // namespace Iris::Ses

#endif  /* !IRIS_SESSION_HPP */
