//////////////////////////////////////////////////////////////////////////
//
// PROJECT: zTestC++ (zTestCpp) C++ Testing framework
// FILE:  TestRunner.h
// PURPOSE: Test Runner implementation
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef TestRunner_h__
#define TestRunner_h__



namespace ztest {

    /*!
     * \class  TestRunner
     *
     * \brief Runs the registered TestSuiteRunners
     */
    struct TestRunner : NullListener
    {
        //called by TestSuiteRegistrar to register a TestSuiteRunner
        template<typename suiteRunner>
        static void RegisterTestSuiteRunner(const char *name, const char *file, int line)
        {
            //check if runner is already registered unique
            if (!isRunnerRegistered(name, file, line))
            {
                //TODO: implement RunnersRegistery to cleanup this pointers
                suiteRunner *runner = new suiteRunner(name, file, line);
                addRunner(runner);
            }
        }
        //return all the registered runners
        static void getAllRunners(TestSuiteRunnerList & runners)
        {
            runners = getRunners();
        }
        //run all the tests and return failed test counts
        static int RunAll()
        {
            DefaultOutputer outputer;
            TestRunner   testrunner(&outputer);
            return testrunner.Run();
        }

        static int RunAll(int argc, char* argv[])
        {
            //TODO: handle command line arguments
            argc;
            argv;
            return RunAll();
        }

        //Find TestSuite runner by it's name passed to describe
        static TestSuiteRunner* findRunner(const char* name)
        {
            TestSuiteRunnerList& runners = getRunners();
            std::string strName(name);

            //TODO: use a map to speed up the search
            for (unsigned int i = 0; i < runners.size(); i++)
            {
                if (runners[i]->getName() == strName)
                    return runners[i];
            }
            return nullptr;
        }

        TestRunner(OutPuter* outputer)
            : _outputer(outputer)
        {}

        //Run the registered Test Suites/ TestRunners
        int Run()
        {
            //add TestRunner as a listener to collect TestResult
            _listeners.addListener(this);
            _listeners.addListener(_outputer);
            //raise the TestStart events
            _listeners.TestStart();
            //call Run on all registred runners
            TestSuiteRunnerList& runners = getRunners();
            for (unsigned int i = 0; i < runners.size(); i++)
            {
                runners[i]->Run(&_listeners);
            }
            _listeners.TestEnd();
            //output the results
            _outputer->OutPutTestResults(_results);
            return _results.failedCount();
        }
        //register a TestListener
        void addListener(TestListener *listener)
        {
            _listeners.addListener(listener);
        }

        //////////////////////////////////////////////////////////////////////////
        // TestListener implementation:
        // Listen on test case success and Failure and update test results
        //////////////////////////////////////////////////////////////////////////
        virtual void TestCaseSuccess(const TestCaseInfo& testCase)
        {
            _results.addSucceeded(testCase);
        }
        virtual void TestCaseFailure(const TestCaseInfo& testCase, const Exception &e)
        {
            _results.addFailed(testCase, e.getFile(), e.getLine(), e.what());
        }

    private:

        //return true if a test runner with the same name,file and line is already registred
        static bool isRunnerRegistered(const char *name, const char *file, int line)
        {
            std::stringstream ss;
            ss << name << file << line;
            std::string key(ss.str());
            return getRunnersMap().find(key) != getRunnersMap().end();
        }
        // add test runner to the registry
        static void addRunner(TestSuiteRunner *runner)
        {
            std::stringstream ss;
            ss << runner->getName() << runner->getFile() << runner->getLine();
            std::string key(ss.str());
            getRunners().push_back(runner);
            getRunnersMap()[key] = getRunners().size() - 1;
        }
        // return test runners map for Test Runners lookup
        static std::map<std::string, int> & getRunnersMap()
        {
            static  std::map<std::string, int> runnersMap;
            return runnersMap;
        }

        static TestSuiteRunnerList& getRunners()
        {
            static std::vector<TestSuiteRunner*> runners;
            return runners;
        }

        /*!
         * \class ListenersContainer
         *
         * \brief delegate TestListerner methods to the registered listeners
         */
        struct ListenersContainer : TestListener
        {
            //register a test listener
            void addListener(TestListener * l)
            {
                _listeners.push_back(l);
            }
            //TestListener interface implementation
            virtual void TestStart()
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestStart();
                }
            }

            virtual void TestSuiteStart(const TestSuiteRunner& runner)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestSuiteStart(runner);
                }
            }

            virtual void TestCaseStart(const TestCaseInfo& testCaseInfo)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestCaseStart(testCaseInfo);
                }
            }

            virtual void TestCaseSuccess(const TestCaseInfo& testCaseInfo)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestCaseSuccess(testCaseInfo);
                }
            }

            virtual void TestCaseFailure(const TestCaseInfo& testCaseInfo, const Exception &e)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestCaseFailure(testCaseInfo, e);
                }
            }

            virtual void TestCaseEnd(const TestCaseInfo& testCaseInfo)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestCaseEnd(testCaseInfo);
                }
            }

            virtual void TestSuiteEnd(const TestSuiteRunner& runner)
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestSuiteEnd(runner);
                }
            }

            virtual void TestEnd()
            {
                for (unsigned int i = 0; i < _listeners.size(); i++)
                {
                    _listeners[i]->TestEnd();
                }
            }

        private:
            std::vector<TestListener*> _listeners;

        };

        //////////////////////////////////////////////////////////////////////////
        // private members
        //////////////////////////////////////////////////////////////////////////
        OutPuter            *_outputer; // the outputer object
        TestResults         _results;   // test results
        ListenersContainer  _listeners; //

    };


}// end namespace ztest




#endif // TestRunner_h__