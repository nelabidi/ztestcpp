//////////////////////////////////////////////////////////////////////////
//
// PROJECT:  zTestCpp C++ Testing Framework
// FILE:  main.cpp
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ztestcpp.h>

using namespace std;


namespace {

describe("TestSuite 2")
{
    it("I want to sleep, please!")
    {
        cout << "in spec: " << getTestCaseName() << endl;
    }
};
}


void TestSuiteRegistrationTest()
{
    describe("TestSuiteRegistration")
    {
        it("Should find this testSuite")
        {
        }
    };

    using namespace ztest;
    bool testSuiteFound = false;

    //should find TestSuiteRegistration
    TestSuiteRunnerList runners;
    TestRunner::getAllRunners(runners);
    for (unsigned i = 0; i < runners.size() && !testSuiteFound; i++)
    {
        testSuiteFound = runners[i]->getName() == "TestSuiteRegistration";
    }

    ASSERT_TEST(testSuiteFound, "TestSuiteRegistration: should find a testSuite");

}

int setupCalls, tearDownCalls, beforeEachCalls, afterEachCalls;
void TestSuiteRunnerTest()
{
    describe("TestSuiteRunner")
    {
        bool setupcalled, beforeEachCalled, afterEachCalled;
        void setUp()
        {
            setupCalls++;
            setupcalled = true;
        }
        void tearDown()
        {
            tearDownCalls++;
        }
        void beforeEach()
        {
            beforeEachCalls++;
            beforeEachCalled = true;
        }
        void afterEach()
        {
            afterEachCalls++;
            afterEachCalled = true;
        }

        it("Should call setUp")
        {
            ASSERT_TEST(setupcalled, getTestCaseFullName().c_str());
        }
        it("Should call tearDown once")
        {
            //ASSERT_TEST(setupCalls == 1, getTestCaseFullName().c_str());
        }
        it("Should call beforEach")
        {
            ASSERT_TEST(beforeEachCalled, getTestCaseFullName().c_str());
        }
        it("Should call afterEach 3 times")
        {
            ASSERT_TEST(afterEachCalls == 3, getTestCaseFullName().c_str());
        }

    };
    using namespace ztest;
    TestSuiteRunnerBase * runner = TestRunner::findRunner("TestSuiteRunner");

    ASSERT_TEST(runner != nullptr, "TestSuiteRunnerTest: Should find runner");
    setupCalls = tearDownCalls = beforeEachCalls = afterEachCalls = 0;

    runner->Run();

    ASSERT_TEST(setupCalls == 1, "TestSuiteRunnerTest: Should call setupCalls 1 time ");
    ASSERT_TEST(tearDownCalls == 1, "TestSuiteRunnerTest: Should call tearDownCalls 1 time");

    ASSERT_TEST(afterEachCalls == 4, "TestSuiteRunnerTest: Should call afterEach 4 times");
    ASSERT_TEST(beforeEachCalls == 4, "TestSuiteRunnerTest: Should call afterEach 4 times");




}


int main(int argc, char* argv[])
{
    cout << "--------------------------------------------" << endl << endl;
    cout << "   zTest Framework for c++ version: " << ZTEST_VERIOSN << endl;
    cout << "--------------------------------------------" << endl << endl;

    TestSuiteRegistrationTest();
    TestSuiteRunnerTest();

    return 0;
}

