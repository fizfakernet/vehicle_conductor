#pragma once

#include "limitation_map.h"
#include "proxy.h"
#include "sender.h"
#include "reader.h"

using namespace VehicleTypes;

class ConductorBase
{
public:
    ConductorBase( LimitationMap &lm,
        Proxy<PositionTimestamp> &pos_proxy_, 
        Proxy<TorqueBrake> &torque_brake_proxy_,
        Reader &reader_,
        Sender &sender_ );
    virtual int drive() = 0;
protected:
    LimitationMap limitation_map;
    Proxy<PositionTimestamp> &pos_proxy;
    Proxy<TorqueBrake> &torque_brake_proxy;
    Reader &reader;
    Sender &sender;
};

class ConductorFast : public ConductorBase
{
public:
    ConductorFast( LimitationMap &lm,
        Proxy<PositionTimestamp> &pos_proxy_, 
        Proxy<TorqueBrake> &torque_brake_proxy_,
        Reader &reader_,
        Sender &sender_);
    int drive() override;
};

void setSpeed(PositionTimestamp &curState, speed &v);

