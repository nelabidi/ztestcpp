//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  StringMatcher.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////
#ifndef StringMatcher_h__
#define StringMatcher_h__


namespace ztest {

    template<>
    struct Matcher<const char*> : MatcherBaseImp<Matcher<const char *> >
    {
        typedef  MatcherBaseImp< Matcher<const char*> > BASE;

        Matcher(const char* actual, const char *file, int line)
            : MatcherBaseImp(file, line),
              _actual(actual)
        {
        }


    protected:
        const char * _actual;
    };

}





#endif // StringMatcher_h__
