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

#ifndef RUNTIMEENVIRONMENT_H
#define RUNTIMEENVIRONMENT_H

#include <cstdint>
#include <map>

#include "ListenerNotifier.h"
#include "SensorData.h"

namespace driverassistance
{

namespace middleware
{

class RuntimeSensorListener;

class SensorInterface
{
public:

    SensorInterface( )
    {
        m_data = common::sensor::SensorData( common::sensor::Coordinates( 10, 10, 10 ), 1234567, 10 );
    }

    const common::sensor::SensorData& data( ) const
    {
        return m_data;
    }

protected:

    void set_id( uint16_t id )
    {
        m_id = id;
    }

private:

    uint16_t m_id;
    common::sensor::SensorData m_data;
};

class DummySensorInterface : public SensorInterface
{
public:

    DummySensorInterface( uint16_t id )
    {
        set_id( id );
    }
};

/**
 * @brief The RuntimeEnvironment class
 * A common runtime environment class for sensor data or information
 * Using singeton pattern for better access.
 */
class RuntimeEnvironment : public common::ListenerNotifier< RuntimeSensorListener >
{
public:

    /**
     * @brief instance Return a static object of RuntimeEnvironment
     * @return A static object of RuntimeEnvironment
     */
    static RuntimeEnvironment& instance( );

    /**
     * @brief sensor_data A getter to read a sensor data based on @sensor_id
     * @param sensor_id A sensor id
     * @return An object of sensor data. The caller needs to validate the data.
     */
    const common::sensor::SensorData& sensor_data( uint16_t sensor_id ) const;

    /**
     * @brief publish To publish the sensor data over the air
     * @param data A sensor data
     */
    void publish( const common::sensor::SensorData& data );

private:

    RuntimeEnvironment( );

private:

    std::map< uint16_t, SensorInterface > m_sensors;
    common::sensor::SensorData m_invalid_data;
};

} // middleware

} // driverassistance

#endif // RUNTIMEENVIRONMENT_H
