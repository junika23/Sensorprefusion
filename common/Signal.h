/*
// -------------------------------------------------------------------------------------------------
//
// Copyright (C) Juniarto Saputra (juniarto.wongso@gmail.com). All rights reserved.
//
// This software, including documentation, is protected by copyright controlled by
// the contributor(s). All rights are reserved. Copying, including reproducing, storing,
// adapting or translating, any or all of this material requires the prior written
// consent of the contributor(s).
//
// -------------------------------------------------------------------------------------------------
*/

#pragma once

#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <mutex>

namespace common
{

/**
 * @brief A convenience class to synchronize between threads
 *
 * Using Signal one or more threads can wait for another thread, e.g. for a calculation result.
 * Signal is similar to a condition variable but avoids spurious wakeups. The downside is that
 * resetting the signal can lead to the situation that not all threads are woken if multiple threads
 * wait for the same signal.
 */
class Signal
{
public:

    /**
     * @brief Construct a Signal
     * @param reset_after_set the signal will be automatically reset by #wait() if it has been set.
     */
    explicit Signal( const bool reset_after_set = true );
    ~Signal( );

    Signal( const Signal& other ) = delete;
    Signal& operator=( const Signal& other ) = delete;

    /**
     * @brief set the signal
     */
    void set( );

    /**
     * @brief reset the signal
     */
    void reset( );

    /**
     * @brief return true if the signal is set
     */
    bool is_set( ) const;

    /**
     * @brief Waits until the signal is set
     *
     * The method returns immediately if the signal was already set, otherwise it will wait for it.
     * This method will block until the signal is set.
     *
     * @return true if the signal was set, false otherwise (e.g. if the destructor was called)
     *
     * @note be aware that not all threads might be woken up if multiple threads wait for the same
     * signal.
     */
    bool wait( );

    /**
     * @brief Waits until the signal is set or until a specified time is over
     *
     * The method returns immediately if the signal was already set, otherwise it will wait for it
     * until the specified timeout is over.
     *
     * @param timeout The max time to wait.
     *
     * @return true if the signal was set within the timeout, 
     *         false otherwise (timeout happened or the destructor was called
     *
     * @note be aware that not all threads might be woken up if multiple threads wait for the same
     * signal.
     */
    bool wait( std::chrono::milliseconds timeout );

private:
    bool m_auto_reset;
    bool m_was_signaled;
    mutable std::mutex m_mutex;
    std::condition_variable m_fulfilled;
};
}

