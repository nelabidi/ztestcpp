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
                if (runners[i]->getName() == strName)
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


}// end namespace ztest




#endif // TestRunner_h__