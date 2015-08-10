//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  TestSuiteRunner.h
// PURPOSE: declare and implement the TestSuiteRunner class
// DATE: 2015/08/05

// NOTES:
//      for every test suite, there is a TestSuiteRunnerImpl object responsible of running it
//      and reporting running events.
//
//////////////////////////////////////////////////////////////////////////

#ifndef TestSuiteRunner_h__
#define TestSuiteRunner_h__

namespace ztest {

    /*!
     * \class   TestSuiteRunnerImpl
     *
     * \brief Implement TestSuiteRunner Interface
     */
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

        ///
        /// \brief Run the attached TestSuite
        ///
        ///
        /// \param[in] : TestListener object
        ///

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
            testSuite * suite = &_testSuite;
            suite->setRunner(this);

            //listener->TestSuiteStart(*this);
            //p->setUp();
            callSetup(suite, listener);

            //for each TestCase check if enabled and run it
            for (int i = 0; i < getTestCasesCount(); i++)
            {
                //set current test case
                _currentTestCase = i;
                TestCaseInfo caseInfo = getCurrentTestCase();
                //check if enabled
                if (isTestCaseEnabled(caseInfo))
                {
                    listener->TestCaseStart(caseInfo);
                    //p->beforeEach();
                    callBeforeEach(suite, listener);

                    MethodPtr ptr = getTestCases()[i].ptr;

                    try
                    {
                        (suite->*ptr)();
                        listener->TestCaseSuccess(caseInfo);
                    }
                    catch (const Exception& e)
                    {
                        listener->TestCaseFailure(caseInfo, e);
                    }

                    //p->afterEach();
                    callAfterEach(suite, listener);
                    listener->TestCaseEnd(caseInfo);
                }
            }
            callTearDown(suite, listener);
            // p->tearDown();
            //listener->TestSuiteEnd(*this);
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

        ///
        /// \brief  getCurrentTestCase
        ///
        /// \return Current running Test case
        ///
        virtual TestCaseInfo getCurrentTestCase()
        {
            return getTestCase(_currentTestCase);
        }
        /// Set the Test Case Filter, see TestCaseFilter for more info
        virtual void setTestCaseFilter(TestCaseFilter *filter)
        {
            _filter = filter;
        }

        //////////////////////////////////////////////////////////////////////////
        // Public Methods
        //////////////////////////////////////////////////////////////////////////

        // add a Test Case used by it macro to register a test case
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

        //Test Case internal data
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
        //testSuite Calls
        void callSetup(testSuite* suite, TestListener *listener)
        {
            listener->TestSuiteStart(*this);
            try
            {
                suite->setUp();
            }
            catch (const Exception &e)
            {
                TestCaseInfo info;
                info.fullName = "setUp of " + _name;
                info.file = _file;
                info.line = _line;
                listener->TestCaseFailure(info, e);
            }
        }

        void callTearDown(testSuite* suite, TestListener *listener)
        {
            try
            {
                suite->tearDown();
            }
            catch (const Exception &e)
            {
                TestCaseInfo info;
                info.fullName = "tearDown of " + _name;
                info.file = _file;
                info.line = _line;
                listener->TestCaseFailure(info, e);
            }
            listener->TestSuiteEnd(*this);
        }
        void callBeforeEach(testSuite* suite, TestListener *listener)
        {
            try
            {
                suite->beforeEach();
            }
            catch (const Exception &e)
            {
                TestCaseInfo info;
                info.fullName = "beforeEach of " + _name;
                info.file = _file;
                info.line = _line;
                listener->TestCaseFailure(info, e);
            }
        }

        void callAfterEach(testSuite* suite, TestListener *listener)
        {
            try
            {
                suite->afterEach();
            }
            catch (const Exception &e)
            {
                TestCaseInfo info;
                info.fullName = "afterEach of " + _name;
                info.file = _file;
                info.line = _line;
                listener->TestCaseFailure(info, e);
            }

        }

        bool        _isRunning; // running state
        std::string _name;      // Test Suite name
        std::string _file;      // Test Suite file
        int         _line;      // Test Suite line
        int         _currentTestCase; // current running test case index

        TestCaseFilter *_filter; // the test case filter object

        testSuite  _testSuite;  // the test suite instance


    };

} //end namespace ztest


#endif // TestSuiteRunner_h__