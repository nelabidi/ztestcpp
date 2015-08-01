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
#include <vector>
#include <sstream>


//#define ENABLE_LOGING

#ifdef ENABLE_LOGING
#include <iostream>
using namespace std;
#define LOG(msg)  cout << msg <<endl;
#else
#define LOG(msg)
#endif // ENABLE_LOGING




#define XCONCAT_I(a,b) a ## b
#define XCONCAT(a,b) XCONCAT_I(a,b)
#define GENERATE_UNIQUE_ID(x)  XCONCAT(x,XCONCAT(_,__LINE__))


#define ZTEST_VERIOSN  "1.0.0"

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
    virtual bool filterTestCase(TestCaseInfo& testCaseInfo) = 0;
    virtual bool filterTestSuite(std::string& testSuiteName) = 0;
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

typedef std::vector<TestSuiteRunnerBase*> TestSuiteRunnerList;

//template<typename testSuite> struct TestSuiteRunner;

template<typename testSuite>
struct TestSuiteBase
{
    typedef testSuite CURRENT_TESTSUITE;

    void setUp()
    {
        //cout << >> TestSuiteImpl::setUp" << endl;
        LOG("-> TestSuiteImpl::setUp");
    }

    void tearDown()
    {
        LOG("-> TestSuiteImpl::tearDown");
    }

    void beforeEach()
    {
        LOG("-> TestSuiteImpl::beforeEach");
    }
    void afterEach()
    {
        LOG("-> TestSuiteImpl::afterEach");
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
        //check if this testSuite is enabled the return from the filter should be true
        if (!isTestSuiteEnabled())
            return;
        //setup
        testSuite * p = &_testSuite;
        p->setRunner(this);
        p->setUp();

        //for each testcase test if enabled and runn it run
        for (int i = 0; i < getTestCasesCount() ; i++)
        {
            //set current test case
            _currentTestCase = i;
            //check if enabled
            if (isTestCaseEnabled(getCurrentTestCase()))
            {
                p->beforeEach();

                //TODO: handle execptions/assertions here

                MethodPtr ptr = getTestCases()[i].ptr;
                (p->*ptr)();

                p->afterEach();
            }
        }
        p->tearDown();
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

    bool isTestSuiteEnabled()
    {
        return _filter != nullptr ? _filter->filterTestSuite(this->getName()) : true;
    }
    bool isTestCaseEnabled(TestCaseInfo& info)
    {
        return _filter != nullptr ? _filter->filterTestCase(info) : true;
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
        }
    }
    static void getAllRunners(TestSuiteRunnerList & runners)
    {
        runners = getRunners();
    }

    static void RunAll()
    {
        TestSuiteRunnerList& runners = getRunners();
        for (unsigned int i = 0; i < runners.size(); i++)
        {
            runners[i]->Run();
        }
    }

    static TestSuiteRunnerBase* findRunner(const char* name)
    {
        TestSuiteRunnerList& runners = getRunners();
        std::string strName(name);

        for (unsigned int i = 0; i < runners.size(); i++)
        {
            if(runners[i]->getName() == strName)
                return runners[i];
        }
        return nullptr;
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
    static TestSuiteRunnerList& getRunners()
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
struct XCONCAT(testCaseId,  reg) {\
    XCONCAT(testCaseId , reg )() \
    { \
        ztest::TestSuiteRunner<CURRENT_TESTSUITE>::addTestCase(&CURRENT_TESTSUITE::testCaseId, testCaseName, __FILE__, __LINE__);\
    } \
} XCONCAT(testCaseId, reg);\
void testCaseId()


#define it(testCaseName) \
TESTCASE_REGISTRATION(GENERATE_UNIQUE_ID(testCase), testCaseName)


//helper macro
//#define tearDown() void tearDown()
//#define setUp() void setUp()





















#endif // ztestcpp_h__