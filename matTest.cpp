#ifndef __matTest
#define __matTest

#include "matComparison.hpp"

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <numeric>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ranges>

TEST(MatTest, GenerationWithCPPStandardAlgorithmWorks)
{
    auto A = cv::Mat(200, 200, CV_16U);
    std::iota( A.begin<unsigned short>(), A.end<unsigned short>(),
        unsigned short(0) );
    
    auto V = std::vector<unsigned short>();
    std::adjacent_difference( A.begin<unsigned short>(), A.end<unsigned short>(),
        std::back_inserter(V) );
    
    EXPECT_EQ( unsigned short(0), A.at<unsigned short>(0, 0) );
    std::ranges::for_each( V.begin() + 1, V.end(), [](const auto& diff) {
        EXPECT_EQ(1, diff);
    } );
}

TEST(MatTest, CopyingLValueIsSlightCopy)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A.row(3);

    B += cv::Scalar::all(1.);

    // the way to check two matrices are identical
    EXPECT_EQ( cv::bEqual( A.row(3), B ), true );
}

TEST(MatTest, CopyingCloneIsDeepCopy)
{
    auto A = cv::Mat(200, 200, CV_16UC4);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A.row(3).clone();

    B += cv::Scalar::all(1.);

    EXPECT_EQ( cv::bNotEqualAll( A.row(3), B ), true );
}

TEST(MatTest, CopyingRvalueIsDeepCopy)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A.row(3) + A.row(2);

    B += cv::Scalar::all(1.);

    EXPECT_EQ( cv::bNotEqualAll( A.row(3), B ), true );
}

TEST(MatTest, AddingScalarReturnsRvalue)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    cv::Mat B = A.row(3) + cv::Scalar::zeros();

    B += cv::Scalar::all(1.);

    EXPECT_EQ( cv::bNotEqualAll( A.row(3), B ), true );
}

TEST(MatTest, SubmatrixCannotRefOutsideOfSelf)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A.row(3);
    auto C = cv::Vec3f();
    EXPECT_THROW( C = B.row(5), cv::Exception );
}

TEST(MatTest, OperationWithScalarEffectsAllComponents)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A * 0.;

    auto C = A;
    C.forEach<cv::Vec3f>( [](auto& el, [[maybe_unused]] auto* pos) {
        el[0] = 0.;
        el[1] = 0.;
        el[2] = 0.;
    } );

    auto D = A.mul( cv::Scalar::all(0.) );

    EXPECT_EQ( cv::bEqual(B, C) && cv::bEqual(B, D) && cv::bEqual(C, D), true );
}

TEST(MatTest, MatExprIsRvalue)
{
    auto A = cv::Mat(200, 200, CV_32FC3);
    cv::randu( A, cv::Scalar::zeros(), cv::Scalar::all(255.) );

    auto B = A.row(3) + cv::Scalar::zeros();
    
    B += cv::Scalar::ones();

    EXPECT_EQ( cv::bEqual( A.row(3), B ), true );
}

TEST(MatTest, Filter2DIsConvolutionOperation)
{
    auto temp = cv::Mat( cv::imread("C:/Users/USER/Desktop/footprint of soilder/opencv/opencv-study/seok.png") );
    auto img = cv::Mat3b( temp.size() );
    temp.convertTo( img, img.depth() );

    auto imgRaisedContrastByFilter2D = cv::Mat3b( img.size() );

    auto kernal = cv::Mat((cv::Mat_<char>(3, 3) << 0, -1, 0,
                                              -1, 5, -1,
                                              0, -1, 0));
    cv::filter2D(img, imgRaisedContrastByFilter2D, img.depth(), kernal);

    auto imgRaisedContrast = cv::Mat3b( img.size() );
    
    const auto nChannels = img.channels();

    for ( auto i = 1; i < img.rows - 1; ++i ) {
        auto prev = img.ptr(i - 1);
        auto curr = img.ptr(i);
        auto next = img.ptr(i + 1);
        auto dest = imgRaisedContrast.ptr(i);

        for ( auto j = nChannels; j < nChannels * ( img.cols - 1 ); ++j ) {
            dest[j] = cv::saturate_cast<uchar>( curr[j] * 5 - prev[j] - curr[j - nChannels]
                - curr[j + nChannels] - next[j] );
        }
    }

    bool isFilter2DConvolution = true;

    for ( auto i = 1; isFilter2DConvolution && i < img.rows - 1; ++i ) {
        auto lhs = imgRaisedContrastByFilter2D.ptr(i);
        auto rhs = imgRaisedContrast.ptr(i);

        for ( auto j = nChannels; j < nChannels * ( img.cols - 1 ); ++j ) {
            if (lhs[j] != rhs[j]) {
                isFilter2DConvolution = false;
                break;
            }
        }
    }

    EXPECT_EQ( isFilter2DConvolution, true );
}

TEST(Terminate, Terminate)
{
    std::cout << "Press any key.\n";
    std::cin.get();
}

#endif // __matTest