/******************************************************************************
 *  File Name:
 *    physical_types.hpp
 *
 *  Description:
 *    Specification of the hardware interface
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_PHYSICAL_TYPES_HPP
#define IRIS_PHYSICAL_TYPES_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include "iris_physical_prj.hpp"
#include <Iris/src/types.hpp>
#include <cstdint>
#include <etl/delegate.h>
#include <etl/forward_list.h>

/*-----------------------------------------------------------------------------
Literal Constants
-----------------------------------------------------------------------------*/
#ifndef IRIS_HW_INTF_MAX_FRAME_SIZE
/**
 * @brief The maximum size of a frame that can be sent or received on the HW interface
 */
#define IRIS_HW_INTF_MAX_FRAME_SIZE ( 128 )
#endif

#ifndef IRIS_PHY_PRJ_HEADER_SIZE
/**
 * @brief Size of the HW driver header in bytes, if required
 */
#define IRIS_PHY_PRJ_HEADER_SIZE ( 4 )
#endif

#ifndef IRIS_PHY_PRJ_PAYLOAD_SIZE
/**
 * @brief Maximum size of the payload in bytes
 */
#define IRIS_PHY_PRJ_PAYLOAD_SIZE                                                                        \
  ( IRIS_HW_INTF_MAX_FRAME_SIZE - IRIS_PHY_PRJ_HEADER_SIZE - sizeof( Iris::Physical::TransactionId_t ) - \
    sizeof( Iris::Physical::FragmentId_t ) - sizeof( Iris::Physical::FrameSize_t ) )
#endif

#ifndef IRIS_PHY_PRJ_FRAME_POOL_SIZE
/**
 * @brief Total frames available in the frame pool
 * @note These frames are used for building packets in send and receive buffers
 */
#define IRIS_PHY_PRJ_FRAME_POOL_SIZE ( 32 )
#endif

namespace Iris::Physical
{
  /*---------------------------------------------------------------------------
  Forward Declarations
  ---------------------------------------------------------------------------*/
  struct Frame;

  /*---------------------------------------------------------------------------
  Aliases
  ---------------------------------------------------------------------------*/
  using FrameList = etl::forward_list_ext<Frame>;
  using FramePool = etl::ipool;
  using DfltFramePool = etl::pool<Frame, IRIS_PHY_PRJ_FRAME_POOL_SIZE>;
#ifndef IRIS_PHY_PRJ_FRAME_TYPES
  using FrameSize_t     = uint16_t;
  using FragmentId_t    = uint8_t;
  using TransactionId_t = uint8_t;
#endif /* !IRIS_PHY_PRJ_FRAME_TYPES */

  /*---------------------------------------------------------------------------
  Structures
  ---------------------------------------------------------------------------*/
#pragma pack( push, 1 )
  /**
   * @brief Base unit of data that is sent or received on the HW interface
   */
  struct Frame
  {
#if IRIS_PHY_PRJ_HEADER_SIZE > 0
    uint8_t header[ IRIS_PHY_PRJ_HEADER_SIZE ]; /**< Optional header for the HW driver */
#endif
    TransactionId_t transaction;                       /**< Transaction ID of packet */
    FragmentId_t    fragment;                          /**< Fragment number */
    FrameSize_t     size;                              /**< Size of the data */
    uint8_t         data[ IRIS_PHY_PRJ_PAYLOAD_SIZE ]; /**< Data being sent or received */
  };
#pragma pack( pop )
  static_assert( sizeof( Frame ) == IRIS_HW_INTF_MAX_FRAME_SIZE, "Frame size is incorrect" );


  /**
   * @brief Interface for the hardware layer to interact with the network layer
   */
  struct NotifyAPI
  {
    /**
     * @brief Called when the hardware is ready to send a frame
     * @return void
     */
    etl::delegate<void( void )> onTXReady;

    /**
     * @brief Called when the hardware has received a frame
     * @return void
     */
    etl::delegate<void( void )> onRXReady;

    /**
     * @brief Called when the hardware has encountered an error
     *
     * @param error What error occurred
     * @return void
     */
    etl::delegate<void( Errno_t )> onError;
  };


  /**
   * @brief Interface for the network layer to interact with the hardware
   */
  struct NetifAPI
  {
    /**
     * @brief Opens the hardware interface
     *
     * @param cb        Callbacks for the hardware layer to notify the network layer
     * @return Errno_t
     */
    etl::delegate<Errno_t( NotifyAPI & )> open;

    /**
     * @brief Closes the hardware interface
     * @return void
     */
    etl::delegate<void( void )> close;

    /**
     * @brief Called periodically to process state
     * @return Errno_t
     */
    etl::delegate<Errno_t( void )> process;

    /**
     * @brief Puts a frame onto the wire
     *
     * @param frame     Frame to send
     * @return Errno_t
     */
    etl::delegate<Errno_t( Frame & )> put;

    /**
     * @brief Gets a frame from the wire
     *
     * @param frame     Where to store the frame
     * @return Errno_t
     */
    etl::delegate<Errno_t( Frame & )> get;
  };

}    // namespace Iris::Physical

#endif /* !IRIS_PHYSICAL_TYPES_HPP */
