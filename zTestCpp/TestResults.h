//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  TestResults.h
// PURPOSE: implement TestResult class
// DATE: 2015/08/06
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef TestResults_h__
#define TestResults_h__





namespace ztest
{

//Failed results data
struct FailedResult
{
    TestCaseInfo testCase;
    std::string file;
    int         line;
    std::string message;
};

//Failed/succeeded results container
struct TestResults
{
    void addFailed(const TestCaseInfo& testCase, std::string file, int line, std::string message)
    {
        FailedResult result;
        result.testCase = testCase;
        result.line = line;
        result.file = file;
        result.message = message;
        _failed.push_back(result);
    }
    void addSucceeded(const TestCaseInfo& testCase)
    {
        _succeded.push_back(testCase);
    }

    unsigned failedCount()
    {
        return _failed.size();
    }
    unsigned succeededCount()
    {
        return _succeded.size();
    }
    unsigned int totalResults()
    {
        return _succeded.size() + _failed.size();
    }

    FailedResult& getFailed(unsigned int index)
    {
        return _failed[index];
    }
    TestCaseInfo& getSucceeded(unsigned int index)
    {
        return _succeded[index];
    }

private:

    std::vector<FailedResult> _failed;
    std::vector<TestCaseInfo> _succeded;

};


} // end namespace ztest




#endif // TestResults_h__
