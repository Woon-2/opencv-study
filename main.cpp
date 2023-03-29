#include <iostream>
#include <numeric>
#include <algorithm>

#include <opencv2/opencv.hpp>

int main()
{
    cv::Mat A(10, 10, CV_16U);
    std::iota(A.begin<unsigned short>(), A.end<unsigned short>(), 0u);

    for (decltype(A.rows) i = 0; i < A.rows; ++i)
    {
        auto pt = A.ptr<unsigned short>(i);
        for (decltype(A.cols) j = 0; j < A.cols; ++j)
        {
            std::cout << pt[j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << "press any key";
    char ch;
    std::cin >> ch;
}