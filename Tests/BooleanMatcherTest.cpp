//////////////////////////////////////////////////////////////////////////
//
// PROJECT:  zTestC++ (zTestCpp) C++ Testing framework
// FILE:  BooleanMatcherTest.cpp
// PURPOSE: BooleanMatcher object test suite
// DATE: 2015/08/10
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ztestcpp.h>


namespace
{


describe("BooleanMatcher")
{

    int return10()
    {
        return 10;
    }

    it("implemnent toBeTrue")
    {
        expect(true).toBeTrue();
    }
    it("implemnent toBeFalse")
    {
        expect(false).toBeFalse();
    }

    it("can be used to check an expression if it's true")
    {
        expect((return10() < 100) && return10() > 5 ).toBeTrue();
    }

};




} //end namespace

