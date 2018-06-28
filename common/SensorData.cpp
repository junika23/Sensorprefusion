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

#include "SensorData.h"


namespace common
{

namespace sensor
{

// -------------------------------------------------------------------------------------------------

SensorData::SensorData( )
    : m_coordinates( 0xFFFF, 0xFFFF, 0xFFFF )
    , m_timestamp( 0 )
    , m_object_class( 0 )
{
}

// -------------------------------------------------------------------------------------------------

SensorData::SensorData( const Coordinates& coordinates, uint32_t timestamp, uint8_t object_class )
    : m_coordinates( coordinates )
    , m_timestamp( timestamp )
    , m_object_class( object_class )
{
}

// -------------------------------------------------------------------------------------------------

SensorData::SensorData( const SensorData& other )
{
    m_coordinates = other.coordinates( );
    m_timestamp = other.timestamp( );
    m_object_class = other.object_class( );
}

// -------------------------------------------------------------------------------------------------

bool
SensorData::is_valid( ) const
{
    return ( m_coordinates.is_valid( ) &&
             m_timestamp > 0 &&
             m_object_class > 0 );
}

// -------------------------------------------------------------------------------------------------

bool
SensorData::operator==( const SensorData& rhs ) const
{
    return is_valid( )
        && rhs.is_valid( )
        && m_coordinates == rhs.coordinates( )
        && m_object_class == rhs.object_class( );
}

// -------------------------------------------------------------------------------------------------

bool
SensorData::operator!=( const SensorData& rhs ) const
{
    return !( *this == rhs );
}

// -------------------------------------------------------------------------------------------------

} // sensor

} // common

// End of file
