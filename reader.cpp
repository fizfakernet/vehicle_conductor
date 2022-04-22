#include "reader.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>
#include <string.h>

using namespace std;

Reader::Reader(int sock)
{
    s = sock;
    tv.tv_sec = 0;
    tv.tv_usec = 500000;
    connectTCPIP(s);
    prevMessage.positionValid = false;
    prevMessage.timeValid = false;
    prevMessage.vValid = false;
}
Reader::~Reader()
{
    if( isConnect() )    disconnectTCPIP();
}
int Reader::connectTCPIP(int sock)
{
    FD_ZERO( &allreads );
    FD_SET( 0, &allreads );
    FD_SET( s, &allreads );
    return 0;
}
int Reader::disconnectTCPIP()
{
    return 0;
}
int Reader::readMessage(Proxy<PositionTimestamp> &proxy)
{
    int ret = 0;
    char bufferRaw[BUFFER_SIZE];
    char bufferFilt[255];
    PositionTimestamp message;

    int len = readMessage(bufferRaw, BUFFER_SIZE);
    if(len < 1) return len;
    charBuffer.add(bufferRaw, (size_t)len );
    if( charBuffer.getMessage(bufferFilt) < 1 ) return -1;

    ret = parse(bufferFilt, message);
    if( 0 == ret ) proxy.setMessage(message);
    return ret;
}
int Reader::readMessage(char *buffer,size_t len)
{
    int result = 0;
    if( (NULL == buffer) || (1 > len) ) return -1;

    readmask = allreads;
    if( select(s + 1, &readmask, NULL, NULL, &tv ) <= 0 )
    {
        cerr << "Error calling select";
        return -2;
    }
    if( FD_ISSET( s, &readmask ) )
    {
        result = recv( s, buffer, BUFFER_SIZE , 0 );
        if( result < 0 )
        {
            cerr << "Error calling recv";
            return -3;
        }
        if( result == 0 )
        {
            cerr << "Server disconnected";
            return -4;
        }
    }
    if( FD_ISSET( 0, &readmask ) )
    {
        cerr << "No server response" ;
        return -5;
    }
    return result;
}
int Reader::parse(const char *buffer, PositionTimestamp &message)
{
    variable pos = -1;
    timestamp t = 1;

    int result = sscanf(buffer , "X:%f:T:%lld", &pos, &t);
    switch(result)
    {
    case 2:
        message.position = pos;
        message.time = t;
        message.positionValid = true;
        message.timeValid = true;
        message.vCalculate(prevMessage);
        prevMessage = message;
        break;
    case 1:
        message.position = pos;
        message.positionValid = true;
        message.timeValid = false;
        message.vValid = false;
        break;
    default:
        cerr << "Bad format input string: " << buffer;
        return -1;
        break;
    }
    return 0;
}

int Reader::findMessage(const char *buffer, size_t length)
{
    if(!buffer) return -2;

    if(length < 1) return -1;
    
    size_t p = length - 1;
    for(; p > 0; p--)
    {
        if('X' == buffer[p]) return p;
    }
    return -1;
}