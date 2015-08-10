//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  ExpectExtraTest.cpp
// PURPOSE: use of expect outside of testcase
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ztestcpp.h>


namespace {

    describe("Expect outside of a test case")
    {

        //use Expect in setup/before
        void setUp()
        {
            void * p = 0;
            expect(p).toBeNull();

        }
        void tearDown()
        {
            void * p = 0;
            expect(p).toBeNull();

        }
        void beforeEach()
        {
            bool b = true;
            expect(b).not().toBeFalse();

        }
        void afterEach()
        {
            void * p = 0;
            expect(p).not().toBeNotNull();

        }

        it("a test case with expect")
        {
            expect(true).toBeTrue();
        }
    };




}//end namespace