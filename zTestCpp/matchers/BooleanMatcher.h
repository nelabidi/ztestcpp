//////////////////////////////////////////////////////////////////////////
//
// PROJECT:  zTestC++ (zTestCpp) C++ Testing framework
// FILE:  BooleanMatcher.h
// PURPOSE: full specialization of Matcher template for boolean expression
// DATE: 2015/08/10
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef BooleanMatcher_h__
#define BooleanMatcher_h__




namespace ztest
{

//pointer type matcher partial specialization


template<>
struct Matcher <bool> : public MatcherBaseImp < Matcher < bool > >
{
    typedef  MatcherBaseImp< Matcher < bool > > BASE;

    Matcher(bool actual, const char *file, int line)
        : MatcherBaseImp(file, line),
          _actual(actual)
    {
    }

    void toBeTrue()
    {
        _result = applyNot(_actual == true);
        throwException("toBeTrue", "Not true");
    }

    void toBeFalse()
    {
        _result = applyNot(_actual == false);
        throwException("toBeFalse", "Not false");
    }

protected:

    bool _actual;
    friend BASE;

};






}//end namespace ztest




#endif // BooleanMatcher_h__



