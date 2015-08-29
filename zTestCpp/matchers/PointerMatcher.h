//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  PointerMatcher.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef PointerMatcher_h__
#define PointerMatcher_h__


namespace ztest
{

//pointer type matcher partial specialization


template<typename actualType>
struct Matcher < actualType * > : public MatcherBaseImp< Matcher < actualType * > >
{
    typedef  MatcherBaseImp< Matcher < actualType * > > BASE;

    Matcher(actualType* actual, const char *file, int line)
        : MatcherBaseImp(file, line),
          _actual(actual)
    {
    }


    void toBeNull()
    {
        _result = _actual == ((void *)0);
        _result = applyNot(_result);
        throwException("toBeNull", "Not null");
    }

    void toBeNotNull()
    {
        _result = _actual != ((void *)0);
        _result = applyNot(_result);
        throwException("toBeNotNull", "is null");
    }


protected:

    actualType * _actual;
    friend BASE;

};






}//end namespace ztest



#endif // PointerMatcher_h__