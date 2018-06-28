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

#include "SimpleHashTable.h"
#include "RuntimeEnvironment.h"

#include <cmath>
#include <vector>
#include <algorithm>


namespace driverassistance
{

namespace sensorfusion
{

// -------------------------------------------------------------------------------------------------

SimpleHashTable::SimpleHashTable( size_t max, uint16_t A, uint16_t B )
    : m_max( max )
    , m_A( A )
    , m_B( B )
{
}

// -------------------------------------------------------------------------------------------------

void
SimpleHashTable::add( const common::sensor::SensorData& data )
{
    // Generate simple hash value for the hash map key
    uint32_t key = generate_hash( data );

    // Time: best O(1), worst O(n). Space: O(n)
    auto found = m_hash.find( key );

    if ( found != m_hash.end( ) )
    {
        common::sensor::SensorData object = std::move( found->second );
        // Time: best O(1), worst O(n). Space: O(n)
        m_hash.erase( found );

        // Publish object
        driverassistance::middleware::RuntimeEnvironment::instance( ).publish( object );
    }

    if ( m_hash.size( ) >= m_max )
    {
        // Time: best O(1), worst O(n). Space: O(n)
        remove_oldest( );
    }

    // Time: best O(1), worst O(n). Space: O(n)
    m_hash[ key ] = data;
}

// -------------------------------------------------------------------------------------------------

uint32_t
SimpleHashTable::generate_hash( const common::sensor::SensorData& data )
{
    uint32_t hash = ( ( data.coordinates( ).x( ) * pow( m_A, 3 ) ) +
             ( data.coordinates().y( ) * pow( m_A, 2 ) ) +
             ( data.coordinates( ).z( ) * m_A ) + data.object_class( ) );
    return hash % m_B;
}

// -------------------------------------------------------------------------------------------------

void
SimpleHashTable::remove_oldest( )
{
    std::vector< std::pair< uint32_t, common::sensor::SensorData > > vec;

    for ( auto it = m_hash.begin( ); it != m_hash.end( ); ++it )
    {
        vec.push_back( *it );
    }

    std::sort( vec.begin( ),
               vec.end( ),
               [=] ( const std::pair< uint32_t, common::sensor::SensorData >& p1,
               const std::pair< uint32_t, common::sensor::SensorData >& p2 ) {

        return p1.second.timestamp( ) < p2.second.timestamp( );

    } );

    m_hash.erase( vec.front( ).first );
}

// -------------------------------------------------------------------------------------------------

} // sensorfusion

} // driverassistance

// End of file
