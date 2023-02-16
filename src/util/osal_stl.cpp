/******************************************************************************
 *  File Name:
 *    osal.cpp
 *
 *  Description:
 *    Iris OSAL implementation using C++20 STL
 *
 *  2023 | Brandon Braun | brandonbraun653@protonmail.com
 *****************************************************************************/

/*-----------------------------------------------------------------------------
Includes
-----------------------------------------------------------------------------*/
#include <Iris/Iris>
#include <chrono>
#include <semaphore>
#include <mutex>

namespace Iris::OSAL
{
  /*---------------------------------------------------------------------------
  Public Functions
  ---------------------------------------------------------------------------*/
  void init()
  {
    // Nothing to do here
  }


  SemaphoreHandle_t createSemaphore()
  {
    return new std::binary_semaphore( 0 );
  }


  void deleteSemaphore( SemaphoreHandle_t handle )
  {
    assert( handle );
    delete reinterpret_cast<std::binary_semaphore *>( handle );
  }


  MutexHandle_t createMutex()
  {
    return new std::recursive_timed_mutex();
  }


  void deleteMutex( MutexHandle_t handle )
  {
    assert( handle );
    delete reinterpret_cast<std::recursive_timed_mutex *>( handle );
  }


  bool waitSemaphore( const SemaphoreHandle_t handle, const uint32_t timeout )
  {
    assert( handle );
    return reinterpret_cast<std::binary_semaphore *>( handle )->try_acquire_for( std::chrono::milliseconds( timeout ) );
  }


  void signalSemaphore( const SemaphoreHandle_t handle )
  {
    assert( handle );
    reinterpret_cast<std::binary_semaphore *>( handle )->release();
  }


  bool lockMutex( const MutexHandle_t handle, const uint32_t timeout )
  {
    assert( handle );
    return reinterpret_cast<std::recursive_timed_mutex *>( handle )->try_lock_for( std::chrono::milliseconds( timeout ) );
  }


  void unlockMutex( const MutexHandle_t handle )
  {
    assert( handle );
    reinterpret_cast<std::recursive_timed_mutex *>( handle )->unlock();
  }

}    // namespace Iris::OSAL
