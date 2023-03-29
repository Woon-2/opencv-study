#include <iostream>
#include <numeric>
#include <algorithm>

#include <opencv2/opencv.hpp>

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

int main()
{
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

    PRINT_NAME_AND_ELEMS(A);
    PRINT_NAME_AND_ELEMS(B);
    PRINT_NAME_AND_ELEMS(C);

    std::cout << "press any key\n";
    char ch;
    std::cin >> ch;
}