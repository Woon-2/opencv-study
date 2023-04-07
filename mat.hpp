#ifndef __mat
#define __mat

#include <iostream>
#include <numeric>
#include <algorithm>

#include <opencv2/opencv.hpp>

#include "experimentLogger.hpp"

#define PRINT_NAME_AND_ELEMS(mat) std::cout << "---Mat " << #mat << "---\n"; printMat(mat);

void printMat(const cv::Mat& mat)
{
    for (decltype(mat.rows) i = 0; i < mat.rows; ++i)
    {
        std::for_each_n(mat.ptr<unsigned short>(i), mat.cols, [](auto n)
            { std::cout << n << ' '; });
        std::cout << '\n';
    }
}

void matAssignTest()
{
    EXPERIMENT_LOG();
    
    cv::Mat A(10, 10, CV_16U);
    std::iota(A.begin<unsigned short>(), A.end<unsigned short>(),
        unsigned short(0));

    cv::Mat B = A.row(3);
    cv::Mat C = B.clone();
    try
    {
        cv::Mat D = C.row(5);
        std::cout << "cv::Mat D = C.row(5); must be failed.\n";
        std::abort();
    }
    catch([[maybe_unused]] cv::Exception& e)
    {}

    C += 1;
    C.copyTo(A.row(0));
    cv::Mat D = A;
    cv::Mat(A.row(2) + A.row(3)).copyTo(D.row(2));

    cv::Mat E = A.clone();
    E.row(9) = A.row(1) + A.row(2) + A.row(3);

    cv::Mat F = A.row(7) * 2;
    F += 5;

    cv::Mat G = A.row(8);
    G += 5;

    PRINT_NAME_AND_ELEMS(A);
    PRINT_NAME_AND_ELEMS(B);
    PRINT_NAME_AND_ELEMS(C);
    PRINT_NAME_AND_ELEMS(D);
    PRINT_NAME_AND_ELEMS(E);
    PRINT_NAME_AND_ELEMS(F);
    PRINT_NAME_AND_ELEMS(G);
}

void matTypeTest()
{
    EXPERIMENT_LOG();
    cv::Mat mtx(3, 3, CV_32F); // make a 3x3 floating-point matrix
    cv::Mat cmtx(10, 1, CV_64FC2); // make a 10x1 2-channel floating-point
                            // matrix (10-element complex vector)
    cv::Mat img(cv::Size(1920, 1080), CV_8UC3); // make a 3-channel (color) image
                                        // of 1920 columns and 1080 rows.
    cv::Mat grayscale(img.size(), CV_MAKETYPE(img.depth(), 1)); // make a 1-channel image of
                                                            // the same size and same
                                                            // channel type as img
    CV_Assert(img.size() == grayscale.size());
    CV_Assert(grayscale.depth() == CV_8U);
    static_assert(CV_8U == CV_8UC1 != CV_8UC(1));
    static_assert(CV_16FC2 == CV_16FC(2));
}

void imageioTest()
{
    EXPERIMENT_LOG();
    auto img = cv::imread("C:\\Users\\USER\\Desktop\\footprint of soilder\\opencv\\opencv-study\\seok.png");
    cv::namedWindow("matTypeTest");
    cv::imshow("matTypeTest", img);
    cv::waitKey(30);
}

#endif //mat