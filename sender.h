#pragma once

#include <stdint.h>
#include "data_messages.h"
#include "proxy.h"
#include "tcpip_base.h"

class Sender : public TcpIpBase
{
public:
    Sender(const char *cp, uint16_t hostshort);
    ~Sender();
    int connectTCPIP(const char *cp, uint16_t hostshort);
    int disconnectTCPIP();
    int sendMessage(const Proxy<TorqueBrake> &proxy);
    int sendMessage(const char *buffer);
};