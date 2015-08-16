//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  CaptureTest.cpp
// PURPOSE:
// DATE: 2015/08/16
// NOTES:
//
//////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <ztestcpp.h>


namespace {

    describe("Capture ostream")
    {

        it("capture std::cout")
        {
            ztest::Capture c(std::cout);
            std::cout << "Hello";
            expect(c).toContain("Hello");

        }

    };



}