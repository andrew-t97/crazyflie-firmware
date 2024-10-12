#include "lidar.h"
#include "debug.h"

#include <stdlib.h>
#include <stddef.h>

lidarRangerLogIds *getRangerLogIds()
{
    lidarRangerLogIds *rangerLogIds = (lidarRangerLogIds *)malloc(sizeof(lidarRangerLogIds));
    if (rangerLogIds == NULL)
    {
        DEBUG_PRINT("Failed to allocate memory for lidar ranger log IDs\n");
        return NULL;
    }

    rangerLogIds->front = logGetVarId("ranger", "front");
    rangerLogIds->back = logGetVarId("ranger", "back");
    rangerLogIds->left = logGetVarId("ranger", "left");
    rangerLogIds->right = logGetVarId("ranger", "right");

    return rangerLogIds;
}

lidarRanges *getLidarRanges(lidarRangerLogIds *rangerLogIds)
{
    lidarRanges *ranges = (lidarRanges *)malloc(sizeof(lidarRanges));
    if (ranges == NULL)
    {
        DEBUG_PRINT("Failed to allocate memory for lidar ranges\n");
        return NULL;
    }

    ranges->front = (float)logGetVarId("range", "front");
    ranges->back = (float)logGetVarId("range", "back");
    ranges->left = (float)logGetVarId("range", "left");
    ranges->right = (float)logGetVarId("range", "right");

    DEBUG_PRINT("Got LiDAR ranges! - Front: %.3f, Back: %.3f, Left %.3f, Right, %.3f",
                (double)ranges->front,
                (double)ranges->back,
                (double)ranges->left,
                (double)ranges->right);

    return ranges;
}