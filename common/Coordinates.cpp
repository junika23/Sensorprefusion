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

#include "Coordinates.h"


namespace common
{

namespace sensor
{

// -------------------------------------------------------------------------------------------------

Coordinates::Coordinates( )
    : m_x( 0xFFFF )
    , m_y( 0xFFFF )
    , m_z( 0xFFFF )
{
}

// -------------------------------------------------------------------------------------------------

Coordinates::Coordinates( uint16_t x, uint16_t y, uint16_t z )
    : m_x( x )
    , m_y( y )
    , m_z( z )
{
}

// -------------------------------------------------------------------------------------------------

Coordinates::Coordinates( const Coordinates& other )
{
    m_x = other.x( );
    m_y = other.y( );
    m_z = other.z( );
}

// -------------------------------------------------------------------------------------------------

bool
Coordinates::is_valid( ) const
{
    return ( m_x != 0xFFFF && m_y != 0xFFFF && m_z != 0xFFFF );
}

// -------------------------------------------------------------------------------------------------

bool
Coordinates::operator==( const Coordinates& rhs ) const
{
    return is_valid( )
        && rhs.is_valid( )
        && m_x == rhs.x( )
        && m_y == rhs.y( )
        && m_z == rhs.z( );
}

// -------------------------------------------------------------------------------------------------

bool
Coordinates::operator!=( const Coordinates& rhs ) const
{
    return !( *this == rhs );
}

// -------------------------------------------------------------------------------------------------

} // sensor

} // common

// End of file
