#pragma once

#include "reader.h"
#include "proxy.h"

class Monitor
{
    Monitor() = delete;
public:
    Monitor( Proxy<PositionTimestamp> &input_proxy_ );
    void print() const;
protected:
    Proxy<PositionTimestamp> &input_proxy;
};