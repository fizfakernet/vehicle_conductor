#pragma once

#include <stdint.h>
#include <stddef.h>
#include <sys/types.h>
#include "data_messages.h"
#include "proxy.h"
#include "tcpip_base.h"
#include "char_buffer.h"
#include "constants.h"

using namespace VehicleTypes;

class Reader : public TcpIpBase
{
public:
    Reader(int sock);
    ~Reader();
    int connectTCPIP(int sock);
    int disconnectTCPIP();
    int readMessage(Proxy<PositionTimestamp> &proxy);
    int readMessage(char *buffer,size_t len);
private:
    int parse(const char *buffer, PositionTimestamp &message);
    int findMessage(const char *buffer, size_t length = 0); // find substring at fomat "X:<number>:T:<number>" return position of start

    fd_set readmask;
    fd_set allreads;
    struct timeval tv;
    PositionTimestamp prevMessage;
    CharBuffer charBuffer;
};