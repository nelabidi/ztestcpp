//////////////////////////////////////////////////////////////////////////
//
// PROJECT:
// FILE:  TestRunner.h
// PURPOSE:
// DATE: 2015/08/05
// NOTES:
//
//////////////////////////////////////////////////////////////////////////


#ifndef TestRunner_h__
#define TestRunner_h__




namespace ztest {


    struct TestRunner : NullListener
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

        static int RunAll()
        {
            DefaultOutputer outputer;
            TestRunner   testrunner(&outputer);
            return testrunner.Run();
        }

        static TestSuiteRunner* findRunner(const char* name)
        {
            TestSuiteRunnerList& runners = getRunners();
            std::string strName(name);

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

        int Run()
        {
            _listeners.addListener(this);
            _listeners.addListener(_outputer);

            _listeners.TestStart();

            TestSuiteRunnerList& runners = getRunners();
            for (unsigned int i = 0; i < runners.size(); i++)
            {
                runners[i]->Run(&_listeners);
            }
            _listeners.TestEnd();

            _outputer->OutPutTestResults(_results);
            return _results.failedCount();
        }

        void addListener(TestListener *listener)
        {
            _listeners.addListener(listener);
        }

        //Listen on test case results
        virtual void TestCaseSuccess(const TestCaseInfo& testCase)
        {
            _results.addSucceeded(testCase);
        }

        virtual void TestCaseFailure(const TestCaseInfo& testCase, const Exception &e)
        {
            _results.addFailed(testCase, e.getFile(), e.getLine(), e.what());
        }

    private:
        static bool isRunnerRegistered(const char *name, const char *file, int line)
        {
            std::stringstream ss;
            ss << name << file << line;
            std::string key(ss.str());
            return getRunnersMap().find(key) != getRunnersMap().end();
        }
        static void addRunner(TestSuiteRunner *runner)
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
            static std::vector<TestSuiteRunner*> runners;
            return runners;
        }
        //listeners container
        struct ListenersContainer : TestListener
        {

            void addListener(TestListener * l)
            {
                _listeners.push_back(l);
            }
            //TestListener interface
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

        OutPuter            *_outputer;
        TestResults         _results;
        ListenersContainer  _listeners;

    };


}// end namespace ztest




#endif // TestRunner_h__