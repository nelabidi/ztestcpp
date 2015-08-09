//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  Expect.h
// PURPOSE: implement and declare Expect factory
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef Expect_h__
#define Expect_h__

#include "Exception.h"

#include "matchers/Matcher.h"
#include "matchers/PointerMatcher.h"


//expect macro helper
#define expect(v) ztest::Expect(v,__FILE__, __LINE__)

//Expect expression to thorw an exception
#define ExpectThrow(expr,type) \
{\
    bool thrown = false;\
    try{ (expr);\
                }catch(type ){ thrown = true; }\
    catch(...){thrown = true; throw ztest::Exception("caught unknown exception",__FILE__,__LINE__); }\
    if(!thrown)  throw ztest::Exception("Expected Exception of type '" #type "' not thrown",__FILE__,__LINE__);\
}

namespace ztest {

    //Expect,  matchers factory

    template<typename actualType>
    static Matcher<actualType>
    Expect(actualType actual, const char *file = nullptr, int line = 0)
    {
        return Matcher<actualType>(actual, file, line);
    }

}// end namespace ztest


#endif // Expect_h__