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

// TODO: Make it so you can provide the ouput range struct for this
void getLidarRanges(lidarRangerLogIds *rangerLogIds, lidarRanges *rangeOut)
{
    rangeOut->front = logGetUint(rangerLogIds->front);
    rangeOut->back = logGetUint(rangerLogIds->back);
    rangeOut->left = logGetUint(rangerLogIds->left);
    rangeOut->right = logGetUint(rangerLogIds->right);

    DEBUG_PRINT("Got LiDAR ranges! - Front: %d, Back: %d, Left: %d, Right: %d\n",
                rangeOut->front,
                rangeOut->back,
                rangeOut->left,
                rangeOut->right);
}