#pragma once

class TcpIpBase
{
public:
    bool isConnect(){return (0 <= s);}
    int getSocket(){return s;}
protected:
    int s; // socket
};