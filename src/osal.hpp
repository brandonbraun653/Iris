/******************************************************************************
 *  File Name:
 *    osal.hpp
 *
 *  Description:
 *    OS abstraction layer
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

#pragma once
#ifndef IRIS_OSAL_HPP
#define IRIS_OSAL_HPP

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <cstdint>

namespace Iris::OSAL
{
  /*---------------------------------------------------------------------------
  Enumerations
  ---------------------------------------------------------------------------*/
  enum class SemaphoreId : uint8_t
  {
    RX_READY_NOTIFY,
    TX_READY_NOTIFY,
    ERROR_NOTIFY,

    NUM_OPTIONS
  };

  enum class MutexId : uint8_t
  {
    RX_QUEUE,
    TX_QUEUE,

    NUM_OPTIONS
  };

  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  /**
   * @brief Initializes the OSAL layer implementation
   */
  void init();

  /**
   * @brief Creates a semaphore
   *
   * @param id        The ID of the semaphore to create
   * @param maxCount  The maximum count of the semaphore
   * @param initCount The initial count of the semaphore
   * @return bool
   */
  bool createSemaphore( const SemaphoreId id, const uint32_t maxCount, const uint32_t initCount );

  /**
   * @brief Creates a mutex
   *
   * @param id        The ID of the mutex to create
   * @return bool
   */
  bool createMutex( const MutexId id );

  /**
   * @brief Waits for a semaphore to be signaled
   *
   * @param id        The ID of the semaphore to wait on
   * @param timeout   The maximum amount of time to wait for the semaphore in milliseconds
   * @return bool
   */
  bool waitSemaphore( const SemaphoreId id, const uint32_t timeout );

  /**
   * @brief Signals a semaphore
   *
   * @param id        The ID of the semaphore to signal
   * @return bool
   */
  bool signalSemaphore( const SemaphoreId id );

  /**
   * @brief Locks a mutex
   *
   * @param id        The ID of the mutex to lock
   * @param timeout   The maximum amount of time to wait for the mutex in milliseconds
   * @return bool
   */
  bool lockMutex( const MutexId id, const uint32_t timeout );

  /**
   * @brief Unlocks a mutex
   *
   * @param id        The ID of the mutex to unlock
   * @return bool
   */
  bool unlockMutex( const MutexId id );

}  // namespace Iris

#endif  /* !IRIS_OSAL_HPP */
