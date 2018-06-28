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

#include <functional>
#include <mutex>

namespace common
{
/**
 * Simple atomic copy on read wrapper.
 */
template < class Type >
class Atomic
{
public:
    using value_type = Type;

    /**
     * Construct.
     */
    template < class SomeType >
    Atomic( SomeType&& m )
        : m( std::forward< SomeType >( m ) )
    {
    }

    /**
     * Construct.
     */
    Atomic( )
        : m( )
    {
    }

    /**
     * Calls the lambda while having a lock on the data.
     */
    template < class Functor >
    auto locked( Functor&& lambda ) -> decltype( lambda( std::declval< Type& >( ) ) )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        return lambda( m );
    }

    /**
     * Calls the lambda while having a lock on the data.
     * const version.
     *
     */
    template < class Functor >
    auto locked( Functor&& lambda ) const -> decltype( lambda( std::declval< const Type& >( ) ) )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        return lambda( m );
    }

    /**
     * Return a copy of the data.
     */
    Type
    locked_copy( ) const
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        return m;
    }

    /**
     * Return the moved data while having a lock.
     */
    Type
    locked_move( )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        return std::move( m );
    }

    /**
     * Assign the data while having a lock.
     */
    template < class SomeType >
    void
    locked_assign( SomeType&& am )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        m = std::forward< SomeType >( am );
    }

    /**
     * Swap while having a lock on the data.
     */
    void
    locked_swap( Type& other )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        std::swap( m, other );
    }

    /**
     * Swap with Type() while having a lock on the data and move.
     */
    Type
    locked_swap_with_default( )
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        Type other{};
        std::swap( m, other );
        return other;
    }

    /**
     * Convert to bool if wrapped type is bool convertible.
     */
    explicit operator bool( ) const
    {
        std::lock_guard< std::mutex > lock( m_mutex );
        return static_cast< bool >( m );
    }

protected:
    mutable std::mutex m_mutex;
    Type m;
};

} // common
