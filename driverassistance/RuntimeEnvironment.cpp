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

#include "RuntimeEnvironment.h"

#include <iostream>


namespace driverassistance
{

namespace middleware
{

// -------------------------------------------------------------------------------------------------

RuntimeEnvironment& RuntimeEnvironment::instance() {
    static RuntimeEnvironment runtime;
    return runtime;
}

// -------------------------------------------------------------------------------------------------

RuntimeEnvironment::RuntimeEnvironment( )
{
    // Initialize the four sensors
    for ( uint16_t i = 1; i < 5; ++i )
    {
        DummySensorInterface sensor( i );
        m_sensors[ i ] = sensor;
    }
}

// -------------------------------------------------------------------------------------------------

const common::sensor::SensorData&
RuntimeEnvironment::sensor_data( uint16_t sensor_id ) const
{
    return m_sensors.count( sensor_id ) ? m_sensors.at( sensor_id ).data( ) : m_invalid_data;
}

// -------------------------------------------------------------------------------------------------

void
RuntimeEnvironment::publish( const common::sensor::SensorData& data )
{
    std::cout << "Publishing object: " << unsigned( data.object_class( ) ) <<
                 " with timestamp: " << data.timestamp( ) << " into the cloud" << std::endl;
}

// -------------------------------------------------------------------------------------------------

} // sensor

} // common

// End of file
