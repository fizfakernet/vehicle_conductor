#include <ctime>
#include "conductor.h"
#include "regulator_speed.h"
#include "constants.h"
#include <iostream>

using namespace VehicleConstants;

ConductorBase::ConductorBase( LimitationMap &lm,
        Proxy<PositionTimestamp> &pos_proxy_, 
        Proxy<TorqueBrake> &torque_brake_proxy_,
        Reader &reader_,
        Sender &sender_) :
limitation_map{lm},
pos_proxy{pos_proxy_},
torque_brake_proxy{torque_brake_proxy_},
reader{reader_},
sender{sender_}
{
    limitation_map.init();
}

ConductorFast::ConductorFast( LimitationMap &lm,
        Proxy<PositionTimestamp> &pos_proxy_, 
        Proxy<TorqueBrake> &torque_brake_proxy_,
        Reader &reader_,
        Sender &sender_) :
ConductorBase(lm, pos_proxy_, torque_brake_proxy_, reader_, sender_)
{

}

int ConductorFast::drive()
{
    if(reader.readMessage(pos_proxy))
    {
        return 0;
    };

    PositionTimestamp curState = pos_proxy.getMessage();
    if( !curState.isValid() ) return 1;
    Limitation* lim = limitation_map.getCurentLimitation(curState.position);
    if( nullptr == lim )
    {
        std::cerr << "Map is not full\n";
        return 2;
    }
    speed taskSpeed = lim->speedLim.second;

    TorqueBrake torqueBrake;
    if( ( taskSpeed - curState.v ) > errorSpeed )
    {
        torqueBrake.torque = 100;
        torqueBrake.brake = 0;
    }
    else if( (( curState.v - taskSpeed ) > errorSpeed) || ( taskSpeed < errorSpeed ) )
    {
        if( (Limitation::ChangerType::taskFast == lim->changerType) || (Limitation::ChangerType::fast == lim->changerType) )
        {
            torqueBrake.torque = 0;
            torqueBrake.brake = 100;
        }
        else if( (Limitation::ChangerType::taskSmooth == lim->changerType) || (Limitation::ChangerType::smooth == lim->changerType) )
        {
            torqueBrake.torque = 0;
            torqueBrake.brake = lim->breakTask;
        }
    }
    else
    {
        RegulatorSpeed::notAcceleration(torqueBrake, taskSpeed);
    }
    torque_brake_proxy.setMessage(torqueBrake);
    int res = sender.sendMessage(torque_brake_proxy);

    return 0;
}        

