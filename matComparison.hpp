#ifndef __matComparison
#define __matComparison

#include <opencv2/opencv.hpp>

#include <array>

namespace cv
{

template <class Pred>
bool bCompare(const cv::Mat& lhs, const cv::Mat& rhs, Pred pred)
{
    if ( lhs.dims != rhs.dims 
        || lhs.size != rhs.size
        || lhs.type() != rhs.type()) {
        return false;
    }

    if ( lhs.isContinuous() && rhs.isContinuous() ) {
        auto lBegin = lhs.ptr();
        auto lEnd = lBegin + lhs.total() + lhs.elemSize();
        auto rBegin = rhs.ptr();

        return std::equal(lBegin, lEnd, rBegin, pred);
    }
    else {
        auto arrays = std::array<const cv::Mat*, 3>({ &lhs, &rhs, nullptr });
        auto ptrs = std::array<uchar*, 2>();
        auto it = cv::NAryMatIterator( arrays.data(), ptrs.data(), 2 );
        auto loops = it.nplanes;
        
        while (loops--) {
            auto lBegin = it.ptrs[0];
            auto lEnd = lBegin + it.size * lhs.elemSize();
            auto rBegin = it.ptrs[1];

            if ( !std::equal(lBegin, lEnd, rBegin, pred) ) {
                return false;
            }

            ++it;
        }

        return true;
    }
}

bool bEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return bCompare( lhs, rhs, std::equal_to<>{} );
}

bool bNotEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return !bCompare( lhs, rhs, std::equal_to<>{} );
}

bool bNotEqualAll(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return cv::sum(lhs == rhs) == cv::Scalar::zeros();
}

bool bLess(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return bCompare( lhs, rhs, std::less<>{} );
}

bool bNotLess(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return !bCompare( lhs, rhs, std::less<>{} );
}

bool bGreater(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return bCompare( lhs, rhs, std::greater<>{} );
}

bool bNotGreater(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return !bCompare( lhs, rhs, std::greater<>{} );
}

bool bLessEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return bCompare( lhs, rhs, std::less_equal<>{} );
}

bool bNotLessEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return !bCompare( lhs, rhs, std::less_equal<>{} );
}

bool bGreaterEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return bCompare( lhs, rhs, std::greater_equal<>{} );
}

bool bNotGreaterEqual(const cv::Mat& lhs, const cv::Mat& rhs)
{
    return !bCompare( lhs, rhs, std::greater_equal<>{} );
}

} // cv

#endif  // __MatComparison