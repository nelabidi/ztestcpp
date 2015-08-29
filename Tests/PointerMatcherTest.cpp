//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  PointerMatcherTest.cpp
// PURPOSE: Pointermatcher object test suite
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <ztestcpp.h>

//anonymous namespace are very important to avoid collisions
namespace
{

using namespace ztest;

describe("PointerMatcher")
{
    bool thrown;

    void beforeEach()
    {
        thrown = false;
    }

    template<typename T1, typename T2 >
    void DoToBeEqualTest(T1  a, T2 b)
    {
        try
        {
            Expect(a, LINE_INFO()).toBe(b);
            Expect(b, LINE_INFO()).toBeEqual(b);
        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
            //std::cerr << e.where() << ": " << e.what() << std::endl;
        }
    }

    template<typename T, typename T1>
    void DoToNotBeEqualTest(T  a, T1 b)
    {
        try
        {
            Expect(a).toBe(b);
            Expect(b).toBeNotEqual(b);
        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
            //std::cerr << e.where() << ": " << e.what() << std::endl;
        }
    }

    it("toBeEqual should handle void*")
    {
        void *a = 0;
        void *b = 0;
        DoToBeEqualTest(a, b);
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeEqual should handle nullptr_t")
    {
        std::nullptr_t p  = nullptr;
        std::nullptr_t p2 =  nullptr;
        DoToBeEqualTest(p, p2);
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeEqual should handle nullptr")
    {
        DoToBeEqualTest(nullptr, nullptr);
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
    }


    it("toBeEqual should handle char*")
    {
        char *a = 0;
        char *b = 0;
        DoToBeEqualTest(a, b);
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeEqual should handle const char*")
    {
        const char *a = 0;
        const char *b = 0;
        DoToBeEqualTest(a, b);
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
    }



    it("toBeEqual should handle diffrent types")
    {
        void *a = 0;
        char *b = 0;
        DoToBeEqualTest(a, b);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }


    ////// toBeNotEqual

    it("toBeNotEqual should handle void*")
    {
        void *a = 0;
        void *b = 0;
        DoToNotBeEqualTest(a, b);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeNotEqual should handle nullptr_t")
    {
        std::nullptr_t p = nullptr;
        std::nullptr_t p2 = nullptr;
        DoToNotBeEqualTest(p, p2);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeNotEqual should handle nullptr")
    {
        DoToNotBeEqualTest(nullptr, nullptr);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }


    it("toBeNotEqual should handle char*")
    {
        char *a = 0;
        char *b = 0;
        DoToNotBeEqualTest(a, b);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }

    it("toBeNotEqual should handle const char*")
    {
        const char *a = 0;
        const char *b = 0;
        DoToNotBeEqualTest(a, b);
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }


    //toEqual
    it("toEqual should compare pointers without type check")
    {

        try
        {
            char * p = NULL;
            void * p2 = NULL;
            ztest::Expect(p, LINE_INFO()).toEqual(p2);
        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
            //std::cerr << e.where() << ": " << e.what() << std::endl;
        }
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());

    }


    it("toNotEqual should compare pointers without type check")
    {

        try
        {
            const char * p = "hi";
            void * p2 = 0;
            ztest::Expect(p, LINE_INFO()).toNotEqual(p2);
        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
            //std::cerr << e.where() << ": " << e.what() << std::endl;
        }
        ASSERT_TEST(!thrown, getTestCaseFullName().c_str());

    }




    it("should detect null")
    {
        try
        {
            char * p = "hi";
            ztest::Expect(p, LINE_INFO()).toBeNull();
        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
        }
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());
    }

    it("should detect not null")
    {
        try
        {
            char * p = NULL;
            ztest::Expect(p, LINE_INFO()).toBeNotNull();

        }
        catch (const ztest::Exception& e)
        {
            e;
            thrown = true;
            //std::cerr << e.where() << ": " << e.what() << std::endl;
        }
        ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());

    }

};




}//end namespace