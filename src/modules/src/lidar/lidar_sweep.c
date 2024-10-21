#include "FreeRTOS.h"
#include "task.h"
#include "config.h"
#include "static_mem.h"
#include "debug.h"
#include "log.h"
#include "lidar_motor_control.h"
#include "lidar.h"

#include <stdlib.h>

static int currentAngle;
static bool isInit;

static void lidarSweepTask(void *);

#define SWEEP_RANGE 90
#define MIN_SWEEP_ANGLE ((int)(SWEEP_RANGE / -2))
#define MAX_SWEEP_ANGLE ((int)(SWEEP_RANGE / -2))
#define LIDAR_FREQUENCY_HZ 50

static int lidarAngle;
static lidarRanges *ranges;

STATIC_MEM_TASK_ALLOC(lidarSweepTask, LIDAR_SWEEP_TASK_STACKSIZE);

void lidarSweepTaskInit()
{
    STATIC_MEM_TASK_CREATE(lidarSweepTask, lidarSweepTask, LIDAR_SWEEP_TASK_NAME, NULL, LIDAR_SWEEP_TASK_PRI);

    ranges = (lidarRanges *)malloc(sizeof(lidarRanges));
    if (ranges == NULL)
    {
        DEBUG_PRINT("Failed to allocate memory for lidar ranges\n");
        return NULL;
    }

    currentAngle = 90;
    isInit = true;
    DEBUG_PRINT("Successfully initialised lidar sweep task\n");
}

bool lidarSweepTaskTest()
{
    return isInit;
}

static lidarRanges *getRangesAtAngle(servo *lidarServo, lidarRangerLogIds *rangerLogIds, int16_t targetAngle)
{
    // Move to angle
    setLidarAngle(lidarServo, targetAngle, true);

    // Wait for lidar to get fresh values
    uint32_t lastWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime, F2T(LIDAR_FREQUENCY_HZ));

    // Get ranges from multi-ranger
    getLidarRanges(rangerLogIds, ranges);

    return ranges;
}

static void lidarSweep(int16_t startAngle, int16_t endAngle, int16_t step, servo *lidarServo, lidarRangerLogIds *lidarLogIds, lidarRanges *rangesOut)
{
    for (int16_t currentAngle = startAngle; currentAngle != endAngle; currentAngle += step)
    {
        lidarRanges *ranges = getRangesAtAngle(lidarServo, lidarLogIds, currentAngle);
        // TODO: Implement logging
    }
}

static void lidarSweepTask(void *parameters)
{
    DEBUG_PRINT("Lidar sweep task started\n");

    systemWaitStart();

    servo *lidarServo = initialiseLiDARServo();
    lidarRangerLogIds *lidarLogIds = getRangerLogIds();

    while (true)
    {
        // Sweep forwards
        lidarSweep(MIN_SWEEP_ANGLE, MAX_SWEEP_ANGLE + 1, 1, lidarServo, lidarLogIds, ranges);

        // Sweep backwards
        lidarSweep(MAX_SWEEP_ANGLE, MIN_SWEEP_ANGLE - 1, -1, lidarServo, lidarLogIds, ranges);
    }

    return;
}