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


namespace ztest
{


template<>
struct Matcher<std::string> : MatcherBaseImp < Matcher<std::string> >
{
    typedef MatcherBaseImp < Matcher<std::string> > BASE;

    Matcher(const std::string& actual, const char *file, int line)
        : MatcherBaseImp(file, line),
          _actual(actual)
    {
    }

    void toContain(const std::string& str)
    {
        _result = _actual.find(str) != _actual.npos;
        _result = applyNot(_result);
        std::string msg = std::string("doesn't contain ") + str;
        throwException("toContain", msg);
    }
    void toContain(const char * str)
    {
        toContain(std::string(str));
    }

protected:
    std::string _actual;
    friend BASE;
};



template<>
struct Matcher<const char*> : MatcherBaseImp < Matcher<const char*> >
{
    typedef MatcherBaseImp < Matcher<const char*> > BASE;

    Matcher(const char* actual, const char *file, int line)
        : BASE(file, line),
          _actual(actual)

    {
    }

    void toContain(const std::string& str)
    {
        _result = std::string(_actual).find(str) != std::string(_actual).npos;
        _result = applyNot(_result);
        std::string msg = std::string("doesn't contain ") + str;
        throwException("toContain", msg);
    }

    void toContain(const char * szStr)
    {
        std::string actual(_actual);
        std::string expected(szStr);

        _result = actual.find(expected) != actual.npos;
        _result = applyNot(_result);
        std::string msg = std::string("doesn't contain ") + expected;
        throwException("toContain", msg);
    }


protected:
    const char* _actual;
    friend BASE;
};

}





#endif // StringMatcher_h__
