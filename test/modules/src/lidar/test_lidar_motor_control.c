#include "lidar_motor_control.h"

#include "unity.h"
#include "FreeRTOS.h"
#include "freertosMocks.h"
#include "param.h"
#include "mock_system.h"
#include "lidar_motor_control_helpers.h"

uint16_t SERVO_TEST_ANGLE = 90;
int16_t FAIL_VALUE = -1;

// Mocks
uint16_t MOCK_PARAM_ID = 1;
uint16_t MOCK_INDEX = 2;
paramVarId_t paramGetVarId(const char *group, const char *name)
{
    paramVarId_t par = {.id = MOCK_PARAM_ID, .index = MOCK_INDEX};
    return par;
};
void paramSetInt(paramVarId_t varid, int valuei) { return; }
void vTaskDelayUntil(const uint32_t ignore) {}

// Tests

servo *getTestServo()
{
    servo *testServo = (servo *)malloc(sizeof(servo));
    testServo->currentAngle = SERVO_TEST_ANGLE;
    testServo->servoAngleParamID.id = MOCK_PARAM_ID;
    testServo->servoAngleParamID.index = MOCK_INDEX;

    return testServo;
}

void testThatSetLidarAngleFailsIfTargetAngleLargerThanMaxAngle()
{
    // Fixture
    servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE + 1;

    // Test
    int16_t ticksToWait = setLidarAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(FAIL_VALUE, ticksToWait);
}

void testThatSetLidarAngleFailsIfTargetAngleSmallerThanMinAngle()
{
    // Fixture
    servo *testServo = getTestServo();
    int16_t targetAngle = MIN_LIDAR_ANGLE - 1;

    // Test
    int16_t ticksToWait = setLidarAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(FAIL_VALUE, ticksToWait);
}

void testThatSetLidarAngleReturnsZeroWhenWaitingForServoToMove()
{
    // Fixture
    servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE / 2;

    // Test
    int16_t ticksToWait = setLidarAngle(testServo, targetAngle, true);

    // Assert
    TEST_ASSERT_EQUAL(0, ticksToWait);
}

void testThatSetLidarAngleReturnsCorrectTicksToWaitWhenNotWaitingForServo()
{
    // Fixture
    servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE;
    int16_t servoTargetAngle = translateLidarTargetAngleToServoAngle(targetAngle, BELT_DRIVE_RATIO, GEAR_RATIO, SERVO_CENTRE_ANGLE);

    uint32_t expectedTimeToComplete = (uint32_t)calculateTimeToCompleteMove(testServo->currentAngle, servoTargetAngle, MILLISECONDS_PER_SIXTY_DEGREES);
    int expectedTicks = M2T(expectedTimeToComplete);

    // Test
    int actualTicks = setLidarAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(expectedTicks, actualTicks);
}

void testThatInitialiseLiDARServoCreatesServoCorrectly()
{
    // Fixture
    uint16_t expectedParamID = MOCK_PARAM_ID;
    uint16_t expectedIndex = MOCK_INDEX;
    uint16_t expectedCurrentAngle = translateLidarTargetAngleToServoAngle(0, BELT_DRIVE_RATIO, GEAR_RATIO, SERVO_CENTRE_ANGLE);

    // Test
    servo *testServo = initialiseLiDARServo();

    // Assert
    TEST_ASSERT_EQUAL(expectedParamID, testServo->servoAngleParamID.id);
    TEST_ASSERT_EQUAL(expectedIndex, testServo->servoAngleParamID.index);
    TEST_ASSERT_EQUAL(expectedCurrentAngle, testServo->currentAngle);
}