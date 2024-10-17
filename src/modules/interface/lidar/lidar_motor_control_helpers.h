#pragma once

#include <stdint.h>

/**
 * @brief Calculates the time required to complete a move from the source angle to the destination
 * angle.
 *
 * This function computes the number of milliseconds needed for the servo to move from the given
 * source angle to the destination angle.
 *
 * @param sourceAngle The starting angle of the movement in degrees.
 * @param destinationAngle The ending angle of the movement in degrees.
 * @param msPerSixtyDegrees The number of milliseconds required by the drive servo to move sixty
 * degrees
 * @return The time required to complete the move in millisenconds.
 */
float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle, uint32_t msPerSixtyDegrees);

/** * @brief Waits for a specified number of ticks.
 *
 * This function halts the execution for the number of ticks provided to allow for the
 * servo to move to its requested angle
 *
 * @param ticksToWait The number of ticks to wait.
 */
void waitForMove(uint32_t ticksToWait);
/**
 * @brief Translates a target angle to a corresponding servo angle.
 *
 * This function takes a target angle and applies the belt drive and gear ratios to calculate
 * what angle we should move the driving servo motor to.
 *
 * @param targetAngle The target angle in degrees.
 * @param servoBeltDriveRatio The ratio between the circumference of the servo and the belt drive pulley
 * @param beltDriveLidarGearRatio The ratio between the belt drive gear and the lidar gear
 * @return The corresponding servo angle.
 */
uint16_t translateLidarTargetAngleToServoAngle(int16_t targetAngle,
                                               float servoBeltDriveRatio,
                                               float beltDriveLidarGearRatio,
                                               uint16_t servoCentreAngle);
