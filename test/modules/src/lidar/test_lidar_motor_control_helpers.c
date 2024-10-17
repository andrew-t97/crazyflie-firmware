#include "lidar_motor_control_helpers.h"

#include "unity.h"

// Mocks

uint32_t xTaskGetTickCount() { return 0; }
void vTaskDelayUntil(const uint32_t ignore) {}

// Tests

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
    uint16_t servoCentreAngle = 90;
    float servoBeltDriveRatio = 1.2;
    float beltDriveLidarGearRatio = 1.5;
    float expectedAngle = 131.25; // (targetAngle + servoCentreAngle) / servoBeltDriveRatio * beltDriveLidarGearRatio

    // Test
    uint16_t actualAngle = translateLidarTargetAngleToServoAngle(targetAngle, servoBeltDriveRatio, beltDriveLidarGearRatio, servoCentreAngle);

    // Assert
    TEST_ASSERT_EQUAL(expectedAngle, actualAngle);
}