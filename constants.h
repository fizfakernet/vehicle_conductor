#pragma once

#include <chrono>
#include "data_messages.h"

#define BUFFER_SIZE 250

namespace VehicleConstants
{
    constexpr std::chrono::milliseconds StepTime(100);
    constexpr std::chrono::milliseconds MonitorTime(1000);

    constexpr double Ctorgue = 21.7;
    constexpr double Cbrake  = 40.;
    constexpr double Cdrag   = 0.7;
    constexpr double Cstatic = 100.;
    constexpr double Mass    = 1000; // kg

    constexpr VehicleTypes::speed errorSpeed = 0.9;
}