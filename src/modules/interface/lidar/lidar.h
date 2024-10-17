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
    uint16_t front;
    uint16_t back;
    uint16_t left;
    uint16_t right;
} typedef lidarRanges;

lidarRangerLogIds *getRangerLogIds(void);

lidarRanges *getLidarRanges(lidarRangerLogIds *);