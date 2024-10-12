#pragma once

#include "log.h"

struct lidarRangerLogIds_s
{
    logVarId_t front;
    logVarId_t back;
    logVarId_t left;
    logVarId_t right;
} typedef lidarRangerLogIds;

struct lidarRanges_s
{
    float front;
    float back;
    float left;
    float right;
} typedef lidarRanges;

lidarRangerLogIds * getRangerLogIds(void);

lidarRanges * getLidarRanges(lidarRangerLogIds *);