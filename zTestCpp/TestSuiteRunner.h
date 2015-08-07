//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TestSuiteRunner.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////

#ifndef TestSuiteRunner_h__
#define TestSuiteRunner_h__

namespace ztest {




    template<typename testSuite>
    struct TestSuiteRunnerImpl : public TestSuiteRunner
    {
        typedef void (testSuite::*MethodPtr)(void);

        //////////////////////////////////////////////////////////////////////////
        // TestSuiteRunner  Interface implementation
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

        virtual void Run(TestListener* listener = 0 )
        {
            if (_isRunning)     return;

            //check if this testSuite is enabled the return from the filter should be true
            if (!isTestSuiteEnabled())
                return;

            NullListener _listener;
            if (listener == 0)
            {
                listener = &_listener;
            }

            _isRunning = true;
            //setup
            testSuite * p = &_testSuite;
            p->setRunner(this);

            listener->TestSuiteStart(*this);
            p->setUp();

            //for each testcase check if enabled and run it
            for (int i = 0; i < getTestCasesCount(); i++)
            {
                //set current test case
                _currentTestCase = i;
                TestCaseInfo caseInfo = getCurrentTestCase();
                //check if enabled
                if (isTestCaseEnabled(caseInfo))
                {
                    listener->TestCaseStart(caseInfo);
                    p->beforeEach();

                    MethodPtr ptr = getTestCases()[i].ptr;

                    try
                    {
                        (p->*ptr)();
                        listener->TestCaseSuccess(caseInfo);
                    }
                    catch (const Exception& e)
                    {
                        listener->TestCaseFailure(caseInfo, e);
                    }

                    p->afterEach();
                    listener->TestCaseEnd(caseInfo);
                }
            }
            p->tearDown();
            listener->TestSuiteEnd(*this);
            _isRunning = false;
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

        TestSuiteRunnerImpl(const char *name, const char *file, int line)
            : _name(name),
              _line(line),
              _file(file)
        {
            _filter = nullptr;
            _currentTestCase = -1;
            _isRunning = false;
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
        bool isTestCaseEnabled(const TestCaseInfo& info)
        {
            return _filter != nullptr ? _filter->filterTestCase(info) : true;
        }


        bool        _isRunning;
        std::string _name;
        std::string _file;
        int         _line;
        int         _currentTestCase;

        TestCaseFilter *_filter;

        testSuite  _testSuite;



    };

} //end namespace ztest


#endif // TestSuiteRunner_h__