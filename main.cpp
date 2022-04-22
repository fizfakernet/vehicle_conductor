#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <iostream>
#include <thread>
#include "loop_thread.h"
#include "sender.h"
#include "reader.h"
#include "proxy.h"
#include "conductor.h"
#include "task_map.h"
#include "monitor.h"
#include "limitation_map.h"

using namespace std;

int main(int argc, char * argv[])
{

      Sender sender("127.0.0.1", 8080);  
      int s = sender.getSocket();
      Reader reader(s);
      Proxy<PositionTimestamp> input_proxy;
      Proxy<TorqueBrake> output_proxy;
      Monitor monitor(input_proxy);

      LimitationMap limitation_map;
      limitation_map.addLimitation(Limitation(0,0,25));
      limitation_map.addLimitation(Limitation(250,0,10));
      limitation_map.addLimitation(Limitation(350,0,0, Limitation::ChangerType::smooth) );
      limitation_map.addLimitation(Limitation(360,0,0));

      limitation_map.init();
      
      TaskLimitationMap taskMap(limitation_map);
      taskMap.init();
      
      ConductorFast conductor(taskMap, input_proxy, output_proxy, reader, sender);

      running = true;
      std::thread thrDrive(repeat, &conductor);
      std::thread thrShow(repeatMonitorShow, &monitor);

      getchar();
      running = false;
      thrDrive.join();  
      thrShow.join();  

      return 0;
}