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

#ifndef SENSORPREFUSION_H
#define SENSORPREFUSION_H

#include "SensorData.h"
#include "RuntimeSensorListener.h"
#include "SimpleHashTable.h"

#include <thread>
#include <mutex>

namespace driverassistance
{

namespace sensorfusion
{

/**
 * @brief The SensorPreFusion class
 * A class for sensor data pre fusion
 */
class SensorPreFusion : public driverassistance::middleware::RuntimeSensorListener
{
public:

    /**
     * @brief Default constructor
     * Construct a SensorPreFusion object
     */
    SensorPreFusion( );

    virtual ~SensorPreFusion( );

public:

    /**
     * @brief init to decided whether a periodic timer approach or listener will be used
     * @param using_periodic_timer True a periodic timer approach will be used, false otherwise.
     */
    void init( bool using_periodic_timer );

protected:

    /**
     * @brief on_sensor_data_updated a callback from ListenerNotifier
     * @param data A sensor data received from RunTimeEnvironment
     * @param sensor_id A sensor id which the data was comming from
     */
    void on_sensor_data_updated( const common::sensor::SensorData& data, uint16_t sensor_id ) override;

private:

    void start_timer(uint32_t interval_ms );

    void stop_timer( );

    void get_sensor_data( );

private:

    std::thread m_thread;
    SimpleHashTable m_list;
    mutable std::mutex m_mutex;
};

} // sensorfusion

} // driverassistance

#endif // SENSORPREFUSION_H
