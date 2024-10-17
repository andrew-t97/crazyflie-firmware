#include "lidar.h"

#include "unity.h"
#include "FreeRTOS.h"
#include "freertosMocks.h"
#include "mock_system.h"

#include <string.h>

#define LEFT_VAR_ID 1
#define RIGHT_VAR_ID 2
#define BACK_VAR_ID 3
#define FRONT_VAR_ID 4

#define LEFT_RANGE 1
#define RIGHT_RANGE 2
#define BACK_RANGE 3
#define FRONT_RANGE 4

// Mocks

logVarId_t logGetVarId(const char *group, const char *name)
{
    if (strcmp(group, "ranger") == 0)
    {
        if (strcmp(name, "front") == 0)
        {
            return FRONT_VAR_ID;
        }
        else if (strcmp(name, "back") == 0)
        {
            return BACK_VAR_ID;
        }
        else if (strcmp(name, "left") == 0)
        {
            return LEFT_VAR_ID;
        }
        else if (strcmp(name, "right") == 0)
        {
            return RIGHT_VAR_ID;
        }
    }
    else
    {
        return -1;
    }
}

unsigned int logGetUint(logVarId_t varid)
{
    switch (varid)
    {
    case FRONT_VAR_ID:
        return FRONT_RANGE;
    case BACK_VAR_ID:
        return BACK_RANGE;
    case LEFT_VAR_ID:
        return LEFT_RANGE;
    case RIGHT_VAR_ID:
        return RIGHT_RANGE;
    }
}

// Tests

void testThatGetRangerLogIdsRetrievesAllLogIds()
{
    // Test
    lidarRangerLogIds *rangerLogIds = getRangerLogIds();

    // Assert
    TEST_ASSERT_EQUAL(rangerLogIds->back, BACK_VAR_ID);
    TEST_ASSERT_EQUAL(rangerLogIds->front, FRONT_VAR_ID);
    TEST_ASSERT_EQUAL(rangerLogIds->left, LEFT_VAR_ID);
    TEST_ASSERT_EQUAL(rangerLogIds->right, RIGHT_VAR_ID);
}

void testThatGetLidarRangesRetrievesRangesCorrectly()
{

    // Fixture
    lidarRangerLogIds *rangerLogIds = getRangerLogIds();

    // Test
    lidarRanges *ranges = getLidarRanges(rangerLogIds);

    // Assert
    TEST_ASSERT_EQUAL(ranges->front, FRONT_RANGE);
    TEST_ASSERT_EQUAL(ranges->back, BACK_RANGE);
    TEST_ASSERT_EQUAL(ranges->right, RIGHT_RANGE);
    TEST_ASSERT_EQUAL(ranges->left, LEFT_RANGE);
}