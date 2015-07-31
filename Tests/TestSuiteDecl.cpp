#include "stdafx.h"



#include <ztestcpp.h>

namespace {


describe("TestSuite 1")
{
    int member;

    void setUp()
    {
        cout << "in setUp: " << getName() << endl;
    }

    void doSomething()
    {

    }

};

} //end namespace