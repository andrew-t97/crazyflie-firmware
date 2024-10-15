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

Servo *getTestServo()
{
    Servo *servo = (Servo *)malloc(sizeof(Servo));
    servo->currentAngle = SERVO_TEST_ANGLE;
    servo->servoAngleParamID.id = MOCK_PARAM_ID;
    servo->servoAngleParamID.index = MOCK_INDEX;

    return servo;
}

void testThatSetServoAngleFailsIfTargetAngleLargerThanMaxAngle()
{
    // Fixture
    Servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE + 1;

    // Test
    int16_t ticksToWait = setServoAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(FAIL_VALUE, ticksToWait);
}

void testThatSetServoAngleFailsIfTargetAngleSmallerThanMinAngle()
{
    // Fixture
    Servo *testServo = getTestServo();
    int16_t targetAngle = MIN_LIDAR_ANGLE - 1;

    // Test
    int16_t ticksToWait = setServoAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(FAIL_VALUE, ticksToWait);
}

void testThatSetServoAngleReturnsZeroWhenWaitingForServoToMove()
{
    // Fixture
    Servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE / 2;

    // Test
    int16_t ticksToWait = setServoAngle(testServo, targetAngle, true);

    // Assert
    TEST_ASSERT_EQUAL(0, ticksToWait);
}

void testThatSetServoAngleReturnsCorrectTicksToWaitWhenNotWaitingForServo()
{
    // Fixture
    Servo *testServo = getTestServo();
    int16_t targetAngle = MAX_LIDAR_ANGLE;
    int16_t servoTargetAngle = translateTargetAngleToServoAngle(targetAngle, BELT_DRIVE_RATIO, GEAR_RATIO, SERVO_CENTRE_ANGLE);

    uint32_t expectedTimeToComplete = (uint32_t)calculateTimeToCompleteMove(testServo->currentAngle, servoTargetAngle, MILLISECONDS_PER_SIXTY_DEGREES);
    int expectedTicks = M2T(expectedTimeToComplete);

    // Test
    int actualTicks = setServoAngle(testServo, targetAngle, false);

    // Assert
    TEST_ASSERT_EQUAL(expectedTicks, actualTicks);
}

void testThatInitialiseLiDARServoCreatesServoCorrectly()
{
    // Fixture
    uint16_t expectedParamID = MOCK_PARAM_ID;
    uint16_t expectedIndex = MOCK_INDEX;
    uint16_t expectedCurrentAngle = translateTargetAngleToServoAngle(0, BELT_DRIVE_RATIO, GEAR_RATIO, SERVO_CENTRE_ANGLE);

    // Test
    Servo *servo = initialiseLiDARServo();

    // Assert
    TEST_ASSERT_EQUAL(expectedParamID, servo->servoAngleParamID.id);
    TEST_ASSERT_EQUAL(expectedIndex, servo->servoAngleParamID.index);
    TEST_ASSERT_EQUAL(expectedCurrentAngle, servo->currentAngle);
}