//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  ztestcpp.h
// PURPOSE:
// DATE: 2015/07/31
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef ztestcpp_h__
#define ztestcpp_h__


#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <exception>

#include <iostream> //outputer


#define ZTEST_VERIOSN  "1.0.0-beta"

//TODO: add login to file
//#define ENABLE_LOGING

#ifdef ENABLE_LOGING
#include <iostream>
using namespace std;
#define LOG(msg)  cout << msg <<endl;
#else
#define LOG(msg)
#endif // ENABLE_LOGING


#define LINE_INFO() __FILE__, __LINE__


#define XCONCAT_I(a,b) a ## b
#define XCONCAT(a,b) XCONCAT_I(a,b)
#define GENERATE_UNIQUE_ID(x)  XCONCAT(x,XCONCAT(_,__LINE__))


namespace ztest {

    struct Exception;
    struct TestListener;


    struct  TestCaseInfo
    {
        std::string fullName;
        std::string name;
        std::string file;
        int line;
    };

    struct TestCaseFilter
    {
        virtual bool filterTestCase(const TestCaseInfo& testCaseInfo) = 0;
        virtual bool filterTestSuite(const std::string& testSuiteName) = 0;
    };

    struct TestSuiteRunner
    {
        virtual void Run(TestListener* = 0) = 0;
        virtual int getLine() = 0;
        virtual std::string getFile() = 0;
        virtual std::string getName() = 0;
        virtual int getTestCasesCount() = 0;
        virtual TestCaseInfo getTestCase(int index) = 0;
        virtual TestCaseInfo getCurrentTestCase() = 0;
        virtual void setTestCaseFilter(TestCaseFilter *filter) = 0;
    };


    struct TestListener
    {

        virtual void TestStart() = 0;
        virtual void TestSuiteStart(const TestSuiteRunner& runner) = 0;
        virtual void TestCaseStart(const TestCaseInfo& testCaseInfo) = 0;
        virtual void TestCaseSuccess(const TestCaseInfo& testCaseInfo) = 0;
        virtual void TestCaseFailure(const TestCaseInfo& testCaseInfo, const Exception &e) = 0;
        virtual void TestCaseEnd(const TestCaseInfo& testCaseInfo) = 0;
        virtual void TestSuiteEnd(const TestSuiteRunner&) = 0;
        virtual void TestEnd() = 0;
    };

    struct NullListener : TestListener
    {
        virtual void TestStart() {}
        virtual void TestSuiteStart(const TestSuiteRunner& ) {}
        virtual void TestCaseStart(const TestCaseInfo& ) {}
        virtual void TestCaseSuccess(const TestCaseInfo& ) { }
        virtual void TestCaseFailure(const TestCaseInfo& , const Exception &) { }
        virtual void TestCaseEnd(const TestCaseInfo& ) {}
        virtual void TestSuiteEnd(const TestSuiteRunner&) {}
        virtual void TestEnd() {}

    };


} //end namespace ztest


#define TESTSUITE_REGISTRATION(testSuiteId,testSuiteName)\
struct testSuiteId;\
static ztest::TestSuiteRegistrar<testSuiteId> GENERATE_UNIQUE_ID(TestSuiteRegistrar)(testSuiteName, __FILE__, __LINE__);\
struct testSuiteId : public ztest::TestSuiteBase<testSuiteId>

// specs/describe macros
#define describe(testSuiteName) \
TESTSUITE_REGISTRATION(GENERATE_UNIQUE_ID(TestSuite), testSuiteName)


#define TESTCASE_REGISTRATION(testCaseId,testCaseName)\
struct XCONCAT(testCaseId,  reg) {\
    XCONCAT(testCaseId , reg )() \
    { \
        ztest::TestSuiteRunnerImpl<CURRENT_TESTSUITE>::addTestCase(&CURRENT_TESTSUITE::testCaseId, testCaseName, __FILE__, __LINE__);\
    } \
} XCONCAT(testCaseId, reg);\
void testCaseId()


#define it(testCaseName) \
TESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)


//forward declaration

namespace ztest {

    struct TestSuiteRunner;
    typedef std::vector<TestSuiteRunner*> TestSuiteRunnerList;
    template<typename testSuite> struct TestSuiteRunnerImpl;

} //end namespace ztest


#include "Console.h"
#include "Expect.h"
#include "TestResults.h"
#include "TestSuite.h"
#include "TestSuiteRunner.h"

#include "DefaultOutputer.h"

#include "TestRunner.h"















#endif // ztestcpp_h__