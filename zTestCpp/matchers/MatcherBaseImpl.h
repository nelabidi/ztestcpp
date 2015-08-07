//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
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


    template<typename matcherClass>
    struct MatcherBaseImp : MatcherBase
    {

        MatcherBaseImp(const char *file, int line)
            : MatcherBase(file, line)
        {
        }

        matcherClass & not()
        {
            MatcherBase::not();
            return getMatcher();
        }

        template<typename expectedType>
        matcherClass& toBe(expectedType target)
        {
            _result = toBeMatcher::compare(getMatcher()._actual, target);
            _result = applyNot(_result);
            throwException("toBe", toBeMatcher::fail_message());
            return getMatcher();
        }

        template<typename expectedType>
        matcherClass& toBeEqual(expectedType target)
        {
            toBe(target);
            return toMatch<expectedType, detail::toEqual>("toBeEqual", target);
        }
        template<typename expectedType>
        matcherClass& toEqual(expectedType target)
        {
            return toMatch<expectedType, detail::toEqual>("toEqual", target);
        }

        template<typename expectedType>
        matcherClass& toBeNotEqual(expectedType target)
        {
            toBe(target);
            not();
            return toMatch<expectedType, detail::toEqual>("toBeNotEqual", target);
        }

        template<typename expectedType>
        matcherClass& toNotEqual(expectedType target)
        {
            not();
            return toMatch<expectedType, detail::toEqual>("toNotEqual", target);
        }



        template<typename validator, typename expectedType>
        matcherClass& toValidate(validator, expectedType target)
        {
            _result = validator::compare(getMatcher()._actual, target);
            _result = applyNot(_result);
            throwException("toValidate", validator::fail_message());
            return getMatcher();
        }


    protected:
        template<typename expectedType, typename Matcher>
        matcherClass& toMatch(const char *ruleName, expectedType target)
        {
            _result = Matcher::compare(getMatcher()._actual, target);
            _result = applyNot(_result);
            throwException(ruleName, Matcher::fail_message());
            return getMatcher();
        }

    private:
        matcherClass& getMatcher()
        {
            return static_cast<matcherClass&>(*this);
        }

    };












}


#endif // MatcherBaseImpl_h__