#include "data_messages.h"

using namespace VehicleTypes;

class RegulatorSpeed
{
public:
    static void notAcceleration(TorqueBrake &tb, speed v);
    static volatile variable breakSpace(speed v1, speed v2);
    static volatile procent breakSmooth(speed v1, speed v2, variable s);
};

