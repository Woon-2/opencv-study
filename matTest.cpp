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

TEST(MatTest, assign001)
{
    auto A = cv::Mat(10, 10, CV_16U);
    std::iota(A.begin<unsigned short>(), A.end<unsigned short>(),
        unsigned short(0));
    
    auto V = std::vector<unsigned short>();
    std::adjacent_difference(A.begin<unsigned short>(), A.end<unsigned short>(),
        std::back_inserter(V));
    
    EXPECT_EQ(unsigned short(0), A.at<unsigned short>(0, 0));
    std::ranges::for_each(V.begin() + 1, V.end(), [](const auto& diff) {
        EXPECT_EQ(1, diff);
    });
}

TEST(MatTest, assign002)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu(A, cv::Scalar::zeros(), cv::Scalar::all(255));

    auto B = A.row(3);

    A.row(3) += cv::Scalar::all( 1. );

    // the way to check two matrices are identical
    EXPECT_EQ( cv::sum(A.row(3) != B), cv::Scalar::zeros() );
}

TEST(MatTest, assign003)
{
    auto A = cv::Mat(200, 200, CV_16UC4);
    cv::randu(A, cv::Scalar::zeros(), cv::Scalar::all(255));

    auto B = A.row(3).clone();

    A.row(3) += cv::Scalar::all( 1. );

    EXPECT_EQ( cv::sum(A.row(3) == B), cv::Scalar::zeros() );
}

TEST(Terminate, Terminate)
{
    std::cout << "Press any key.\n";
    std::cin.get();
}

#endif // __matTest