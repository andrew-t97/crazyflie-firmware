// Library for controlling the motor of the LiDAR

#pragma once

#include <stdint.h>
#include "param.h"

#define MILLISECONDS_PER_SIXTY_DEGREES 500
#define GEAR_RATIO 1.2121
#define BELT_DRIVE_RATIO 1.1
#define MIN_ANGLE ((180 - 90) / GEAR_RATIO)
#define MAX_ANGLE MIN_ANGLE + 90
#define STARTING_ANGLE 90 // TODO: Do checks of max and min possible angles

struct servo
{
    paramVarId_t servoAngleParamID;
    uint16_t currentAngle;

} typedef Servo;

/**
 * @brief Sets the angle of a servo motor.
 *
 * This function sets the angle of the specified servo motor to the target angle.
 *
 * @param servo The servo motor to set the angle for.
 * @param targetAngle The target angle to set for the servo motor.
 * @param waitForMove Flag indicating whether to wait for the servo motor to finish moving.
 *
 * @return The number of ticks to wait for the servo motor to finish moving.
 */
unsigned int setServoAngle(Servo const *servo, const uint16_t targetAngle, const bool waitForMove);

/**
 * @brief Initialises the LiDAR servo motor.
 *
 * This function initialises the LiDAR servo motor.
 *
 * @return A pointer to the initialised servo motor.
 */
Servo *initialiseLiDARServo();