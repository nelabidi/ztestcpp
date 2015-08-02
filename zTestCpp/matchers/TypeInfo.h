//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TypeInfo.h
// PURPOSE:
// DATE: 2015/08/02
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef TypeInfo_h__
#define TypeInfo_h__



namespace ztest {

    namespace detail {

        /*template<typename T>
        struct type_info_base
        {
        typedef T TypeInfo;

        };*/
        template<typename T, bool i = false, bool f = false>
        struct type_info
        {
            typedef T type;
            static const bool is_integral = i;
            static const bool is_float = f;
            static const bool is_numeric = is_integral || is_float;
        };

        template<> struct type_info<bool> : public type_info < bool, true > {};
        template<> struct type_info<char> : public type_info < char, true > {};
        template<> struct type_info<short> : public type_info < short, true > {};
        template<> struct type_info<long> : public type_info < long, true > {};

        template<> struct type_info<int> : public type_info < int, true > {};
        template<> struct type_info<long long> : public type_info < long long, true > {};
        template<> struct type_info<float> : public type_info < float, true, true > {};
        template<> struct type_info<double> : public type_info < double, true, true > {};


    }
}



#endif // TypeInfo_h__