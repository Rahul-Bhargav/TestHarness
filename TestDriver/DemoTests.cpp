#pragma once
#define IN_DLL
////////////////////////////////////////////////////////////////////////////
// DemoTests.cpp : multiple test classes to demo					      //
// ver 1.0                                                                //
//                                                                        //
// Application : OOD F18 Project 2			                              //
// Platform    : VS17 Community - Windows 10				              //
// Author:      Bhargav Rahul Surabhi, Syracuse University				  //
//              brsurabh@syr.edu					                      //
// Source      : Ammar Salman, EECS Department, Syracuse University       //
//               313/788-4694, hoplite.90@hotmail.com                     //
////////////////////////////////////////////////////////////////////////////
/*
*  Package description:
* ======================
*  This is a demo test driver DLL package. It follows the same
*  protocol defined in ITest.h package. For DllLoader, it doesn't care
*  if the TestDriver contains one or many Test Classes as it will attempt
*  to get the collection of ITest*.
*
*  Required Files:
*  ---------------
*  Test.h
*  TestContainer.h
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 13 Oct 2018
*  - first release
*/

#include "../TestUtilities/Test.h"
#include "../TestUtilities/TestsContainer.h"

#include <thread>
#include <iostream>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////
// Test class Demo1
class Demo1 : public TestUtilities::Test
{
public:
	Demo1() : TestUtilities::Test("Demo1", "Rahul") {}
	bool test()
	{
		_hostedLogger->work("\n  Testing Demo1 class");
		_hostedLogger->work("\n ---------------------");
		_hostedLogger->work("\n--Test always passes\n");
		return true;
	}
};

//////////////////////////////////////////////////////////////////
// Test class Demo2
class Demo2 : public TestUtilities::Test
{
public:
	Demo2() : TestUtilities::Test("Demo2", "Rahul") {}
	bool test()
	{
		_hostedLogger->work("\n  Testing Demo2 class");
		_hostedLogger->work("\n ---------------------");
		_hostedLogger->work("\n--Test always fails\n");
		return true;
	}
};


//////////////////////////////////////////////////////////////////
// Test class Demo3
class Demo3 : public TestUtilities::Test
{
public:
	Demo3() : TestUtilities::Test("Demo3", "Rahul") {}
	bool test()
	{
		_hostedLogger->work("\n  Testing Demo3 class");
		_hostedLogger->work("\n ---------------------");
		_hostedLogger->work("\n--Test always Throws\n");
		std::exception ex("\nwas thrown\n");
		throw ex;
		return true; // won't get here
	}
};

//////////////////////////////////////////////////////////////////
// Test class Demo4
class Demo4 : public TestUtilities::Test
{
public:
	Demo4() : TestUtilities::Test("Demo4", "Rahul") {}
	bool test()
	{
		_hostedLogger->work("\n  Testing Demo4 class");
		_hostedLogger->work("\n ---------------------");
		_hostedLogger->work("\n--Takes time to execute\n");
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		return true;
		return true; // won't get here
	}
};

//////////////////////////////////////////////////////////////////
// Container that's responsible for returning a collection of the
// previous 2 test classes. It will return a collection of:
// 1) ITest* that points to an instance of TestProcessCmdArgs
// 2) ITest* that points to an instance of TestConverter

__declspec(dllexport) TestUtilities::ITestsContainer* get_TestContainer()
{
	TestUtilities::ITestsContainer* testsContainer = new TestUtilities::TestsContainer();
	TestUtilities::TestPtr demo1 = TestUtilities::TestPtr(new Demo1());
	TestUtilities::TestPtr demo2 = TestUtilities::TestPtr(new Demo2());
	TestUtilities::TestPtr demo3 = TestUtilities::TestPtr(new Demo3());
	TestUtilities::TestPtr demo4 = TestUtilities::TestPtr(new Demo4());
	testsContainer->addTest(demo1);
	testsContainer->addTest(demo2);
	testsContainer->addTest(demo3);
	testsContainer->addTest(demo4);

	return testsContainer;
}

