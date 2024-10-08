#include "lidar_motor_control.h"
#include "stddef.h"

static float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle)
{
    float angleDifference = fabs(destinationAngle - sourceAngle);
    float degreesPerMs = 60.0 / MILLISECONDS_PER_SIXTY_DEGREES;
    float timeMs = angleDifference / degreesPerMs;

    return timeMs;
}

static void waitForMove(uint32_t ticksToWait)
{
    if (ticksToWait == 0)
    {
        return;
    }

    uint32_t currentTime = xTaskGetTickCount();
    vTaskDelayUntil(&currentTime, ticksToWait);
}

unsigned int setServoAngle(Servo const *servo, const uint16_t targetAngle, const bool waitForServoToReachTarget)
{
    DEBUG_PRINT("Setting LiDAR servo to angle %d\n", targetAngle);
    paramSetInt(servo->servoAngleParamID, targetAngle);

    int ticksToWait = 0;
    uint32_t timeToCompleteMoveMs = (uint32_t)calculateTimeToCompleteMove(servo->currentAngle, targetAngle);
    if (waitForServoToReachTarget)
    {
        DEBUG_PRINT("Waiting for LiDAR servo to move to angle %d\n", targetAngle);
        waitForMove(timeToCompleteMoveMs);
        ticksToWait = 0;
        DEBUG_PRINT("LiDAR servo moved to angle %d!\n", targetAngle);
    }
    else
    {
        ticksToWait = M2T(timeToCompleteMoveMs);
    }

    servo->currentAngle = targetAngle;
    return ticksToWait;
}

Servo *initialiseLiDARServo()
{
    Servo *servo = (Servo *)malloc(sizeof(Servo));
    if (servo == NULL)
    {
        DEBUG_PRINT("Failed to allocate memory for LiDAR servo\n");
        return NULL;
    }

    uint16_t initialAngle = 90;

    /* Setting the current angle to zero so that we wait the max time, ensuring we always wait long
     enough for the move to complete */
    servo->servoAngleParamID = paramGetVarId("servo", "servoAngle");
    servo->currentAngle = 0;

    DEBUG_PRINT("LiDAR Servo Angle ID: %d\n", (int)servo->servoAngleParamID.id);

    setServoAngle(servo, initialAngle, true);

    return servo;
}
