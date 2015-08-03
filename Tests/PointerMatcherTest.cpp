//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  PointerMatcherTest.cpp
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <ztestcpp.h>



namespace {


    describe("PointerMatcher, pointers operations")
    {
        bool thrown;
        void beforeEach()
        {
            thrown = false;
        }

        it("should handle toBe, same pointer types")
        {

            try
            {
                char * p = NULL;
                int * p2 = nullptr;
                ztest::Expect(p, LINE_INFO()).toBe(p2);
            }
            catch (const ztest::Exception& e)
            {

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(thrown, getTestCaseFullName().c_str());

        }

        it("should handle null")
        {

            try
            {
                char * p = NULL;
                ztest::Expect(p, LINE_INFO()).toBeNull();
            }
            catch (const ztest::Exception& e)
            {

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());

        }

        it("should handle not null")
        {

            try
            {
                char * p = "hi";
                ztest::Expect(p, LINE_INFO()).toBeNotNull();
            }
            catch (const ztest::Exception& e)
            {

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
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

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
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

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST_FAILS(!thrown, getTestCaseFullName().c_str());

        }

        it("should handle nullptr")
        {

            try
            {
                char * p = nullptr;
                ztest::Expect(p, LINE_INFO()).toBeNull();
            }
            catch (const ztest::Exception& e)
            {

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }



        it("should handle pointer to nullptr pointer ")
        {

            try
            {
                char ** p = nullptr;
                ztest::Expect(p, LINE_INFO()).toBeNull();
                char *p2;
                p = &p2;
                ztest::Expect(p, LINE_INFO()).toBeNotNull();

            }
            catch (const ztest::Exception& e)
            {

                thrown = true;
                //TODO: here set the result message
                std::cerr << e.where() << ": " << e.what() << std::endl;
            }
            ASSERT_TEST(!thrown, getTestCaseFullName().c_str());
        }


    };




}//end namespace