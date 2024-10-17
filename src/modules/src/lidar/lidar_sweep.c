#include "FreeRTOS.h"
#include "task.h"
#include "config.h"
#include "static_mem.h"
#include "debug.h"
#include "log.h"
#include <stdlib.h>

static int currentAngle;
static bool isInit;

static void lidarSweepTask(void *);

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
    // TODO: Implement this
    return;
}