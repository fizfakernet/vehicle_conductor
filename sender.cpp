#include "sender.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <string.h>
#include <iostream>

using namespace VehicleTypes;

Sender::Sender(const char *cp, uint16_t hostshort)
{
    s = connectTCPIP(cp, hostshort);
}
Sender::~Sender()
{
    if(isConnect()) disconnectTCPIP();
}

int Sender::connectTCPIP(const char *cp, uint16_t hostshort)
{
      s = socket( AF_INET, SOCK_STREAM, 0 );
      if(s < 0)
      {
              std::cerr << "Error calling socket\n" ;
              return -1;
      }

      struct sockaddr_in peer;
      peer.sin_family = AF_INET;
      peer.sin_port = htons( hostshort );
      peer.sin_addr.s_addr = inet_addr( cp );
      int result = connect( s, ( struct sockaddr * )&peer, sizeof( peer ) );
      if( result )
      {
              std::cerr << "Error calling connect\n" ;
              return -2;
      }
      return s;
}

int Sender::disconnectTCPIP()
{
    int ret = shutdown(s, 1);
    if( 0 > ret ) s = -50;
    return ret;
}

int Sender::sendMessage(const Proxy<TorqueBrake> &proxy)
{
    TorqueBrake tb = proxy.getMessage();
    char buffer[256];
    sprintf(buffer, "T:%d:B:%d",tb.torque,tb.brake);
    sendMessage(buffer);
    return 0;
}
#include <iostream>
int Sender::sendMessage(const char *buffer)
{
    int len = strlen(buffer);
    int result = send( s, buffer, len, 0);
    if( result <= 0 )
    {
        std::cerr << "Error calling send\n" ;
        return -1;
    }
    return result;
}
