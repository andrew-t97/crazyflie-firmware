
#include "lidar_motor_control_helpers.h"

static float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle, uint32_t msPerSixtyDegrees)
{
    float angleDifference = fabs(destinationAngle - sourceAngle);
    float degreesPerMs = 60.0 / msPerSixtyDegrees;
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

static uint16_t translateTargetAngleToServoAngle(uint16_t targetAngle, float servoBeltDriveRatio, float beltDriveLidarGearRatio)
{
    return targetAngle * beltDriveLidarGearRatio / servoBeltDriveRatio;
}
