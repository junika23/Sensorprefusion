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

#include <iostream>
#include <chrono>
#include <thread>
#include <signal.h>

#include "driverassistance/SensorPreFusion.h"


void sig_handler(int s)
{
    std::cout << "Caught signal " << s << std::endl;
    exit(1);
}

// ------------------------------------------------------------------------------------------------

int main( int argc, char* argv[ ] )
{
    signal( SIGINT, sig_handler );

    driverassistance::sensorfusion::SensorPreFusion sensor_pre_fusion;
    sensor_pre_fusion.init( true );

    while (1)
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
    }

    return 0;
}

// -------------------------------------------------------------------------------------------------

// End of file
