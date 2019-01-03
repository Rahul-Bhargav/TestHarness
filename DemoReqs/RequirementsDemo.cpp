#pragma once
/////////////////////////////////////////////////////////////////////
// ReuirementsDemo.cpp - Register and export the tests from		   //
//						 RequirementsDemo.h						   //
// ver 2.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#define IN_DLL
#include "RequirementsDemo.h"


__declspec(dllexport) TestUtilities::ITestsContainer* get_TestContainer()
{
	std::string path = "../";
	TestUtilities::ITestsContainer* testsContainer = new TestUtilities::TestsContainer();
	TestUtilities::TestPtr test1 = TestUtilities::TestPtr(new TestReq1(path));
	TestUtilities::TestPtr test2a = TestUtilities::TestPtr(new TestReq2a(path));
	TestUtilities::TestPtr test2b = TestUtilities::TestPtr(new TestReq2b(path));
	TestUtilities::TestPtr test3 = TestUtilities::TestPtr(new TestReq3(path));
	TestUtilities::TestPtr test4a = TestUtilities::TestPtr(new TestReq4(path));
	TestUtilities::TestPtr test4b = TestUtilities::TestPtr(new TestReq5(path));
	TestUtilities::TestPtr test5b = TestUtilities::TestPtr(new TestReq6(path));
	TestUtilities::TestPtr test5c = TestUtilities::TestPtr(new TestReq7(path));
	TestUtilities::TestPtr test6a = TestUtilities::TestPtr(new TestReq8(path));
	TestUtilities::TestPtr test6b = TestUtilities::TestPtr(new TestReq9(path));
	TestUtilities::TestPtr test7a = TestUtilities::TestPtr(new TestReq10(path));

	testsContainer->addTest(test1);
	testsContainer->addTest(test2a);
	testsContainer->addTest(test2b);
	testsContainer->addTest(test3);
	testsContainer->addTest(test4a);
	testsContainer->addTest(test4b);
	testsContainer->addTest(test5b);
	testsContainer->addTest(test5c);
	testsContainer->addTest(test6a);
	testsContainer->addTest(test6b);
	testsContainer->addTest(test7a);

	return testsContainer;
}
