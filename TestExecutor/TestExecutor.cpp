#pragma
/////////////////////////////////////////////////////////////////////
// TestExecutor.cpp - Definitions of the functions in TestExecutor //
// ver 1.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include "TestExecutor.h"
#include "../LoggerUtilities/Logger.h"
#include "../TestUtilities/TestsContainer.h"
#include "../TestUtilities/ITest.h"
#include "../HostedUtilities/IHostedResource.h"
#include <memory>
#include <string>

namespace TestExecutor {


	TestExecutor::TestExecutor(SptrHostableLogger hostableLogger) : _hostableLogger(hostableLogger)
	{
	}


	TestExecutor::~TestExecutor()
	{
	}

	bool TestExecutor::RunSingleTest(TestUtilities::TestPtr test) 
	{
		bool result = false;
		try
		{
			result = test->test();  // execute test which may throw an exception
			auto logInfo = LoggerUtilities::TestInfo{ test->getName(), test->getAuthor(), result };
			_hostableLogger->LogResult(logInfo);
		}
		catch (std::exception& ex)
		{
			auto logInfo = LoggerUtilities::TestInfo{ test->getName(), test->getAuthor(), false, false, &ex};
			_hostableLogger->LogResult(logInfo);
		}
		return result;
	}

	bool TestExecutor::TestExecutor::runTests(ITRPtr testContainer)
	{
		bool result = true;
		for (auto item : testContainer->AllTests())
		{
			bool tResult = RunSingleTest(item);
			if (tResult == false)
				result = false;
		}
		return result;
	}
}

#ifdef TEST_TESTEXECUTOR

class Test2 : public TestUtilities::ITest
{
public:
	bool test()
	{
		return false;
	}

	// Inherited via ITest
	virtual std::string getName() override
	{
		return std::string();
	}
	virtual std::string getAuthor() override
	{
		return std::string();
	}
	virtual void acceptHostedLogger(TestUtilities::LoggerHostedResourcePtr hostedResource) override
	{
	}
	virtual TestUtilities::LoggerHostedResourcePtr getHostedLogger() override
	{
		return TestUtilities::LoggerHostedResourcePtr();
	}
};

class Test3 : public TestUtilities::ITest
{
public:
	bool test()
	{
		std::exception ex("\n  -- this test always throws -- \n\n");
		throw ex;
		return true;
	}

	// Inherited via ITest
	virtual std::string getName() override
	{
		return std::string();
	}
	virtual std::string getAuthor() override
	{
		return std::string();
	}
	virtual void acceptHostedLogger(TestUtilities::LoggerHostedResourcePtr hostedResource) override
	{
	}
	virtual TestUtilities::LoggerHostedResourcePtr getHostedLogger() override
	{
		return TestUtilities::LoggerHostedResourcePtr();
	}
};

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Please enter the directory for the tests";
	}
	std::string path = argv[1];
	TestUtilities::ITestsContainer* testsContainer = new TestUtilities::TestsContainer();
	TestUtilities::ITest* test2 = new Test2();
	TestUtilities::ITest* test3 = new Test3();
	testsContainer->addTest(std::shared_ptr<TestUtilities::ITest>(test2));
	testsContainer->addTest(std::shared_ptr<TestUtilities::ITest>(test3));

	auto testLogger = std::shared_ptr<LoggerUtilities::HostableTestLogger>(new LoggerUtilities::HostableTestLogger());
	testLogger->AddStream(std::cout, "console");

	TestExecutor::TestExecutor executor = TestExecutor::TestExecutor(testLogger);
	bool result = executor.runTests(testsContainer);
	std::cin.get();
	std::cout << "\n\n";

	return 0;
}

#endif // TEST_TESTEXECUTOR

