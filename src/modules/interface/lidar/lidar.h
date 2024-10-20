#pragma once

#include "log.h"

/*
Struct containing the log ids for the ranges of each point on the multi-ranger
*/
struct lidarRangerLogIds_s
{
    logVarId_t front;
    logVarId_t back;
    logVarId_t left;
    logVarId_t right;
} typedef lidarRangerLogIds;

/*
Struct containing the ranges of each direction of the multi-ranger
*/
struct lidarRanges_s
{
    uint16_t front;
    uint16_t back;
    uint16_t left;
    uint16_t right;
} typedef lidarRanges;

/**
 * @brief Retrieves the log IDs for the multi-ranger.
 *
 * This function returns a pointer to a lidarRangerLogIds struct containing the log IDs
 * associated with the multi-ranger.
 *
 * @return Pointer to a lidarRangerLogIds struct containing the multi-ranger's log IDs.
 */
lidarRangerLogIds *getRangerLogIds(void);

/**
 * @brief Retrieves the current ranges of each direction on the multi-ranger
 *
 * This function returns a pointer to a lidarRanges struct containing the ranges in each direction
 * of the multi-ranger.
 *
 * @param rangerLogIds The log ids of each direction of the multi-ranger.
 * @return Pointer to a lidarRanges struct containing the multi-ranger's current ranges.
 */
lidarRanges *getLidarRanges(lidarRangerLogIds *rangerLogIds);