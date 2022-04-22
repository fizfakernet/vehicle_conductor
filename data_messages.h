#pragma once

namespace VehicleTypes
{
    typedef int procent;
    typedef float variable;
    typedef unsigned long long int timestamp;
    typedef double speed;

    struct TorqueBrake
    {
        procent torque; // proc [0..100]
        procent brake;  // proc [0..100]
    };

    struct PositionTimestamp
    {
        variable position; // metres
        timestamp time;    // milliseconds
        speed v;           // m/s
        bool positionValid = false;
        bool timeValid = false;
        bool vValid = false;
        void vCalculate(const PositionTimestamp &aldMess)
        {
            vValid = false;
            if( timeValid && aldMess.timeValid && positionValid && aldMess.positionValid )
            {
                speed dt = time - aldMess.time;
                if( 0 == dt ) return;
                v = 1000 * ( position - aldMess.position ) / dt;
                vValid = true;
            }
        }
        bool isValid(){return (positionValid && timeValid && vValid); }
    };

} // namespace VehicleTypes
