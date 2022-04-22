#pragma once

#include "limitation_map.h"

class TaskLimitationMap : public LimitationMap
{
public:
    TaskLimitationMap(LimitationMap &limitationMap);
    TaskLimitationMap() = delete;
    TaskLimitationMap(TaskLimitationMap&) = delete;
};

