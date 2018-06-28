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

#ifndef RUNTIMESENSORLISTENER_H
#define RUNTIMESENSORLISTENER_H

#include "SensorData.h"

namespace driverassistance
{

namespace middleware
{

/**
 * @brief The RuntimeSensorListener class
 * A class for receiving sensor data from sensor sub-systems
 */
class RuntimeSensorListener
{
public:

    virtual ~RuntimeSensorListener( ) = default;

    /**
     * @brief on_sensor_data_updated a callback to receive sensor data
     * @param data A sensor data received from RunTimeEnvironment
     * @param sensor_id A sensor id which the data was comming from
     */
    virtual void on_sensor_data_updated( const common::sensor::SensorData& data, uint16_t sensor_id );

protected:

    RuntimeSensorListener( ) = default;

private:

    // Forbid copying
    RuntimeSensorListener( RuntimeSensorListener const& )            = delete;
    RuntimeSensorListener& operator=( RuntimeSensorListener const& ) = delete;


};

} // middleware

} // driverassistance

#endif // RUNTIMESENSORLISTENER_H
