//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  StringMatcherTest.cpp
// PURPOSE:
// DATE: 2015/08/16
// NOTES:
//
//////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <ztestcpp.h>


namespace
{


describe("String Matcher Test")
{
    it("implement contains")
    {
        expect("Hello naoufel").toContain("Hello");

    }
    it("implement equal/notequal")
    {
        expect("Hello").toEqual("Hello");
        expect("Hello").toBeEqual("Hello");
        expect("hello").toBeNotEqual("naoufel");


    }

};


}