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

namespace {
    using namespace ztest;


    describe("Matcher, basic types handling, toBe and toBeEqual")
    {

        bool thrown;
        void beforeEach()
        {
            thrown = false;
        }

        template<typename T>
        void DoTest(const T & a, const T & b)
        {
            try
            {
                Expect(a, LINE_INFO()).toBe(b);
                Expect(b, LINE_INFO()).toEqual(b);
            }
            catch (const ztest::Exception&)
            {
                thrown = true;
            }
        }

        it("should do type check")
        {
            try
            {
                ztest::Expect('\0', LINE_INFO()).toBeEqual(0);

            }
            catch (const ztest::Exception& e)
            {
                e;
                thrown = true;
                //TODO: here set the result message
                // std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(thrown, getTestCaseFullName().c_str());

        }
        it("should handle bool")
        {
            try
            {
                Expect(true).toBe(true);
                Expect(true).toEqual(true);
            }
            catch (const ztest::Exception& )
            {
                thrown = true;
                //std::cerr << e.what() << std::endl;
            }
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle char")
        {
            char a = 'a';
            char b = 'b';
            try
            {
                Expect(a).toBe(b);
                Expect(a).toBeEqual(a);
            }
            catch (const ztest::Exception&)
            {
                thrown = true;
                //std::cerr << e.what() << std::endl;
            }
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle short")
        {
            DoTest<short>(1, 2);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());

        }
        it("should handle long")
        {
            DoTest<long>(1, 2);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle int")
        {
            DoTest<int>(1, 2);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle long long")
        {
            DoTest<long long>(1, 2);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle float")
        {
            DoTest<float>(1.0, 2.0);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
        it("should handle double")
        {
            DoTest<double>(1.0, 2.0);
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }

        it("should handle char*")
        {
            DoTest<char *>("a", "b");
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }
    };



    describe("Matcher, not operator")
    {

        it("should negate the result")
        {
            bool thrown = false;
            try
            {
                ztest::Expect(0, LINE_INFO()).not().toEqual(0);

            }
            catch (const ztest::Exception& e)
            {
                e;
                thrown = true;
                //TODO: here set the result message
                // std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(thrown, getTestCaseFullName().c_str());
        }

        it("toNotEqual")
        {
            bool thrown = false;
            try
            {
                // ztest::Expect(0, LINE_INFO()).toNotEqual(1);
                ztest::Expect(0, LINE_INFO()).toNotEqual(0);

            }
            catch (const ztest::Exception& e)
            {
                e;
                thrown = true;
            }
            ASSERT_TEST(thrown, getTestCaseFullName().c_str());
        }

        it("complex not abuse")
        {
            bool thrown = false;
            try
            {
                // !(0 != 0) && (0 == 1) -> false, should throw
                ztest::Expect(0, LINE_INFO()).not().toNotEqual(0).toEqual(1);

            }
            catch (const ztest::Exception& e)
            {
                e;
                thrown = true;
                //std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(thrown, getTestCaseFullName().c_str());
        }

    };

}// end namespace
