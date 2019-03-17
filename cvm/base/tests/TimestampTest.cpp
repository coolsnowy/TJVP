#include <vector>

#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

#include <cvm/base/Timestamp.h>

#include <gtest/gtest.h>

using namespace cvm;
using namespace cvm::base;

TEST(TimestampTest, TimestampTest)
{
    Timestamp time1 = Timestamp::now();
    Timestamp time2 = addTime(time1.microSecondsSinceEpoch(), 1);
    Timestamp time3 = time2;
    Timestamp time4 = Timestamp::invalid();
    Timestamp time5 = Timestamp::now();
    Timestamp time6 = Timestamp::fromUnixTime(123456);
    Timestamp time7 = Timestamp::fromUnixTime(123456, 123456);

    ASSERT_LT(time1, time2);
    ASSERT_EQ(time2, time3);
    ASSERT_GT(time2, time1);
    ASSERT_NE(time1, time2);
    ASSERT_LE(time1, time2);
    ASSERT_GE(time2, time1);
    ASSERT_LE(time2, time3);
    ASSERT_GE(time2, time3);
    ASSERT_FALSE(time4.valid());
    ASSERT_TRUE(time5.valid());
    ASSERT_EQ(time6.microSecondsSinceEpoch(), static_cast<int64_t>(123456) * 1000 * 1000);
    ASSERT_EQ(time6.secondsSinceEpoch(), static_cast<int64_t>(123456));
    ASSERT_EQ(time7.microSecondsSinceEpoch(), static_cast<int64_t>(123456) * 1000 * 1000 + 123456);
    ASSERT_EQ(time7.secondsSinceEpoch(), static_cast<int64_t>(123456));
    ASSERT_EQ(differTime(time7, time6), static_cast<int64_t>(123456));
    ASSERT_EQ(addTime(time6, 123456), time7);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

