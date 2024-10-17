#include "lidar.h"
#include "debug.h"
#include "log.h"

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

    ranges->front = logGetUint(rangerLogIds->front);
    ranges->back = logGetUint(rangerLogIds->back);
    ranges->left = logGetUint(rangerLogIds->left);
    ranges->right = logGetUint(rangerLogIds->right);

    DEBUG_PRINT("Got LiDAR ranges! - Front: %d, Back: %d, Left: %d, Right: %d\n",
                ranges->front,
                ranges->back,
                ranges->left,
                ranges->right);

    return ranges;
}