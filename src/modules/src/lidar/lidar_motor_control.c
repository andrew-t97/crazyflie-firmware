
#include "FreeRTOS.h"
#include "task.h"
#include "param.h"
#include "debug.h"
#include "lidar_motor_control.h"
#include "lidar_motor_control_helpers.h"

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

int setLidarAngle(servo *servo, const int16_t lidarTargetAngle, const bool waitForServoToReachTarget)
{
    if (lidarTargetAngle > MAX_LIDAR_ANGLE)
    {
        DEBUG_PRINT("Lidar target angle too large - target angle: %d, max angle: %d\n", lidarTargetAngle, (int)MAX_LIDAR_ANGLE);
        return -1;
    }
    else if (lidarTargetAngle < MIN_LIDAR_ANGLE)
    {
        DEBUG_PRINT("Lidar target angle too small - target angle: %d, minimum angle: %d\n", lidarTargetAngle, (int)MIN_LIDAR_ANGLE);
        return -1;
    }

    uint16_t servoTargetAngle = translateLidarTargetAngleToServoAngle(lidarTargetAngle, BELT_DRIVE_RATIO, GEAR_RATIO, SERVO_CENTRE_ANGLE);

    DEBUG_PRINT("Moving LiDAR angle to %d degrees\n", lidarTargetAngle);
    DEBUG_PRINT("Moving servo to translated target angle of %d degrees\n", servoTargetAngle);
    paramSetInt(servo->servoAngleParamID, servoTargetAngle);

    int ticksToWait = 0;
    uint32_t timeToCompleteMoveMs = (uint32_t)calculateTimeToCompleteMove(servo->currentAngle, servoTargetAngle, MILLISECONDS_PER_SIXTY_DEGREES);
    if (waitForServoToReachTarget)
    {
        DEBUG_PRINT("Waiting for LiDAR servo to move to %d degrees\n", lidarTargetAngle);
        waitForMove(timeToCompleteMoveMs);
        ticksToWait = 0;
        DEBUG_PRINT("LiDAR servo moved to %d degrees\n", lidarTargetAngle);
    }
    else
    {
        ticksToWait = M2T(timeToCompleteMoveMs);
    }

    servo->currentAngle = servoTargetAngle;
    return ticksToWait;
}

servo *initialiseLiDARServo()
{
    servo *lidarServo = (servo *)malloc(sizeof(servo));
    if (lidarServo == NULL)
    {
        DEBUG_PRINT("Failed to allocate memory for LiDAR servo\n");
        return NULL;
    }

    int16_t initialAngle = 0;

    /* Setting the servo current angle to zero so that we wait the max time, ensuring we always wait long
     enough for the move to complete */
    lidarServo->servoAngleParamID = paramGetVarId("servo", "servoAngle");
    lidarServo->currentAngle = 0;

    DEBUG_PRINT("LiDAR servo set angle ID: %d\n", (int)lidarServo->servoAngleParamID.id);

    setLidarAngle(lidarServo, initialAngle, true);

    return lidarServo;
}
