#ifndef __mat
#define __mat

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>

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

void testMatAssign()
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

void testMatType()
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

void testImageIO()
{
    EXPERIMENT_LOG();
    auto img = cv::imread("C:\\Users\\USER\\Desktop\\footprint of soilder\\opencv\\opencv-study\\seok.png");
    cv::namedWindow("testImageIO");
    cv::imshow("testImageIO", img);
    cv::waitKey(30);
}

void testSubMatrix()
{
    EXPERIMENT_LOG();
    auto img = cv::imread("C:\\Users\\USER\\Desktop\\footprint of soilder\\opencv\\opencv-study\\seok.png");
    auto sub = img(cv::Range::all(), cv::Range(50, 250));
    cv::namedWindow("testSubMatrix");
    cv::imshow("testSubMatrix", sub);
    cv::waitKey(30);
}

void testPrintMat()
{
    EXPERIMENT_LOG();
    auto mat = cv::Mat(4, 2, CV_8UC4, cv::Scalar(4, 16, 64, 128));
    std::cout << mat << '\n';
}

void testInitializer()
{
    EXPERIMENT_LOG();
    cv::Mat A = (cv::Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
    cv::Mat B = cv::Mat_<double>({1, 2, 3, 4, 5, 6, 7, 8, 9}).reshape(3);
    std::cout << A << '\n';
    std::cout << B << '\n';
}

void testRandu()
{
    EXPERIMENT_LOG();
    auto mat = cv::Mat(4, 4, CV_8UC4, cv::Scalar::zeros());
    cv::randu(mat, cv::Scalar::zeros(), cv::Scalar::all(255));
    std::cout << mat << '\n';
}

void testOutputFormat()
{
    EXPERIMENT_LOG();
    auto mat = cv::Mat(3, 2, CV_8UC3);
    cv::randu(mat, cv::Scalar::zeros(), cv::Scalar::all(255));

    std::cout << "[default]\n";
    std::cout << mat << "\n\n";
    std::cout << "[python]\n";
    std::cout << cv::format(mat, cv::Formatter::FMT_PYTHON) << "\n\n";
    std::cout << "[numpy]\n";
    std::cout << cv::format(mat, cv::Formatter::FMT_NUMPY) << "\n\n";
    std::cout << "[C]\n";
    std::cout << cv::format(mat, cv::Formatter::FMT_C) << "\n\n";
    std::cout << "[csv]\n";
    std::cout << cv::format(mat, cv::Formatter::FMT_CSV) << "\n\n";
}

void testPoint()
{
    EXPERIMENT_LOG();
    auto p1 = cv::Point2i(3, 4);
    auto p2 = cv::Point3f(2.3f, 4.5f, 6.7f);
    auto p3 = cv::Point2i(cv::Size(1, 2));
    auto p4 = cv::Point3f(cv::Vec3f(1.1f, 2.2f, 3.3f));

    std::cout << p1 << '\n';
    std::cout << p2 << '\n';
    std::cout << p3 << '\n';
    std::cout << p4 << '\n';
}

void testStdVec()
{
    EXPERIMENT_LOG();
    auto v1 = std::vector<float>(5);
    std::iota(std::begin(v1), std::end(v1), 1);
    
    std::cout << cv::Mat(v1) << '\n';

    auto v2 = std::vector<cv::Point2f>(5);
    std::ranges::generate(v2, [](){ return cv::Point2f{CV_PI, 0.f}; });

    std::cout << v2 << '\n';
}

#endif //mat