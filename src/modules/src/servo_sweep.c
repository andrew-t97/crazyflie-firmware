#include "FreeRTOS.h"
#include "task.h"

#include "system.h"
#include "debug.h"
#include "config.h"
#include "static_mem.h"
#include "param.h"
#include "debug.h"
#include "queue.h"

#include <stdio.h>

#define RATE_1000_HZ 500
#define MILLISECONDS_PER_SIXTY_DEGREES 100

static void servoSweepTask(void *);
STATIC_MEM_TASK_ALLOC(servoSweepTask, SERVO_SWEEP_TASK_STACKSIZE);

static bool isInit = false;
static paramVarId_t servoAngleID;
static uint16_t currentAngle;
static uint32_t lastWakeTime;

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

static float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle)
{
    float angleDifference = fabs(destinationAngle - sourceAngle);
    float degreesPerMs = 60.0 / MILLISECONDS_PER_SIXTY_DEGREES;
    float timeMs = angleDifference / degreesPerMs;

    return timeMs;
}

static unsigned int setServoAngle(uint16_t angle)
{
    DEBUG_PRINT("Setting servo to angle %d\n", angle);
    paramSetInt(servoAngleID, angle);
    uint32_t timeToCompleteMoveMs = (uint32_t)calculateTimeToCompleteMove(currentAngle, angle);
    currentAngle = angle;
    return M2T(timeToCompleteMoveMs);
}

static void waitForMove(uint32_t ticksToWait)
{
    if (ticksToWait == 0)
    {
        return;
    }

    lastWakeTime = xTaskGetTickCount();
    vTaskDelayUntil(&lastWakeTime, ticksToWait);
}

static void servoSweepTask(void *parameters)
{
    DEBUG_PRINT("Servo sweep task started\n");

    unsigned int ticksToWait;

    systemWaitStart();

    servoAngleID = paramGetVarId("servo", "servoAngle");
    DEBUG_PRINT("Servo Angle ID: %d\n", (int)servoAngleID.id);

    while (1)
    {

        lastWakeTime = xTaskGetTickCount();
        vTaskDelayUntil(&lastWakeTime, F2T(RATE_1000_HZ));

        for (int i = 45; i < 135; ++i)
        {
            ticksToWait = setServoAngle(i);
            waitForMove(ticksToWait);
        }

        for (int i = 135; i > 45; --i)
        {
            ticksToWait = setServoAngle(i);
            waitForMove(ticksToWait);
        }
    }
}