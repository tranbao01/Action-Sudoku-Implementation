/**
 * @file StopWatchTest.cpp
 * @author Paul Boik
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <StopWatch.h>

/**
 * Tests a stopwatch at Zero
 */
TEST(StopWatchTest, EmptyStopWatch)
{
    StopWatch TestWatch(0);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "0:00");
}

/**
 * Tests a stopwatch less than a minute
 */
TEST(StopWatchTest, OnlySeconds)
{
    StopWatch TestWatch(5000);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "0:05");
}

/**
 * Tests a stopwatch with only minutes
 */
TEST(StopWatchTest, OnlyMinutes)
{
    StopWatch TestWatch(300000);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "5:00");
}

/**
 * Tests a stopwatch with both minutes and seconds
 */
TEST(StopWatchTest, Everything)
{
    StopWatch TestWatch(305000);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "5:05");
}

/**
 * Tests a stopwatch with only minutes
 */
TEST(StopWatchTest, EverythignNew)
{
    StopWatch TestWatch(200000);
    TestWatch.Pause();
    ASSERT_TRUE(TestWatch.Time() == "3:20");
}