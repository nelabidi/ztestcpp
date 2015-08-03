//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TypeInfoTest.cpp
// PURPOSE:
// DATE: 2015/08/03
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include <ztestcpp.h>

#include <iostream>
using namespace std;

//TODO: implement this test using ztestFrameWork

struct MyStruct
{
    MyStruct()
    {
        cout << ztest::detail::type_info<const int&>::is_numeric << ztest::detail::type_info<const int&>::name() << endl;
        cout << ztest::detail::type_info<int&>::is_numeric << ztest::detail::type_info<int&>::name() << endl;
        cout << ztest::detail::type_info<const int&>::is_ref << endl;
        cout << ztest::detail::type_info<const int&>::is_constant << endl;
        cout << ztest::detail::type_info<const int*&>::is_ptr << endl;
        cout << ztest::detail::type_info<const int&>::is_float << endl;

        cout << "-----------------------------------\n";

        cout << ztest::detail::type_info<const char *>::is_string << " " << ztest::detail::type_info<const char *>::name() << endl;
        cout << ztest::detail::type_info<char *>::is_string << " " << ztest::detail::type_info<char *>::name() << endl;
        cout << ztest::detail::type_info<const std::string&>::is_string << " " << ztest::detail::type_info<const std::string&>::name() << endl;
        cout << ztest::detail::type_info<std::string&>::is_string << " " << ztest::detail::type_info<std::string&>::name() << endl;
        cout << ztest::detail::type_info<std::string>::is_string << " " << ztest::detail::type_info<std::string>::name() << endl;

        cout << ztest::detail::type_info<char >::is_string << ztest::detail::type_info<char>::name() << endl;

        cout << typeid(ztest::detail::type_kind<int>::value).name() << " " << ztest::detail::type_info<int>::name() << endl;
        cout << typeid(ztest::detail::type_kind<int*>::value).name() << " " << ztest::detail::type_info<int*>::name() << endl;
        cout << typeid(ztest::detail::type_kind<int&>::value).name() << " " << ztest::detail::type_info<int&>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const int>::value).name() << " " << ztest::detail::type_info<const int>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const int*>::value).name() << " " << ztest::detail::type_info<const int*>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const int&>::value).name() << " " << ztest::detail::type_info<const int&>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const char>::value).name() << " " << ztest::detail::type_info<const char>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const short>::value).name() << " " << ztest::detail::type_info<const short>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const long long&>::value).name() << " " << ztest::detail::type_info<const long long&>::name() << endl;
        cout << "-----------------------------------\n";

        cout << typeid(ztest::detail::type_kind<float>::value).name() << " " << ztest::detail::type_info<float>::name() << endl;
        cout << typeid(ztest::detail::type_kind<float*>::value).name() << " " << ztest::detail::type_info<float*>::name() << endl;
        cout << typeid(ztest::detail::type_kind<float&>::value).name() << " " << ztest::detail::type_info<float&>::name() << endl;

        cout << typeid(ztest::detail::type_kind<char *>::value).name() << " " << ztest::detail::type_info<char *>::name() << endl;
        cout << typeid(ztest::detail::type_kind<const char*>::value).name() << " " << ztest::detail::type_info<const char*>::name() << endl;
        cout << typeid(ztest::detail::type_kind<std::string&>::value).name() << " " << ztest::detail::type_info<std::string &>::name() << endl;

        cout << typeid(ztest::detail::type_kind<unsigned char>::value).name() << " " << ztest::detail::type_info<unsigned char>::name() << endl;
        cout << typeid(ztest::detail::type_kind<signed const char>::value).name() << " " << ztest::detail::type_info<signed const char>::name() << endl;
        cout << typeid(ztest::detail::type_kind<long double>::value).name() << " " << ztest::detail::type_info<long double>::name() << endl;

    }
} ;