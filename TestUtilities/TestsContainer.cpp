#pragma
/////////////////////////////////////////////////////////////////////
// TestContainer.cpp -  The test container class definitions	   //
// ver 1.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>
#include <memory>
#include "TestsContainer.h"
#include "Test.h"


namespace TestUtilities
{
	TestsContainer::TestsContainer()
	{
		_tests = TestPtrVec(0);
	}
	
	TestsContainer::~TestsContainer()
	{
	}
	
	bool TestsContainer::addTest(TestPtr item)
	{
		try
		{
			this->_tests.push_back(item);
		}
		catch (const std::exception& ex)
		{
			std::cout << "Cannot add the test to the list see the below exception for additional details \n." << ex.what();
			return false;
		}
		return true;
	}


	bool TestsContainer::deleteTest(std::string name)
	{
		try
		{
			//Find the test item based on the test name and erase the object from the vector
			auto it = std::find_if(_tests.begin(), _tests.end(), [&name](TestPtr test) {return test->getName() == name; });
			if (it != _tests.end())
			{
				_tests.erase(it);
			}
			else
			{
				std::cout << "Cannot find the test to delete.";
				return false;
			}
			// TODO: implement erase   _tests.erase(std::remove(_tests.begin(), _tests.end(), item), _tests.end());
		}
		catch (const std::exception& ex)
		{
			std::cout << "Cannot delete the test from the list see the below exception for additional details \n." << ex.what();
			return false;
		}
		return false;
	}

	bool TestsContainer::clearTests()
	{
		try
		{
			_tests.clear();
		}
		catch (const std::exception& ex)
		{
			std::cout << "Cannot clear the tests.\n " << ex.what();
		}
		return false;
	}
	const TestPtrVec TestsContainer::AllTests()
	{
		return _tests;
	}

#ifdef TEST_TESTUTILITIES
	std::ostream& out = std::cout;

	class TestPasses : public Test
	{
	public:
		TestPasses(std::string name, std::string author) : Test(name, author) {}
		bool test() override { return true; }							//Is override necessary?
		~TestPasses() { out << "\n  -- deleting TestPasses"; }
	};

	class TestFails : public Test
	{
	public:
		TestFails(std::string name, std::string author) : Test(name, author) {}
		bool test() override { return false; }
		~TestFails() { out << "\n  -- deleting TestFails"; }
	};

	class TestThrows : public Test
	{
	public:
		TestThrows(std::string name, std::string author) : Test(name, author) {}
		bool test()
		{
			std::exception ex("\n  -- this test always throws -- ");
			throw ex;
		}
		~TestThrows() { out << "\n  -- deleting TestThrows"; }
	};

	// define a test that tests other code

	class SampleCode
	{
	public:
		SampleCode(const std::string& msg) : msg_(msg) {}

		std::string result()
		{
			return "result" + msg_;
		}
		~SampleCode() { out << "\n  -- deleting SampleCode\n"; }
	private:
		std::string msg_;
	};

	class TestCode : public Test
	{
	public:
		TestCode(const std::string& msg, std::string name, std::string author) : msg_(msg), Test(name, author) {}
		bool test()
		{
			out << "\n  test input = \"" + msg_ << "\"";     // logging test input

			SampleCode ctt(msg_);
			std::string result = ctt.result();

			out << "\n  test output = \"" + result << "\"";  //logging test output
			return (result == "result" + msg_);
		}
		~TestCode() { out << "\n  -- deleting TestCode"; }
	private:
		std::string msg_;
	};
#endif
}
