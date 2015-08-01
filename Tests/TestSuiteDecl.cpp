#include "stdafx.h"

#include <ztestcpp.h>
#include <iostream>



namespace {

using namespace std;

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