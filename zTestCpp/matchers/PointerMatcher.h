//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  PointerMatcher.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef PointerMatcher_h__
#define PointerMatcher_h__

#include "MatcherBaseImpl.h"

namespace ztest {



    template<typename actualType>
    struct Matcher < actualType * > : MatcherBaseImp< Matcher < actualType * >>
    {
        typedef  MatcherBaseImp< Matcher < actualType * >> BASE;

        Matcher(actualType* actual, const char *file, int line)
            : MatcherBaseImp( file, line),
              _actual(actual)
        {
        }


        void toBeNull()
        {
            _result =  _actual  == ((void *)0);
            applyNot(_result);
            throwException("teBeNull", "Not null");
        }

        void toBeNotNull()
        {
            _result = _actual != ((void *)0);
            applyNot(_result);
            throwException("toBeNotNull", "is null");
        }


    protected:

        actualType * _actual;
        friend BASE;

    };






}//end namespace zetest



#endif // PointerMatcher_h__