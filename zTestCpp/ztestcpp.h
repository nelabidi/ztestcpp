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



#define ZTEST_VERIOSN  "1.0.0"

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
        ztest::TestSuiteRunner<CURRENT_TESTSUITE>::addTestCase(&CURRENT_TESTSUITE::testCaseId, testCaseName, __FILE__, __LINE__);\
    } \
} XCONCAT(testCaseId, reg);\
void testCaseId()


#define it(testCaseName) \
TESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)







#include "Console.h"
#include "Expect.h"


//forward declaration

namespace ztest {

    struct TestSuiteRunnerBase;
    typedef std::vector<TestSuiteRunnerBase*> TestSuiteRunnerList;
    template<typename testSuite> struct TestSuiteRunner;

} //end namespace ztest


#include "TestSuite.h"
#include "TestSuiteRunner.h"
#include "TestRunner.h"














#endif // ztestcpp_h__