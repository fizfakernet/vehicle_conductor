#include "regulator_speed.h"
#include "constants.h"
#include <math.h>

using namespace VehicleConstants;

void RegulatorSpeed::notAcceleration(TorqueBrake &tb, speed v)
{
    tb.torque = ( ( (Cdrag * v*v) + Cstatic ) / Ctorgue );
    tb.brake = 0;
}

volatile variable RegulatorSpeed::breakSpace(speed v1, speed v2)
{ 
    return 65; // this must be calculate
}

volatile procent RegulatorSpeed::breakSmooth(speed v1, speed v2, variable s)
{
    return 63; // this must be calculate
}