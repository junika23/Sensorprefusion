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

#include "Signal.h"

#include <limits>

namespace common
{

const std::chrono::milliseconds INFINITE_TIMEOUT(
    std::numeric_limits< std::chrono::milliseconds::rep >::max( ) );

// -------------------------------------------------------------------------------------------------

Signal::Signal( const bool reset_after_set )
    : m_auto_reset( reset_after_set )
    , m_was_signaled( false )
{
}

// -------------------------------------------------------------------------------------------------

Signal::~Signal( )
{
    // destroying a condition_variable while threads are still waiting is undefined behavior
    // so make sure no-one is still waiting
    m_fulfilled.notify_all( );
}

// -------------------------------------------------------------------------------------------------

void
Signal::set( )
{
    std::lock_guard< std::mutex > guard( m_mutex );
    m_was_signaled = true;
    m_fulfilled.notify_all( );
}

// -------------------------------------------------------------------------------------------------

void
Signal::reset( )
{
    std::lock_guard< std::mutex > guard( m_mutex );
    m_was_signaled = false;
}

// -------------------------------------------------------------------------------------------------

bool
Signal::is_set( ) const
{
    std::lock_guard< std::mutex > guard( m_mutex );
    return m_was_signaled;
}

// -------------------------------------------------------------------------------------------------

bool
Signal::wait( )
{
    return wait( INFINITE_TIMEOUT );
}

// -------------------------------------------------------------------------------------------------

bool
Signal::wait( std::chrono::milliseconds timeout )
{
    std::unique_lock< std::mutex > lock( m_mutex );
    if ( timeout == INFINITE_TIMEOUT )
    {
        m_fulfilled.wait( lock, [this]( ) { return m_was_signaled; } );
    }
    else
    {
        m_fulfilled.wait_for( lock, timeout, [this]( ) { return m_was_signaled; } );
    }

    bool success = m_was_signaled;
    if ( m_auto_reset )
    {
        m_was_signaled = false;
    }

    return success;
}

// -------------------------------------------------------------------------------------------------

} // common
