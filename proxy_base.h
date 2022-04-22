#pragma once

#include <mutex>

class ProxyBase
{
protected:
    void lock() const;
    void unlock() const;
private:
    mutable std::mutex mut;
};
