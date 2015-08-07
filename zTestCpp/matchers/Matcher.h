//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  Matcher.h
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef Matcher_h__
#define Matcher_h__


#include "matchers/MatcherBaseImpl.h"

namespace ztest {


    template<typename actualType>
    struct Matcher : MatcherBaseImp< Matcher<actualType> >
    {
        typedef  MatcherBaseImp< Matcher<actualType> > BASE;


        Matcher(actualType actual, const char *file, int line)
            : MatcherBaseImp(file, line),
              _actual(actual)
        {
        }

        template<typename expectedType>
        Matcher& toBeLess(expectedType target)
        {
            toBe(target);
            return BASE::toMatch<expectedType, detail::toBeLess>("toBeLess", target);
        }

        template<typename expectedType>
        Matcher& lessThen(expectedType target)
        {
            return BASE::toMatch<expectedType, detail::toBeLess>("lessThen", static_cast<actualType>(target));
        }


        template<typename expectedType>
        Matcher& toBeLessOrEqual(expectedType target)
        {
            using namespace detail;

            toBe(target);
            bool result = toEqual::compare(_actual, target) || toBeLess::compare(_actual, target);
            _result = applyNot(result);
            throwException("toBeLessOrEqual", "Not less or equal");
            return *this;
        }

        template<typename expectedType>
        Matcher& toBeGreater(expectedType target)
        {
            using namespace detail;

            toBe(target);
            bool result = !(toEqual::compare(_actual, target) || toBeLess::compare(_actual, target));
            _result = applyNot(result);
            throwException("toBeGreater", "Not Greater");
            return *this;
        }
        template<typename expectedType>
        Matcher& toBeGreaterOrEqual(expectedType target)
        {
            using namespace detail;

            toBe(target);
            bool result = !(toBeLess::compare(_actual, target));
            _result = applyNot(result);
            throwException("toBeGreaterOrEqual", "Not Greater or equal");
            return *this;
        }


    private:

        friend BASE;
        actualType _actual;

    };


    namespace detail {

        struct toEqual
        {
            template < typename actualType, typename expectedType >
            static bool compare(actualType lh, expectedType rh)
            {
                return  lh == rh;
            }
            static const char *fail_message()
            {
                return "Not equal";
            }
        };

        struct toBeLess
        {
            template < typename actualType, typename expectedType >
            static bool compare(actualType lh, expectedType rh)
            {
                return  lh < rh;
            }
            static const char *fail_message()
            {
                return "Not Less Then";
            }
        };

    }


}//end namespace ztest





#endif // Matcher_h__