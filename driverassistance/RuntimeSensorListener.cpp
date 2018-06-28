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

#include "RuntimeSensorListener.h"


namespace driverassistance
{

namespace middleware
{

// -------------------------------------------------------------------------------------------------

void
RuntimeSensorListener::on_sensor_data_updated( const common::sensor::SensorData& data,
                                               uint16_t sensor_id )
{
    VAR_UNUSED( data );
    VAR_UNUSED( sensor_id );
}

// -------------------------------------------------------------------------------------------------

} // middleware

} // driverassistance

// End of file
