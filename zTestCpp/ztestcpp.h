//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  ztestcpp.h
// PURPOSE: this the main library include file
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
#include <exception> //used by Exception object
#include <iostream> //used by DefaultOutputer


#define ZTEST_VERIOSN  "1.1.0"


//Helper macros
#define LINE_INFO() __FILE__, __LINE__
#define XCONCAT_I(a,b) a ## b
#define XCONCAT(a,b) XCONCAT_I(a,b)
#define GENERATE_UNIQUE_ID(x)  XCONCAT(x,XCONCAT(_,__LINE__))

namespace ztest {
    //Forward declaration
    struct Exception;
    struct TestListener;
    struct TestResults;

    //TestCase data
    struct  TestCaseInfo
    {
        std::string fullName;
        std::string name;
        std::string file;
        int line;
    };
    // TestCase Filter interface
    struct TestCaseFilter
    {
        virtual bool filterTestCase(const TestCaseInfo& testCaseInfo) = 0;
        virtual bool filterTestSuite(const std::string& testSuiteName) = 0;
    };
    //TestSuiteRunner Interface
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

    //TestListener interface
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
    // A listener who does nothing!
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

    // Outputer interface
    struct OutPuter : NullListener
    {
        virtual void OutPutTestResults(TestResults &) = 0;
    };


} //end namespace ztest

//TestSuite/TestCase registration macros
#define TESTSUITE_REGISTRATION(testSuiteId,testSuiteName)\
struct testSuiteId;\
static ztest::TestSuiteRegistrar<testSuiteId> GENERATE_UNIQUE_ID(TestSuiteRegistrar)(testSuiteName, __FILE__, __LINE__);\
struct testSuiteId : public ztest::TestSuiteBase<testSuiteId>


#define TESTCASE_REGISTRATION(testCaseId,testCaseName)\
struct XCONCAT(testCaseId,  reg) {\
    XCONCAT(testCaseId , reg )() \
    { \
        ztest::TestSuiteRunnerImpl<CURRENT_TESTSUITE>::addTestCase(&CURRENT_TESTSUITE::testCaseId, testCaseName, __FILE__, __LINE__);\
    } \
} XCONCAT(testCaseId, reg);\
void testCaseId()


// specs/describe macros
#define describe(testSuiteName) \
TESTSUITE_REGISTRATION(GENERATE_UNIQUE_ID(TestSuite), testSuiteName)

#define it(testCaseName) \
TESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)

//Exclude macros

#define XTESTSUITE_REGISTRATION(testSuiteId,testSuiteName)\
struct testSuiteId;\
struct testSuiteId : public ztest::TestSuiteBase<testSuiteId>


#define XTESTCASE_REGISTRATION(testCaseId,testCaseName)\
struct XCONCAT(testCaseId,  reg) {\
    XCONCAT(testCaseId , reg )() \
    { \
    } \
} XCONCAT(testCaseId, reg);\
void testCaseId()

// xdescribe macro, exclude test suite
#define xdescribe(testSuiteName) \
XTESTSUITE_REGISTRATION(GENERATE_UNIQUE_ID(TestSuite), testSuiteName)

// xit macro, exclude spec
#define xit(testCaseName) \
XTESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)


//forward declaration
namespace ztest {

    struct TestSuiteRunner;
    typedef std::vector<TestSuiteRunner*> TestSuiteRunnerList;
    template<typename testSuite> struct TestSuiteRunnerImpl;

} //end namespace ztest


#include "Console.h"
#include "Capture.h"
#include "Expect.h"
#include "TestResults.h"
#include "TestSuite.h"
#include "TestSuiteRunner.h"
#include "DefaultOutputer.h"

#include "TestRunner.h"
















#endif // ztestcpp_h__