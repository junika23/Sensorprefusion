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

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <cstdint>

#include "Coordinates.h"

namespace common
{

namespace sensor
{

#define VAR_UNUSED( x ) ( ( void )&( x ) )

/**
 * @brief The SensorData class
 * A common class for sensor data or information
 */
class SensorData
{
public:

    /**
     * @brief Default constructor
     * Construct an invalid SensorData object
     */
    SensorData( );

    /**
     * @brief Default constructor with parameters
     * @param coordinates A coordinates represent an object with respect to the vehicle’s mass center [Xv, Yv, Zv] in meter
     * @param timestamp A timestamp
     * @param object_class An object class
     */
    SensorData( const Coordinates& coordinates, uint32_t timestamp, uint8_t object_class );

    /**
     * @brief Copy constructor
     * @param other another SensorData object to be copied.
     */
    SensorData( const SensorData& other );

public:

    /**
     * @brief Validates the SensorData object
     * @return True if SensorData is valid, false otherwise.
     */
    bool is_valid( ) const;

    /**
     * @brief Get the object coordinates from SensorData
     * @return coordinates
     */
    Coordinates coordinates( ) const
    {
        return m_coordinates;
    }

    /**
     * @brief Get the timestamp from SensorData
     * @return timestamp
     */
    uint32_t timestamp( ) const
    {
        return m_timestamp;
    }

    /**
     * @brief Get the object class from SensorData
     * @return second
     */
    uint8_t object_class( ) const
    {
        return m_object_class;
    }

public:

    /**
     * @brief Equality of SensorData.
     * SensorData are equal when all parts are equal except the timestamp.
     * This SensorData and lhs need to be valid. If either is (or both!)
     * are invalid, the function returns false.
     *
     * @param lhs The SensorData to compare to.
     *
     * @return True if SensorData are equal.
     */
    bool operator==( const SensorData& lhs ) const;

    /**
     * @brief Inequality SensorData.
     * SensorData are not equal when any of SensorData parts except the timestamp are not equal.
     * This SensorData and lhs need to be valid. If either is (or both!)
     * are invalid, the function returns true.
     *
     * @param lhs The SensorData to compare to.
     *
     * @return true if SensorData are not equal.
     */
    bool operator!=( const SensorData& lhs ) const;

private:

    Coordinates m_coordinates;
    uint32_t m_timestamp;
    uint8_t m_object_class;
};

} // sensor

} // common

#endif // SENSORDATA_H
