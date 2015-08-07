//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  DefaultOutputer.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef DefaultOutputer_h__
#define DefaultOutputer_h__



#include "TestSuiteRunner.h"

namespace ztest {


    struct DefaultOutputer : TestListener
    {

        virtual void TestStart(const TestSuiteRunner& )
        {
        }

        virtual void TestCaseStart(const TestCaseInfo& )
        {

        }

        virtual void TestCaseSuccess(const TestCaseInfo& )
        {
            std::cerr << PASS_COLOR << "." << DEFAULT_COLOR;
        }

        virtual void TestCaseFailure(const TestCaseInfo& , const Exception &)
        {
            std::cerr << FAIL_COLOR << "X" << DEFAULT_COLOR;
        }

        virtual void TestCaseEnd(const TestCaseInfo& )
        {

        }

        virtual void TestEnd(const TestSuiteRunner& )
        {
            std::cerr << DEFAULT_COLOR << std::endl;
        }

    };



}  //end namespace ztest




#endif // DefaultOutputer_h__