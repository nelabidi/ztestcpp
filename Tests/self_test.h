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

namespace diagnostics {
struct Assert
{
    inline void operator() (const char* file, int line, const char*expr, const char* msg)
    {
        std::stringstream ss;
        ss << file << "(" << line << "): " << expr << ", " << msg << "... Failed";;
        std::cerr << ss.str() << std::endl;
        exit(1);
    }
    inline void operator() (const char* msg)
    {
        std::stringstream ss;
        ss << msg << "... Ok";
        std::cerr << ss.str() << std::endl;
    }
};
}


#define ASSERT_TEST(exp,msg)  (void) (!(exp) ? diagnostics::Assert()( __FILE__,__LINE__,(#exp),msg)  :  diagnostics::Assert()(msg) )




#endif // self_test_h__