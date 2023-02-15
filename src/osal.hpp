/******************************************************************************
 *  File Name:
 *    osal.hpp
 *
 *  Description:
 *    OS abstraction layer. This needs implementation by the Iris integrator.
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
  Aliases
  ---------------------------------------------------------------------------*/
  using SemaphoreHandle_t = void *;
  using MutexHandle_t     = void *;

  /*---------------------------------------------------------------------------
  Constants
  ---------------------------------------------------------------------------*/
  static constexpr uint32_t WAIT_FOREVER = 0xFFFFFFFF;
  static constexpr uint32_t NO_WAIT      = 0x00000000;

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
   * @param maxCount  The maximum count of the semaphore
   * @param initCount The initial count of the semaphore
   * @return SemaphoreHandle_t
   */
  SemaphoreHandle_t createSemaphore( const uint32_t maxCount, const uint32_t initCount );

  /**
   * @brief Deletes a semaphore
   *
   * @param handle    The handle of the semaphore to delete
   * @return void
   */
  void deleteSemaphore( const SemaphoreHandle_t handle );

  /**
   * @brief Creates a mutex
   * @return MutexHandle_t
   */
  MutexHandle_t createMutex();

  /**
   * @brief Deletes a mutex
   *
   * @param handle    The handle of the mutex to delete
   * @return void
   */
  void deleteMutex( const MutexHandle_t handle );

  /**
   * @brief Waits for a semaphore to be signaled
   *
   * @param handle    The handle of the semaphore to wait on
   * @param timeout   The maximum amount of time to wait for the semaphore in milliseconds
   * @return bool
   */
  bool waitSemaphore( const SemaphoreHandle_t handle, const uint32_t timeout );

  /**
   * @brief Signals a semaphore
   *
   * @param handle    The handle of the semaphore to signal
   * @return bool
   */
  bool signalSemaphore( const SemaphoreHandle_t handle );

  /**
   * @brief Locks a mutex
   *
   * @param handle    The handle of the mutex to lock
   * @param timeout   The maximum amount of time to wait for the mutex in milliseconds
   * @return bool
   */
  bool lockMutex( const MutexHandle_t handle, const uint32_t timeout );

  /**
   * @brief Unlocks a mutex
   *
   * @param handle    The handle of the mutex to unlock
   * @return bool
   */
  bool unlockMutex( const MutexHandle_t handle );

}  // namespace Iris

#endif  /* !IRIS_OSAL_HPP */
