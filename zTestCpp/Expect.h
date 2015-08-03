//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  Expect.h
// PURPOSE:
// DATE: 2015/08/01
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef Expect_h__
#define Expect_h__




#include "Exception.h"

#include "matchers/MatcherBase.h"
#include "matchers/Matcher.h"
#include "matchers/PointerMatcher.h"

#include "matchers/TypeInfo.h"

namespace ztest {


#if 0
    template<typename actualType>
    struct Matcher
    {
        /*struct ExpectedType
        {

        };*/

        Matcher(actualType actual, const char *file, int line)
            : _actual(actual),
              _line(line),
              _file(file)
        {
        }
        template<typename expectedType>
        void toBe(expectedType)
        {
            _result = false;
            throwException("toBe", "Not Same type");
        }
        template<>
        void toBe<actualType>(actualType )
        {
            _result = true;
        }
        template<typename expectedType>
        void toEqual(expectedType target)
        {
            toBe(target);
            _result = _result && compare(target, _actual);
            throwException("toEqual", "Not equal");

        }
        template<typename actualType, typename expectedType>
        bool compare(const actualType& , const expectedType &)
        {
            return false;
        }

        template<>
        bool compare<actualType, actualType>(const actualType& lh, const actualType &rh)
        {
            return lh == rh;
        }

    protected:
        void throwException(const char * from, const char *message)
        {
            if (!_result)
            {
                std::string msg(from);
                msg += " Failed with: " + std::string(message);
                throw Exception(msg, _file, _line);
            }
        }

        actualType _actual;
        const char* _file;
        int         _line;
        bool        _result;
    };


    /*template<typename actualType>
    struct Matcher : public detail::type_info< actualType >
    {
        Matcher(actualType actual, const char *file, int line)
            : _actual(actual),
              _line(line),
              _file(file)
        {
        }

        actualType _actual;
        const char* _file;
        int         _line;
    };*/


    /*template<typename T>
    struct IntegralMatcher
    {
        typedef detail::type_info<T>::type actualType;

        void toEqual()
        {

        }

        IntegralMatcher(actualType actual, const char *file, int line)
            : _actual(actual),
              _line(line),
              _file(file)
        {
        }

        actualType _actual;
        const char* _file;
        int         _line;
    };*/


    template<typename T>
    struct MatcherBase
    {
        typedef T ActualType;

        ActualType _actual;
        const char* _file;
        int         _line;
        bool        _result;

        void throwException(const char * from, const char *message)
        {
            if (!_result)
            {
                std::string msg(from);
                msg += " Failed with: " + std::string(message);
                throw Exception(msg, _file, _line);
            }
        }

    };

    template<typename actualType>
    struct ToBeMatcher  //: public MatcherBase<actualType>
    {
        template<typename expectedType>
        void toBe(expectedType)
        {
            _result = false;
            throwException("toBe", "Not Same type");
        }
        template<>
        void toBe<actualType>(actualType)
        {
            _result = true;
        }
    };

    template<typename actualType>
    struct EqualityMatcher  //: public MatcherBase < actualType >
    {
        template<typename expectedType>
        void toEqual(expectedType target)
        {
            _result = _result && compare(target, _actual);
            throwException("toEqual", "Not equal");
        }
        template<typename actualType, typename expectedType>
        bool compare(const actualType&, const expectedType &)
        {
            return false;
        }
        template<>
        bool compare<actualType, actualType>(const actualType& lh, const actualType &rh)
        {
            return lh == rh;
        }
    };

    template<typename T>
    struct Matchers : EqualityMatcher<T>, ToBeMatcher<T>, MatcherBase<T>
    {
        Matchers(T actual, const char *file, int line)
            : _actual(actual),
              _line(line),
              _file(file)
        {
        }
    };

#endif

    typedef enum MatcherKind
    {
        INTEGRAL_MATCHER = 1,
        NOT_INTEGRAL_MATCHER = 0,

    };

    template<typename T, MatcherKind kind>
    struct MatcherImpl : public Matcher < T >
    {
        MatcherImpl(T actual, const char *file, int line) :
            Matcher(actual, file, line)
        {
        }
    };


    template<typename T>
    struct MatcherImpl<T, INTEGRAL_MATCHER> : public Matcher<T>
    {
        MatcherImpl(T actual, const char *file, int line):
            Matcher(actual, file, line)
        {
        }
    };


    template<typename T >
    struct  MatcherKindGetter
    {
        typedef detail::type_info<T> info;

        static const MatcherKind kind = (info::is_integral) ? INTEGRAL_MATCHER : NOT_INTEGRAL_MATCHER;
    };


    template<typename actualType>
    static Matcher<actualType>
    Expect(actualType actual, const char *file = nullptr, int line = 0)
    {
        // return MatcherImpl<actualType, detail::type_info<actualType>::is_arithmetic>(actual, file, line);
        //if(detail::type_info<actualType>::is_integral)
        //    std::cout << "*** is integral \n";
        //return Matcher<actualType>(actual, file, line);

        return MatcherImpl<actualType, MatcherKindGetter<actualType>::kind >(actual, file, line);
    }


}// end namespace ztest





#endif // Expect_h__