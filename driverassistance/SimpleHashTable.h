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

#ifndef DATACACHE_H
#define DATACACHE_H

#include <unordered_map>
#include "SensorData.h"

namespace driverassistance
{

namespace sensorfusion
{

/**
 * @brief The SimpleHashTable class
 * A hash table with its own (simple polynomial) hash function but
 * without any guarantee against collision.
 */
class SimpleHashTable
{
public:

    /**
     * @brief SimpleHashTable constructor
     * @param max The maximum number of elements
     * @param A first parameter for polynomial hash function
     * @param B second parameter for polynomial hash function
     */
    SimpleHashTable( size_t max, uint16_t A, uint16_t B );

    SimpleHashTable( ) = delete;

    /**
     * @brief add sensor data into SimpleHashTable
     * @param data The sensor data to be added
     */
    void add( const common::sensor::SensorData& data );

private:

    uint32_t generate_hash( const common::sensor::SensorData& data );

    void remove_oldest( );

private:

    std::unordered_map< uint32_t, common::sensor::SensorData > m_hash;
    size_t m_max;
    uint16_t m_A;
    uint16_t m_B;
};

} // sensorfusion

} // driverassistance

#endif // DATACACHE_H
