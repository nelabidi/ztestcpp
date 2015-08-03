//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  MatcherBaseImpl.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef MatcherBaseImpl_h__
#define MatcherBaseImpl_h__


#include "MatcherBase.h"

namespace ztest {


    template<typename matcher>
    struct MatcherBaseImp : MatcherBase
    {

        MatcherBaseImp(const char *file, int line)
            : MatcherBase(file, line)
        {
        }

        matcher & not()
        {
            MatcherBase::not();
            return getMatcher();
        }

        template<typename expectedType>
        matcher& toBe(expectedType target)
        {
            _result = toBeMatcher::compare(getMatcher()._actual, target);
            _result = applyNot(_result);
            throwException("toBe", toBeMatcher::fail_message());
            return getMatcher();
        }
    private:
        matcher& getMatcher()
        {
            return static_cast<matcher&>(*this);
        }

    };










}


#endif // MatcherBaseImpl_h__