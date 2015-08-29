//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  ExceptionThrowTest.cpp
// PURPOSE: test ExpectThrow macro
// DATE: 2015/08/09
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "self_test.h"



namespace
{

describe("ExceptionThrow")
{
    struct CustomExcpetion
    {
        CustomExcpetion(const char* msg)
            : what(msg)
        {
        }
        std::string what;
    };
    void throwme()
    {
        throw CustomExcpetion("Throw me");
    }
    it("ExpectThrow skeleton")
    {
        {
            bool thrown = false;
            try
            {
                throwme();
            }
            catch (const CustomExcpetion e)
            {
                expect(e.what).toBeEqual(std::string("Throw me"));
                thrown = true;
            }
            catch (...)
            {
                throw ztest::Exception("unknown exception thrown");
            }
            if (!thrown)
                throw ztest::Exception("Exception not thrown");

        }
    }
    it("using macro")
    {
        ExpectThrow(throwme(), CustomExcpetion);
    }

};

}