// Tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <ztestcpp.h>

using namespace std;
namespace {

describe("TestSuite 2")
{
    void setUp()
    {

        cout << "in setUp: " << getName() << endl;
    }

    it("I want to sleep, please!")
    {
        cout << "in spec: " << getTestCaseName() << endl;
    }

};

}

struct TestSuiteRegistery
{
    typedef map<string, void* > Map;
    static Map & getMap()
    {
        static Map registery;
        return registery;
    }
    static void dump()
    {
        Map::iterator it;
        for (it = getMap().begin(); it != getMap().end(); it++)
        {
            cout << "key: " << it->first << " , " << it->second << endl;
        }
    }
};





/*struct TestSuite1;
static TestSuiteRegistrar<TestSuite1> TestSuite1Registrar("TestSuite1", __FILE__, __LINE__);
struct TestSuite1 : public TestSuiteBase<TestSuite1>
{

    void setUp()
    {
        cout << "in TestSuite1::setUp" << endl;
    }

    void tearDown()
    {
        cout << "in TestSuite1::tearDown" << endl;
    }


    void beforeEach()
    {

    }
    void afterEach() {}


    void spec1()
    {
        cout << "in spec1" << endl;
    }

    void spec2()
    {
        cout << "in spec2" << endl;
    }
};
*/



void TestSuiteRegistrationTest()
{

    TestSuiteRegistery::dump();
}


int main(int argc, char* argv[])
{
    cout << "zTest Framework for c++" << endl;

    TestSuiteRegistrationTest();

    return 0;
}

