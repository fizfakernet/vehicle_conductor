#pragma once

#include <chrono>
#include <atomic>
#include <iostream>
#include <thread>
#include "data_messages.h"
#include "conductor.h"
#include "constants.h"
#include "monitor.h"

using namespace VehicleTypes;
using namespace std::chrono_literals;
using namespace std;
using namespace VehicleConstants;

void repeat(ConductorBase *conductor);
std::atomic<bool> running;

void loop(ConductorBase *conductor)
{
    conductor->drive();
}

void repeat(ConductorBase *conductor)
{
    if(nullptr == conductor) return;

    while (running)
    {
        loop(conductor);
        std::this_thread::sleep_for(StepTime);
    }

}

void repeatMonitorShow(Monitor *monitor)
{
    if(nullptr == monitor) return;

    while (running)
    {
        monitor -> print();
        std::this_thread::sleep_for(MonitorTime);
    }

}
