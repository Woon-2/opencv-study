#ifndef __matTest
#define __matTest

#include <gtest/gtest.h>
#include <iostream>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HelloTest, BasicAssertions2)
{
    EXPECT_EQ(1 + 2 + 3 + 4 + 5, 15);
}

TEST(Terminate, Terminate)
{
    std::cout << "Press any key.\n";
    std::cin.get();
}

#endif // __matTest