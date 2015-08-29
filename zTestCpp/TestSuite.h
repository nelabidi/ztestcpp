//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  TestSuite.h
// PURPOSE: declare and implement the TestSuiteBase and TestSuiteRegistrar
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef TestSuite_h__
#define TestSuite_h__

namespace ztest
{


/*!
 * \class TestSuiteBase
 *
 * \brief The base class for every Test suite
 */
template<typename testSuite>
struct TestSuiteBase
{
    typedef testSuite CURRENT_TESTSUITE;

    void setUp()
    {
    }
    void tearDown()
    {
    }
    void beforeEach()
    {
    }
    void afterEach()
    {
    }
    //
    // return the name of the current TestSuite, the string parameter passed to describe
    std::string getName()
    {
        return _runner->getName();
    }
    //return the file where the test-suite is implemented
    std::string getFile()
    {
        return _runner->getFile();
    }
    //return the line where the test-suite is declared
    int     getLine()
    {
        return _runner->getLine();
    }
    //return the name, the string parameter passed to it macro
    std::string getTestCaseName()
    {
        return _runner->getCurrentTestCase().name;
    }
    //return the full name of the spec
    std::string getTestCaseFullName()
    {
        return _runner->getCurrentTestCase().fullName;
    }

private:

    friend struct TestSuiteRunnerImpl < testSuite > ;
    //called from TestSuiteRunner to set the current runner
    void setRunner(TestSuiteRunnerImpl< testSuite > * runner)
    {
        _runner = runner;
    }
    TestSuiteRunnerImpl < testSuite >* _runner;
};


/*!
 * \class TestSuiteRegistrar
 *
 * \brief this class is responsible for the test suite registration. there is one instance of this
 *        for each declared test suite with describe macro
 */
template<typename T>
struct TestSuiteRegistrar
{
    TestSuiteRegistrar(const char *name, const char *file, int line)
    {
        TestRunner::RegisterTestSuiteRunner < TestSuiteRunnerImpl<T>>(name, file, line);
    }
};


}// end namespace ztest



#endif // TestSuite_h__