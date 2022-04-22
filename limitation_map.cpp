#include "limitation_map.h"

Limitation::Limitation(variable start, speed minimum,speed maximum, ChangerType ct , procent breakLim)
{ 
    startZone = start;
    speedLim.first = minimum; 
    speedLim.second = maximum;
    changerType = ct;
    breakTask = breakLim;
}

bool Limitation::operator<(const Limitation & a1)
{ 
    return ( startZone < a1.startZone ); 
}

Limitation* LimitationMap::getCurentLimitation(variable pos)
{
    while(move(pos) );
    if( limMap.end() == curent) return nullptr;
    return &(*curent);
}

Limitation* LimitationMap::getNextLimitation()
{
    if( limMap.end() == curent) return nullptr;
    std::list<Limitation>::iterator next = std::next( curent );
    if( limMap.end() == next) return nullptr;
    return &(*next);
}

Limitation* LimitationMap::nextLimitation()
{
    if( limMap.end() == curent) return nullptr;

    variable aldPos = (*curent).startZone;
    curent++;
    if( aldPos > (*curent).startZone ) 
    {
        curent = limMap.end(); 
        return nullptr;
    }

    if( limMap.end() == curent) return nullptr;

    return &(*curent);
}

bool LimitationMap::move(variable pos)
{
    if( limMap.empty() ) return false;
    if( limMap.end() == curent) return false;

    auto next = std::next(curent);
    if( limMap.end() == next) return false;
    if( ( (*next).startZone < (*curent).startZone ) ) return false;
    if( (*next).startZone > pos ) return false;

    curent = next;

    return true;
}

void LimitationMap::addLimitation(Limitation lim)
{
    limMap.push_back(lim);
}

void LimitationMap::init()
{ 
    if( limMap.empty() ) return;
    curent = limMap.begin(); 
};