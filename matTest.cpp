#ifndef __matTest
#define __matTest

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>

TEST(MatTest, assign)
{
    auto A = cv::Mat(10, 10, CV_16U);
    std::iota(A.begin<unsigned short>(), A.end<unsigned short>(),
        unsigned short(0));
    
    auto V = std::vector<unsigned short>();
    std::adjacent_difference(A.begin<unsigned short>(), A.end<unsigned short>(),
        std::back_inserter(V));

    std::ranges::for_each(V, [](const auto& diff) {
        std::cout << diff << ' ';
    });

    GTEST_ASSERT_EQ(unsigned short(0), A.at<unsigned short>(0, 0));
    std::ranges::for_each(V.begin() + 1, V.end(), [](const auto& diff) {
        GTEST_ASSERT_EQ(1, diff);
    });
}

TEST(Terminate, Terminate)
{
    std::cout << "Press any key.\n";
    std::cin.get();
}

#endif // __matTest