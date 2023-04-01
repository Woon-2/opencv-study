#ifndef __experimentLogger
#define __experimentLogger

#ifdef ENABLE_EXPERIMENT_LOGGER

#define EXPERIMENT_LOG() experimentLogger  __experimentLogObj(__FUNCTION__, __FILE__, __LINE__)

namespace
{
class experimentLogger
{
public:
    experimentLogger(const char* funcName, const char* fileName,
        int lineNumber)
        : expNumber(++expCnt), funcName(funcName), fileName(fileName),
            lineNumber(lineNumber)
    {
        std::cout << "[experiment " << expNumber << "] - \""
            << funcName << "\" in " << fileName << ", line "
            << lineNumber << " entry\n";
    }

    ~experimentLogger()
    {
        std::cout << "[experiment " << expNumber << "] - \""
            << funcName << "\" in " << fileName << ", line "
            << lineNumber << " done\n";
    }

    experimentLogger(const experimentLogger&) = delete;
    experimentLogger& operator=(const experimentLogger&) = delete;

private:
    static size_t expCnt;

    size_t expNumber;
    const char* funcName;
    const char* fileName;
    const int lineNumber;
};

size_t experimentLogger::expCnt = 0;
}

#else

#define EXPERIMENT_LOG()

#endif // ENABLE_EXPERIMENT_LOGGER

#endif // __experimentLogger