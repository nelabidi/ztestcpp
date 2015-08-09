//////////////////////////////////////////////////////////////////////////
//
// PROJECT:  zTestC++ (zTestCpp) C++ Testing framework
// FILE:  TestSuiteDecl.cpp
// PURPOSE:  TestSuite skeleton
// DATE: 2015/08/07
// NOTES:
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "self_test.h"


//anonymous namespace are very important to zTestCpp, it helps to avoid collisions
namespace {

    using namespace std;

    describe("A TestSuite")
    {
        //can declare members/fixtures
        int member, reset;

        struct MyStruct
        {
            int i;
            float f;
            void reset()
            {
                f = 0.0;
                i = 0;
            }
        };
        MyStruct *p;

        //with setup
        void setUp()
        {
            //initialize
            member = 1;
            p = new MyStruct();
        }
        //with tearDown
        void tearDown()
        {
            delete p;

        }
        //called beforeEach TestCase
        void beforeEach()
        {
            reset = 0;
            p->reset();
        }

        void afterEach()
        {
            //cleanup
        }
        //can declare a function to be used in a test case
        void doSomething()
        {
            //check or do something here
        }
        //this is a test case
        it("contains a test case")
        {

        }

    };

} //end namespace