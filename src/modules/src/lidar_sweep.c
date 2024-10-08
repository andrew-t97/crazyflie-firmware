#include "FreeRTOS.h"
#include "task.h"
#include "config.h"
#include "static_mem.h"
#include "debug.h"
#include "log.h"
#include <stdlib.h>

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

static int currentAngle;
static bool isInit;

static void lidarSweepTask(void *);

static lidarRangerLogIds *getRangerLogIds()
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

static lidarRanges *getLidarRanges(lidarRangerLogIds *rangerLogIds)
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

    DEBUG_PRINT("Got LiDAR ranges! - Front: %.3f, Back: %.3f, Left %.3f, Right, %.3f", ranges->front, ranges->back, ranges->left, ranges->right);

    return ranges;
}

STATIC_MEM_TASK_ALLOC(lidarSweepTask, LIDAR_SWEEP_TASK_STACKSIZE);

void lidarSweepTaskInit()
{
    STATIC_MEM_TASK_CREATE(lidarSweepTask, lidarSweepTask, SERVO_SWEEP_TASK_NAME, NULL, SERVO_SWEEP_TASK_PRI);

    currentAngle = 90;
    isInit = true;
    DEBUG_PRINT("Successfully initialised lidar sweep task\n");
}

bool lidarSweepTaskTest()
{
    return isInit;
}

static void lidarSweepTask(void *parameters)
{
    return;
}