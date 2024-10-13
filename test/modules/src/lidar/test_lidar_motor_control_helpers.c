#include "lidar_motor_control_helpers.h"

#include "unity.h"

uint32_t xTaskGetTickCount() { return 0; }
void vTaskDelayUntil(const uint32_t ignore) {}

float calculateTimeToCompleteMove(float sourceAngle, float destinationAngle, uint32_t msPerSixtyDegrees);
uint16_t translateTargetAngleToServoAngle(uint16_t targetAngle, float servoBeltDriveRatio, float beltDriveLidarGearRatio);

void testCalculateTimeToMoveCalculatesCorrectTime()
{
    // Fixture
    uint16_t startingAngle = 45;
    uint16_t targetAngle = 90;
    uint16_t degressToMove = 45;
    uint16_t msPerSixtyDegrees = 5;
    uint16_t degreesPerMs = 60.0 / msPerSixtyDegrees;
    float expectedTime = degressToMove / degreesPerMs;

    // Test
    float actualTimeToCompleteMove = calculateTimeToCompleteMove(startingAngle, targetAngle, msPerSixtyDegrees);

    // Assert
    TEST_ASSERT_EQUAL(expectedTime, actualTimeToCompleteMove);
}

void testTranslateTargetAngleToServoAngleCalculatesCorrectAngle()
{
    // Fixture
    uint16_t targetAngle = 15;
    float servoBeltDriveRatio = 2.5;
    float beltDriveLidarGearRatio = 1.2;
    float expectedAngle = 7; //(targetAngle * beltDriveLidarGearRatio / servoBeltDriveRatio)

    // Test
    uint16_t actualAngle = translateTargetAngleToServoAngle(targetAngle, servoBeltDriveRatio, beltDriveLidarGearRatio);

    // Assert
    TEST_ASSERT_EQUAL(expectedAngle, actualAngle);
}