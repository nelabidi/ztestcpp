//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  DefaultOutputer.h
// PURPOSE: a default and basic Outputer implementation
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef DefaultOutputer_h__
#define DefaultOutputer_h__


namespace ztest
{


struct DefaultOutputer :  OutPuter
{

    virtual void TestCaseSuccess(const TestCaseInfo& )
    {
        std::cerr << PASS_COLOR << "." << DEFAULT_COLOR;
    }

    virtual void TestCaseFailure(const TestCaseInfo& , const Exception &)
    {
        std::cerr << FAIL_COLOR << "X" << DEFAULT_COLOR;
    }

    virtual void TestEnd( )
    {
        std::cerr << DEFAULT_COLOR << std::endl;
    }

    virtual void OutPutTestResults(TestResults &testResults)
    {
        outPutFailures(testResults);
        outPutSummary(testResults);
    }

private:
    void outPutSummary(TestResults & testResults)
    {
        std::cerr << "   " << PASS_COLOR << testResults.succeededCount();
        std::cerr << DEFAULT_COLOR << " Passed, ";
        std::cerr << FAIL_COLOR << testResults.failedCount();
        std::cerr << DEFAULT_COLOR << " Failed.\n\n";

    }
    void outPutFailures(TestResults & testResults)
    {
        if (!testResults.failedCount())
            return;

        std::cerr << FAIL_COLOR << testResults.failedCount()  << " Test Failed:\n" << DEFAULT_COLOR;
        for (unsigned int i = 0; i < testResults.failedCount(); i++)
        {
            FailedResult result = testResults.getFailed(i);
            std::stringstream ss;
            ss << result.file << "(" << result.line << "): " <<  result.message << ".\n";
            std::cerr << ss.str();

        }
    }
};



}  //end namespace ztest




#endif // DefaultOutputer_h__