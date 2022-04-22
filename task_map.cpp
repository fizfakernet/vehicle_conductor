#include "task_map.h"
#include "regulator_speed.h"

#include <iostream>

TaskLimitationMap::TaskLimitationMap(LimitationMap &limitationMap)
{
    limitationMap.init();
    Limitation* curLim = limitationMap.getCurentLimitation(0);
    speed prevHighLimit = 0;

    for(; nullptr != curLim; curLim = limitationMap.nextLimitation() )
    {
        if( curLim->speedLim.second > prevHighLimit ) // limit softer
        {
            addLimitation( *curLim );
        }
        else // limit harder
        {
            variable start;
            Limitation::ChangerType chType = Limitation::ChangerType::invalid;
            procent breakTask = 100;

            switch( curLim->changerType )
            {
                case Limitation::ChangerType::fast:
                    start = curLim->startZone - RegulatorSpeed::breakSpace(prevHighLimit, curLim->speedLim.second);
                    chType = Limitation::ChangerType::taskFast;
                    break;
                case Limitation::ChangerType::smooth:
                
                    Limitation* next = limitationMap.getNextLimitation();
                    if( nullptr == next ) 
                    {
                        chType = Limitation::ChangerType::invalid;
                    }
                    else
                    {
                        variable s = next->startZone - curLim->startZone;
                        start = curLim->startZone ;
                        chType = Limitation::ChangerType::taskSmooth;
                        breakTask = RegulatorSpeed::breakSmooth(prevHighLimit, curLim->speedLim.second, s);
                    }
                    break;
            }

            addLimitation( 
                Limitation(
                    start,
                    curLim->speedLim.first,
                    curLim->speedLim.second,
                    chType,
                    breakTask
                    ) 
                );
        }
        prevHighLimit = curLim->speedLim.second;
    }
    init();
}