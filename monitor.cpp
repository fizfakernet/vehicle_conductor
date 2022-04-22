#include "monitor.h"
#include <iostream>

using namespace std;

Monitor::Monitor( Proxy<PositionTimestamp> &input_proxy_ ) :
input_proxy{input_proxy_}
{
}

void Monitor::print() const
{
    PositionTimestamp message = input_proxy.getMessage();
    if( message.isValid() )
    {
        cout << "X = " << message.position 
            << " T = " << message.time
            << " v = " << message.v 
            << endl;
    }
    else if( message.positionValid && message.timeValid )
    {
        cout << "X = " << message.position 
            << " T = " << message.time
            << endl;
    }
}