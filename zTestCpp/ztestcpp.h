//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  ztestcpp.h
// PURPOSE:
// DATE: 2015/07/31
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef ztestcpp_h__
#define ztestcpp_h__


#include <string>
#include <map>
//#include <set>
//#include <list>
#include <vector>
#include <sstream>


#include <iostream>
using namespace std;

#define XCONCAT_I(a,b) a ## b
#define XCONCAT(a,b) XCONCAT_I(a,b)
#define GENERATE_UNIQUE_ID(x)  XCONCAT(x,XCONCAT(_,__LINE__))


namespace ztest {
//forward declaration

template<typename testSuite> struct TestSuiteRunner;



struct  TestCaseInfo
{
    std::string fullName;
    std::string name;
    std::string file;
    int line;
};

struct TestCaseFilter
{
    virtual bool filter(TestCaseInfo& testCaseInfo) = 0;
};


struct TestSuiteRunnerBase
{
    virtual void Run() = 0;
    virtual int getLine() = 0;
    virtual std::string getFile() = 0;
    virtual std::string getName() = 0;
    virtual int getTestCasesCount() = 0;
    virtual TestCaseInfo getTestCase(int index) = 0;
    virtual TestCaseInfo getCurrentTestCase() = 0;
    virtual void setTestCaseFilter(TestCaseFilter *filter) = 0;
};

//template<typename testSuite> struct TestSuiteRunner;

template<typename testSuite>
struct TestSuiteBase
{
    typedef testSuite CURRENT_TESTSUITE;

    void setUp()
    {
        cout << "IN >> TestSuiteImpl::setUp" << endl;
    }

    void tearDown()
    {
        cout << "IN >> TestSuiteImpl::tearDown" << endl;
    }

    void beforeEach()
    {
        cout << "TestSuiteImpl::beforeEach" << endl;
    }
    void afterEach()
    {
        cout << "TestSuiteImpl::afterEach" << endl;
    }

    std::string getName()
    {
        return _runner->getName();
    }

    std::string getFile()
    {
        return _runner->getFile();
    }

    int     getLine()
    {
        return _runner->getLine();
    }

    std::string getTestCaseName()
    {
        return _runner->getCurrentTestCase().name;
    }
    std::string getTestCaseFullName()
    {
        return _runner->getCurrentTestCase().fullName;
    }

private:

    friend struct TestSuiteRunner < testSuite > ;
    /*  std::string _name;
      std::string _file;
      int         _line;*/
    void setRunner(TestSuiteRunner< testSuite > * runner)
    {
        _runner = runner;
    }

    TestSuiteRunner < testSuite >* _runner;
};





template<typename testSuite>
struct TestSuiteRunner : public TestSuiteRunnerBase
{
    typedef void (testSuite::*MethodPtr)(void);

    //////////////////////////////////////////////////////////////////////////
    // TestSuiteRunnerBase  Interface implementation
    //////////////////////////////////////////////////////////////////////////

    virtual int getLine()
    {
        return _line;
    }

    virtual std::string getFile()
    {
        return _file;
    }

    virtual std::string getName()
    {
        return _name;
    }

    virtual void Run()
    {
        //TODO: filter and run
        testSuite * p = &_testSuite; //new testSuite();

        p->setRunner(this);

        p->setUp();

        //for each test case run
        for (int i = 0; i < getTestCasesCount() ; i++)
        {
            //TODO: filter and run
            _currentTestCase = i;
            MethodPtr ptr =  getTestCases()[i].ptr;
            (p->*ptr)();
        }
    }

    virtual int getTestCasesCount()
    {
        return getTestCases().size();
    }

    virtual TestCaseInfo getTestCase(int index)
    {
        if (index >= getTestCasesCount())
            throw std::exception("Invalid TestCase index.");

        TestCaseInfo info;
        TestCase testCase = getTestCases()[index];
        info.file = testCase.file;
        info.line = testCase.line;
        info.name = testCase.name;
        info.fullName = _name + " " + info.name;

        return info;
    }


    virtual TestCaseInfo getCurrentTestCase()
    {
        return getTestCase(_currentTestCase);
    }

    virtual void setTestCaseFilter(TestCaseFilter *filter)
    {
        _filter = filter;
    }

    //////////////////////////////////////////////////////////////////////////
    // Public Methods
    //////////////////////////////////////////////////////////////////////////
    static void addTestCase(MethodPtr ptr, const char *name, const char *file, int line)
    {
        TestCase info;
        info.file = file;
        info.line = line;
        info.name = name;
        info.ptr = ptr;
        getTestCases().push_back(info);
    }

    TestSuiteRunner(const char *name, const char *file, int line)
        : _name(name),
          _line(line),
          _file(file)
    {
        _filter = nullptr;
        _currentTestCase = -1;
    }

private:

    struct TestCase;
    typedef std::vector<TestCase> TestCasesList;

    struct TestCase : public TestCaseInfo
    {
        MethodPtr ptr;
    };

    static TestCasesList& getTestCases()
    {
        static TestCasesList  list;
        return list;
    }

    std::string _name;
    std::string _file;
    int         _line;
    int         _currentTestCase;

    TestCaseFilter *_filter;

    testSuite  _testSuite;


};

struct TestRunner
{
    template<typename suiteRunner>
    static void RegisterTestSuiteRunner(const char *name, const char *file, int line)
    {
        //check if runner is already registered unique
        if (!isRunnerRegistered(name, file, line))
        {
            suiteRunner *runner = new suiteRunner(name, file, line);
            addRunner(runner);
            runner->Run();
        }

    }

private:
    static bool isRunnerRegistered(const char *name, const char *file, int line)
    {
        std::stringstream ss;
        ss << name << file << line;
        std::string key(ss.str());
        return getRunnersMap().find(key) != getRunnersMap().end();
    }
    static void addRunner(TestSuiteRunnerBase *runner)
    {
        std::stringstream ss;
        ss << runner->getName() << runner->getFile() << runner->getLine();
        std::string key(ss.str());
        getRunners().push_back(runner);
        getRunnersMap()[key] = getRunners().size() - 1;
    }
    static std::map<std::string, int> & getRunnersMap()
    {
        static  std::map<std::string, int> runnersMap;
        return runnersMap;
    }
    static std::vector<TestSuiteRunnerBase*>& getRunners()
    {
        static std::vector<TestSuiteRunnerBase*> runners;
        return runners;
    }
};



template<typename T>
struct TestSuiteRegistrar //: public TestSuiteRegistery
{
    TestSuiteRegistrar(const char *name, const char *file, int line)
    {
        TestRunner::RegisterTestSuiteRunner < TestSuiteRunner<T>>(name, file, line);
    }
};

//testCase
template<typename testSuite>
struct TestCaseRegistry
{
    typedef void (testSuite::*MethodPtr)(void);
    static void RegsiterTestCase(MethodPtr ptr, const char *name, const char *file, int line)
    {

    }
};

} //end namespace ztest


#define TESTSUITE_REGISTRATION(testSuiteId,testSuiteName)\
struct testSuiteId;\
static ztest::TestSuiteRegistrar<testSuiteId> TestSuiteRegistrar(testSuiteName, __FILE__, __LINE__);\
struct testSuiteId : public ztest::TestSuiteBase<testSuiteId>

// specs/describe macros
#define describe(testSuiteName) \
TESTSUITE_REGISTRATION(GENERATE_UNIQUE_ID(TestSuite), testSuiteName)

//ztest::TestCaseRegistry::RegsiterTestCase<CURRENT_TESTSUITE>(  testCaseName, __FILE__, __LINE__);

//

#define TESTCASE_REGISTRATION(testCaseId,testCaseName)\
struct XCONCAT(testCaseId,  registrar) {\
    XCONCAT(testCaseId , registrar )() \
    { \
        ztest::TestSuiteRunner<CURRENT_TESTSUITE>::addTestCase(&CURRENT_TESTSUITE::testCaseId, testCaseName, __FILE__, __LINE__);\
    } \
} XCONCAT(testCaseId, registrar);\
void testCaseId()


#define it(testCaseName) \
TESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)


//helper macro
//#define tearDown() void tearDown()
//#define setUp() void setUp()





















#endif // ztestcpp_h__