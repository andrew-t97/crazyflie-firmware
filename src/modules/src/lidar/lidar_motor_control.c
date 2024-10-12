
#include "FreeRTOS.h"
#include "task.h"
#include "param.h"
#include "debug.h"
#include "lidar_motor_control.h"
#include "lidar_motor_control_helpers.h"

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

int setServoAngle(Servo *servo, const uint16_t targetAngle, const bool waitForServoToReachTarget)
{

    if (targetAngle > MAX_ANGLE)
    {
        DEBUG_PRINT("Target angle too large - target angle: %d, max angle: %.3f", targetAngle, (double)MAX_ANGLE);
        return -1;
    }
    else if (targetAngle < MIN_ANGLE)
    {
        DEBUG_PRINT("Target angle too small - target angle: %d, minimum angle: %.3f", targetAngle, (double)MIN_ANGLE);
        return -1;
    }

    uint16_t servoTargetAngle = translateTargetAngleToServoAngle(targetAngle, BELT_DRIVE_RATIO, GEAR_RATIO);

    DEBUG_PRINT("Setting LiDAR angle to %d degrees\n", targetAngle);
    DEBUG_PRINT("Moving servo angle to %d  degrees\n", servoTargetAngle);
    paramSetInt(servo->servoAngleParamID, servoTargetAngle);

    int ticksToWait = 0;
    uint32_t timeToCompleteMoveMs = (uint32_t)calculateTimeToCompleteMove(servo->currentAngle, targetAngle, MILLISECONDS_PER_SIXTY_DEGREES);
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
