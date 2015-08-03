//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  self_test.h
// PURPOSE:
// DATE: 2015/07/31
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef self_test_h__
#define self_test_h__


#include <iostream>
#include <sstream>


#include <ztestcpp.h>


namespace diagnostics {
    struct Assert
    {
        inline void operator() (const char* file, int line, const char*expr, const char* msg)
        {
            std::stringstream ss;

            ss << file << "(" << line << "): " << expr << ", " << msg << "..." ;
            std::cerr << ss.str() << FAIL_COLOR << "Failed" << std::endl << DEFAULT_COLOR;
            //exit(1);
            Errors()++;
        }
        inline void operator() (const char* msg)
        {
            std::stringstream ss;
            ss << msg << "...";
            std::cerr << ss.str() << PASS_COLOR << "Ok" << std::endl;
            std::cerr << DEFAULT_COLOR;
        }
        static int& Errors()
        {
            static int errors;
            return errors;
        }
    };

}

//use when an expression it not expected to fail
#define ASSERT_TEST(exp,msg)  (void) (!(exp) ? diagnostics::Assert()( __FILE__,__LINE__,(#exp),msg)  :  diagnostics::Assert()(msg) )

//use when an assertion is expected to fail
#define ASSERT_TEST_FAILS(exp,msg)  (void) ((exp) ? diagnostics::Assert()( __FILE__,__LINE__,(#exp),msg)  :  diagnostics::Assert()(msg) )

//return errors count if any
#define HAS_ERRORS() diagnostics::Assert::Errors();


#endif // self_test_h__