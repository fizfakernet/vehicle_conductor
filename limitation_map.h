#pragma once

#include <utility>
#include <list>
#include "data_messages.h"

using namespace VehicleTypes;

struct Limitation
{
    enum ChangerType
    {
        invalid,
        fast,
        smooth,
        taskFast,
        taskSmooth
    } changerType;
    Limitation(variable start, speed minimum,speed maximum, ChangerType ct = fast, procent breakLim = 100);
    std::pair<speed,speed> speedLim;
    procent breakTask;
    variable startZone;

    bool operator<(const Limitation & a1);
};

class LimitationMap
{
public:
    ~LimitationMap() { limMap.clear();}; 
    Limitation* getCurentLimitation(variable pos);
    Limitation* getNextLimitation();
    void addLimitation(Limitation lim);
    void init();

    Limitation* nextLimitation(); // move curent element to one and return point to it
private:
    bool move(variable pos);
    std::list<Limitation> limMap;
    std::list<Limitation>::iterator curent;
};