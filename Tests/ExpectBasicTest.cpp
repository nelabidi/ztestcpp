//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  ExpectBasicTest.cpp
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ztestcpp.h>


describe("Expect basic, integral types handling")
{
    it("should throw an expection if a test fails")
    {
        bool thrown = false;
        try
        {
        }
        catch (ztest::Exception* )
        {
            thrown = true;
        }
        catch (...)
        {
            thrown = false;
        }
        ASSERT_TEST(thrown, getTestCaseFullName().c_str());

    }
    it("should handle bool")
    {

    }
    it("should handle char")
    {

    }
    it("should handle short")
    {

    }
    it("should handle long")
    {

    }
    it("should handle int")
    {

    }
    it("should handle long long")
    {

    }
    it("should handle float")
    {

    }
    it("should handle double")
    {

    }

};
