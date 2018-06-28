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

#include "SensorPreFusion.h"
#include "RuntimeEnvironment.h"

namespace driverassistance
{

namespace sensorfusion
{

// -------------------------------------------------------------------------------------------------

SensorPreFusion::SensorPreFusion( )
    : m_list( 10, 3, 91 )
{
}

// -------------------------------------------------------------------------------------------------

SensorPreFusion::~SensorPreFusion( )
{
    if ( driverassistance::middleware::RuntimeEnvironment::instance( ).is_listener_added( this ) )
    {
        driverassistance::middleware::RuntimeEnvironment::instance( ).remove_listener( this );
    }
}

// -------------------------------------------------------------------------------------------------

void
SensorPreFusion::init( bool using_periodic_timer )
{
    if ( !using_periodic_timer )
    {
        driverassistance::middleware::RuntimeEnvironment::instance( ).add_listener( this );
    }
    else
    {
        start_timer( 10 );
    }
}

// -------------------------------------------------------------------------------------------------

void
SensorPreFusion::on_sensor_data_updated( const common::sensor::SensorData& data, uint16_t sensor_id )
{
    VAR_UNUSED( sensor_id );
    std::lock_guard< std::mutex > guard( m_mutex );
    m_list.add( data );
}

// -------------------------------------------------------------------------------------------------

void
SensorPreFusion::start_timer( uint32_t interval_ms )
{
    std::thread( [ this, interval_ms ] ( ) {

        while ( true )
        {
            auto delay = std::chrono::steady_clock::now( ) +
                    std::chrono::milliseconds( interval_ms );
            get_sensor_data( );
            std::this_thread::sleep_until( delay );
        }

    }).detach( );
}

// -------------------------------------------------------------------------------------------------

void
SensorPreFusion::get_sensor_data( )
{
    m_list.add( driverassistance::middleware::RuntimeEnvironment::instance( ).sensor_data( 1 ) );
    m_list.add( driverassistance::middleware::RuntimeEnvironment::instance( ).sensor_data( 2 ) );
    m_list.add( driverassistance::middleware::RuntimeEnvironment::instance( ).sensor_data( 3 ) );
    m_list.add( driverassistance::middleware::RuntimeEnvironment::instance( ).sensor_data( 4 ) );
}

// -------------------------------------------------------------------------------------------------

} // sensorfusion

} // driverassistance

// End of file
