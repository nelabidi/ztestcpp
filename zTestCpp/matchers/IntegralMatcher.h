//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  IntegralMatcher.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef IntegralMatcher_h__
#define IntegralMatcher_h__


#include "MatcherBaseImpl.h"
#include "TypeInfo.h"

namespace ztest {


    template <>
    struct Matcher<detail::int_type >:    public MatcherBaseImp < Matcher <detail::int_type> >
    {
        typedef MatcherBaseImp < Matcher <detail::int_type> > BASE;

        template<typename actualType>
        Matcher(actualType actual, const char*file, const char line)
            : MatcherBaseImp(file, line),
              _actual(actual)
        {}

        template<typename expectedType>
        Matcher& toBeEqual(expectedType target)
        {
            toBe(target);

        }

        Matcher& toEqual(int target)
        {
            _result = _actual == target;
            applyNot(_result);

            return *this;
        }



    protected:
        int     _actual;
        friend  BASE;

    };




}





#endif // IntegralMatcher_h__