#include "FreeRTOS.h"
#include "task.h"

#include "lidar_motor_control_helpers.h"
#include <math.h>

float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle, uint32_t msPerSixtyDegrees)
{
    float angleDifference = fabs(destinationAngle - sourceAngle);
    float degreesPerMs = 60.0 / msPerSixtyDegrees;
    float timeMs = angleDifference / degreesPerMs;

    return timeMs;
}

void waitForMove(uint32_t ticksToWait)
{
    if (ticksToWait == 0)
    {
        return;
    }

    uint32_t currentTime = xTaskGetTickCount();
    vTaskDelayUntil(&currentTime, ticksToWait);
}

uint16_t translateTargetAngleToServoAngle(int16_t targetAngle,
                                          float servoBeltDriveRatio,
                                          float beltDriveLidarGearRatio,
                                          uint16_t servoCentreAngle)
{
    return (targetAngle + servoCentreAngle) / servoBeltDriveRatio * beltDriveLidarGearRatio;
}
