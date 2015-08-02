//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  Matcher.h
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef Matcher_h__
#define Matcher_h__


namespace ztest {


    struct toBeMatcher
    {
        template < typename actualType >
        static bool compare(actualType, actualType)
        {
            return true;
        }
        template < typename actualType, typename expectedType >
        static bool compare(actualType, expectedType)
        {
            return false;
        }
        static const char *fail_message()
        {
            return "Not same type";
        }
    };

    struct toEqualMatcher
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

    struct toBeLessMatcher
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


    template < typename actualType >
    struct Matcher : MatcherBase
    {
        Matcher(actualType actual, const char *file, int line)
            : MatcherBase(file, line) ,
              _actual(actual)
        {
            _result = false;
            _not = false;
        }

        //interface
        template<typename expectedType>
        void typeCheck(expectedType target)
        {
            _result = toBeMatcher::compare(_actual, target);
            throwException("typeCheck", toBeMatcher::fail_message());
        }


        template<typename expectedType>
        Matcher& toBe(expectedType target)
        {
            _result = toBeMatcher::compare(_actual, target);
            _result = applyNot(_result);
            throwException("toBe", toBeMatcher::fail_message());
            return *this;
        }

        template<typename expectedType>
        Matcher& toEqual(expectedType target)
        {
            typeCheck(target);
            _result = applyNot(toEqualMatcher::compare(_actual, target));
            throwException("toEqual", toEqualMatcher::fail_message());
            return *this;
        }

        Matcher& not()
        {
            _not = !_not;
            return *this;
        }

        template<typename expectedType>
        Matcher& toNotEqual(expectedType target)
        {
            typeCheck(target);
            bool result = !toEqualMatcher::compare(_actual, target);
            _result = applyNot(result);
            throwException("toNotEqual", toEqualMatcher::fail_message());
            return *this;
        }

        template<typename expectedType>
        Matcher& toBeLess(expectedType target)
        {
            typeCheck(target);
            _result = applyNot(toBeLessMatcher::compare(_actual, target));
            throwException("toBeLess", toBeLessMatcher::fail_message());
            return *this;
        }

        template<typename expectedType>
        Matcher& toBeLessOrEqual(expectedType target)
        {
            typeCheck(target);
            bool result = toEqualMatcher::compare(_actual, target) || toBeLessMatcher::compare(_actual, target);
            _result = applyNot(result);
            throwException("toBeLessOrEqual", "Not less or equal");
            return *this;
        }
        template<typename expectedType>
        Matcher& toBeGreater(expectedType target)
        {
            typeCheck(target);
            bool result = !(toEqualMatcher::compare(_actual, target) || toBeLessMatcher::compare(_actual, target));
            _result = applyNot(result);
            throwException("toBeGreater", "Not Greater");
            return *this;
        }
        template<typename expectedType>
        Matcher& toBeGreaterOrEqual(expectedType target)
        {
            typeCheck(target);
            bool result = !(toBeLessMatcher::compare(_actual, target));
            _result = applyNot(result);
            throwException("toBeGreaterOrEqual", "Not Greater or equal");
            return *this;
        }


    protected:

        bool applyNot(bool result)
        {
            bool retVal = _not ? !result : result;
            _not = false;
            return retVal;
        }

        actualType _actual;

        bool       _not;


    };



}//end namespace ztest





#endif // Matcher_h__