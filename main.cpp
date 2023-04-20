#define ENABLE_EXPERIMENT_LOGGER

#include "mat.hpp"

#include <iostream>

int main()
{
    std::cout << "******************************\n";
    std::cout << "opencv expriments\n";
    std::cout << "******************************\n";

    testMatAssign();
    testMatType();
    testImageIO();
    testSubMatrix();
    testPrintMat();
    testInitializer();
    testRandu();
    testOutputFormat();
    testPoint();
    testStdVec();

    std::cout << "press any key\n";
    char ch;
    std::cin >> ch;
}