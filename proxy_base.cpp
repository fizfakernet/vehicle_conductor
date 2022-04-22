#include "proxy_base.h"

void ProxyBase::lock() const
{
    mut.lock();
}

void ProxyBase::unlock() const
{
    mut.unlock();
}