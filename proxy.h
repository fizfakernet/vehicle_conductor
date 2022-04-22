#pragma once

#include "proxy_base.h"

using namespace VehicleTypes;

template<typename T>
class Proxy : public ProxyBase
{
public:
    void setMessage(const T mess);
    T getMessage() const;
private:
    T message;
};

class PositionTimestampProxy : public Proxy<PositionTimestamp>{};

template <typename T>
void Proxy<T>::setMessage(const T mess)
{
    lock();
    message = mess;
    unlock();
}

template <typename T>
T Proxy<T>::getMessage() const
{
    T mess;
    lock();
    mess = message;
    unlock();
    return mess;
}