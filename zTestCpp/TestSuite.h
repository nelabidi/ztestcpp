//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TestSuite.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef TestSuite_h__
#define TestSuite_h__

namespace ztest {



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

        friend struct TestSuiteRunnerImpl < testSuite > ;
        void setRunner(TestSuiteRunnerImpl< testSuite > * runner)
        {
            _runner = runner;
        }

        TestSuiteRunnerImpl < testSuite >* _runner;
    };



    template<typename T>
    struct TestSuiteRegistrar //: public TestSuiteRegistery
    {
        TestSuiteRegistrar(const char *name, const char *file, int line)
        {
            TestRunner::RegisterTestSuiteRunner < TestSuiteRunnerImpl<T>>(name, file, line);
        }
    };





}// end namespace ztest



#endif // TestSuite_h__