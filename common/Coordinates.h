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

#ifndef COORDINATES_H
#define COORDINATES_H

#include <cstdint>

namespace common
{

namespace sensor
{

/**
 * @brief The Coordinates class
 * Coordinates of a detected object with respect to the vehicle’s mass center [Xv, Yv, Zv] in meter
 * as a scaled 16 bit unsigend integer value, scaling factor 1/1000, the default/init value is 0xFFFF
 */
class Coordinates
{
public:

    /**
     * @brief Default constructor
     * Construct an invalid Coordinates object
     */
    Coordinates( );

    /**
     * @brief Default constructor with parameters
     * @param x An unsigned number represents x-axis with respect to the vehicle’s masscenter in meter
     * @param y An unsigned number represents y-axis with respect to the vehicle’s masscenter in meter
     * @param z An unsigned number represents z-axis with respect to the vehicle’s masscenter in meter
     */
    Coordinates( uint16_t x, uint16_t y, uint16_t z );

    /**
     * @brief Copy constructor
     * @param other another Coordinates object to be copied.
     */
    Coordinates( const Coordinates& other );

public:

    /**
     * @brief Validates the Coordinates object
     * @return True if Coordinates is valid, false otherwise.
     */
    bool is_valid( ) const;

    /**
     * @brief Get the x value from Coordinates
     * @return x
     */
    uint16_t x( ) const
    {
        return m_x;
    }

    /**
     * @brief Get the y from Coordinates
     * @return y
     */
    uint16_t y( ) const
    {
        return m_y;
    }

    /**
     * @brief Get the z from Coordinates
     * @return z
     */
    uint16_t z( ) const
    {
        return m_z;
    }

public:

    /**
     * @brief Equality of Coordinates.
     * Coordinates are equal when all parts are equal.
     * This Coordinates and lhs need to be valid. If either is (or both!)
     * are invalid, the function returns false.
     *
     * @param lhs The Coordinates to compare to.
     *
     * @return True if Coordinates are equal.
     */
    bool operator==( const Coordinates& lhs ) const;

    /**
     * @brief Inequality Coordinates.
     * Coordinates are not equal when any of Coordinates parts are not equal.
     * This Coordinates and lhs need to be valid. If either is (or both!)
     * are invalid, the function returns true.
     *
     * @param lhs The Coordinates to compare to.
     *
     * @return true if Coordinates are not equal.
     */
    bool operator!=( const Coordinates& lhs ) const;

private:

    uint16_t m_x;
    uint16_t m_y;
    uint16_t m_z;
};

} // sensor

} // common

#endif // COORDINATES_H
