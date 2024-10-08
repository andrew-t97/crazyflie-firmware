#include "FreeRTOS.h"
#include "task.h"

#include "system.h"
#include "debug.h"
#include "config.h"
#include "static_mem.h"
#include "param.h"
#include "debug.h"
#include "queue.h"
#include "log.h"

#include <stdio.h>
#include <math.h>

#define RATE_1000_HZ 500
#define MAX_ANGLE 157
#define MIN_ANGLE 22
#define RANGE_WAIT_TIME_MS 50

static void servoSweepTask(void *);
STATIC_MEM_TASK_ALLOC(servoSweepTask, SERVO_SWEEP_TASK_STACKSIZE);

static bool isInit = false;
static paramVarId_t servoAngleID;
static uint16_t currentAngle;
static uint32_t lastWakeTime;
static logVarId_t idLeft;
static logVarId_t idRight;
static logVarId_t idFront;
static logVarId_t idBack;
static uint16_t current_left_range;
static uint16_t current_right_range;
static uint16_t current_front_range;
static uint16_t current_back_range;

void servoSweepTaskInit()
{
    STATIC_MEM_TASK_CREATE(servoSweepTask, servoSweepTask, SERVO_SWEEP_TASK_NAME, NULL, SERVO_SWEEP_TASK_PRI);

    currentAngle = 90;
    isInit = true;
    DEBUG_PRINT("Successfully initialised servo sweep task\n");
}

bool servoSweepTaskTest()
{
    return isInit;
}

static void logRanges()
{
    lastWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime, M2T(RANGE_WAIT_TIME_MS));

    current_left_range = logGetUint(idLeft);
    current_right_range = logGetUint(idRight);
    current_front_range = logGetUint(idFront);
    current_back_range = logGetUint(idBack);

    DEBUG_PRINT("Angle: %d, Front range: %d, Right range: %d, Left range: %d, Back range: %d", currentAngle, current_front_range, current_right_range, current_left_range, current_back_range);
}

static void servoSweepTask(void *parameters)
{
    DEBUG_PRINT("Servo sweep task started\n");

    // unsigned int ticksToWait;

    systemWaitStart();

    servoAngleID = paramGetVarId("servo", "servoAngle");
    DEBUG_PRINT("Servo Angle ID: %d\n", (int)servoAngleID.id);

    idLeft = logGetVarId("range", "left");
    idRight = logGetVarId("range", "right");
    idFront = logGetVarId("range", "front");
    idBack = logGetVarId("range", "back");

    while (1)
    {

        lastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&lastWakeTime, F2T(RATE_1000_HZ));

        for (int i = MIN_ANGLE; i < MAX_ANGLE; ++i)
        {
            // ticksToWait = setServoAngle(i);
            // waitForMove(ticksToWait);
            logRanges();
        }

        for (int i = MAX_ANGLE; i > MIN_ANGLE; --i)
        {
            // ticksToWait = setServoAngle(i);
            // waitForMove(ticksToWait);
            logRanges();
        }
    }
}