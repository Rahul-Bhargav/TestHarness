#pragma once
///////////////////////////////////////////////////////////////////////
// RequirementsDemo.h - All the tests that show the requirements     //
//																	 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes that shows the project requirements
*
* Required Files:
* ---------------
*   Test.h
*   TestsContainer.h
*   TestHelpers.h
*
* Maintenance History:
* --------------------
* ver 3.0 : 4 Dec 2018
* - Project 4 changes
* ver 2.0 : 18 Nov 2018
* - Project 3 changes
* ver 1.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none planned
*/

#include<iostream>
#include "../TestUtilities/Test.h"
#include "../TestUtilities/TestsContainer.h"
#include "../TestUtilities/TestHelpers.h"

using Path = std::string;
using Message = std::string;
using Line = size_t;
using File = std::string;
using Files = std::vector<File>;

class TestReq1 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Demonstrates use of C++
	*  Test Procedure:
	*  - Displays C++ files in project directory
	*/
private:
	const std::string path_;
public:
	TestReq1(const std::string& path) : path_(path),Test("Requirement 1", "Rahul") {}
	~TestReq1() { std::cout << "\n  deleting TestReq1"; }
	bool test()
	{
		Message msg = "Req #1 - Use C++";
		Path path = path_ + "/TestUtilities";
		return TestUtilities::TestHelpers::showDirContents(path, msg);
	}
};

class TestReq2a : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Demonstrates use of WPF
	*  Test Procedure:
	*  - Displays files of project source code that use.
	*/
private:
	const std::string path_;
public:
	TestReq2a(const std::string& path) : path_(path), Test("Requirement 2a", "Rahul") {}
	~TestReq2a() { std::cout << "\n  deleting TestReq2a"; }
	bool test()
	{
		Message msg = "Req #2a - use WPF";
		Path fileSpec = path_ + "/GUI";
		return TestUtilities::TestHelpers::showDirContents(fileSpec, msg);
	}
};

class TestReq2b : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Demonstrates use of WPF
	*  Test Procedure:
	*  - show files that have wpf code.
	*  - The demo has the WPF UI
	*/
private:
	const std::string path_;
public:
	TestReq2b(const std::string& path) : path_(path), Test("Requirement 2b", "Rahul") {}
	~TestReq2b() { std::cout << "\n  deleting TestReq2b"; }
	bool test()
	{
		Message msg = "Req #2b - use WPF for user display";
		Path fileSpec = path_ + "/GUI/MainWindow.xaml";
		return TestUtilities::TestHelpers::showFileLines(fileSpec, 1, 10, msg);
	}
};

class TestReq3 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*   Demonstrates That the client is non blocking
	*  Test Procedure:
	*  - Already shown in the demo
	*/
private:
	const std::string path_;
public:
	TestReq3(const std::string& path) : path_(path), Test("Requirement 3", "Rahul") {}
	~TestReq3() { std::cout << "\n  deleting TestReq3"; }
	bool test()
	{
		_hostedLogger->work("Req #3 - Demonstrates That the client is non blocking \n\n");
		_hostedLogger->work("This is already is the client demo that executed. \n\n");
		return true;
	}
};

class TestReq4 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*   Demonstrates the provision selecting dlls and send the test request.
	*   Also shows the test results
	*  Test Procedure:
	*  - Already shown in the demo
	*/
private:
	const std::string path_;
public:
	TestReq4(const std::string& path) : path_(path), Test("Requirement 4", "Rahul") {}
	~TestReq4() { std::cout << "\n  deleting TestReq4"; }
	bool test()
	{
		_hostedLogger->work("Req #4 - Demonstrates the provision selecting dlls and send the test request.  \n\n");

		_hostedLogger->work("This is already is the client demo that executed. \n\n");
		return true;
	}
};


class TestReq5 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Demonstrates the provision of a logger which can take multiple streams
	*  Test Procedure:
	*  - Displays lines of Logger class containing a vector of the streams
	*/
private:
	const std::string path_;
public:
	TestReq5(const std::string& path) : path_(path), Test("Requirement 5", "Rahul") {}
	~TestReq5() { std::cout << "\n  deleting TestReq5a"; }
	bool test()
	{
		Message msg = "Req #5 - Demonstrates the provision of message designs appropriate for this application - see lines 150 and 151";
		Path path = path_ + "/Translater/Translater.h";
		TestUtilities::TestHelpers::showFileLines(path, 132, 152, msg);
		return true;
	}
};

class TestReq6 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*   Shall support sending TestRequest messages from Client to TestHarness Server.
	*  Test Procedure:
	*  - Displays lines of client where the tests requests are sent.
	*/
private:
	const std::string path_;
public:
	TestReq6(const std::string& path) : path_(path), Test("Requirement 6", "Rahul") {}
	~TestReq6() { std::cout << "\n  deleting TestReq6"; }
	bool test()
	{
		Message msg = "Req #6 - Shall support sending TestRequest messages from Client to TestHarness Server, This is also shown in the demo";
		Path path = path_ + "/Translater/Translater.h";
		TestUtilities::TestHelpers::showFileLines(path, 132, 152, msg);
		return true;
	}
};

class TestReq7 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*   Shall support correctly executing each TestRequest, as a sequence of tests, with each TestRequest running in its own Process Pool child process.
	*  Test Procedure:
	*  - Shown in the console output during the demo
	*/
private:
	const std::string path_;
public:
	TestReq7(const std::string& path) : path_(path), Test("Requirement 7", "Rahul") {}
	~TestReq7() { std::cout << "\n  deleting TestReq7"; }
	bool test()
	{
		Message msg = "Req #7 - Shown in the console output during the demo";
		Path path = path_ + "/TestExecutive/TestExecutive.h";
		return TestUtilities::TestHelpers::showFileLines(path, 214, 219, msg);
	}
};

class TestReq8 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*  Shall support sending test results, via results messages, from the child process executing the tests to the Client that made the request.
	*  Test Procedure:
	*  - Displays the lines where the test results are sent
	*/
private:
	const std::string path_;
public:
	TestReq8(const std::string& path) : path_(path), Test("Requirement 8", "Rahul") {}
	~TestReq8() { std::cout << "\n  deleting TestReq8"; }
	bool test()
	{
		Message msg = "Req #8 -  sending test results, via results messages, from the child process executing the tests to the Client that made the request.";
		Path path = path_ + "/TestExecutive/TestExecutive.h";
		TestUtilities::TestHelpers::showFileLines(path, 131, 141, msg);

		_hostedLogger->work("Req #8b - Show that the client can recieve such messages\n\n");

		_hostedLogger->work("Shown as a txt file output during the demo\n\n ");

		return true;
	}
};

class TestReq9 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*  Shall demonstrate correct test operations for two or more concurrent clients.
	*  You need to ensure that testing takes enough time to ensure that more than one child process is running at the same time.
	*  Test Procedure:
	*  - Included a time taking test in the demo
	*/
private:
	const std::string path_;
public:
	TestReq9(const std::string& path) : path_(path), Test("Requirement 9", "Rahul") {}
	~TestReq9() { std::cout << "\n  deleting TestReq9"; }
	bool test()
	{
		_hostedLogger->work("Req #9 - demonstrate correct test operations for two or more concurrent clients \n\n");

		_hostedLogger->work("Included a time taking test in the demo \n\n");

		return true;
	}
};

class TestReq10 : public TestUtilities::Test
{
	/*
	*  Test Description:
	*   Demonstrates that there are tests that show the above requirements are met with a automated test suite that is run with the test harness
	*  Test Procedure:
	*  - Displays lines of this demo where the tests are written.
	*/
private:
	const std::string path_;
public:
	TestReq10(const std::string& path) : path_(path), Test("Requirement 10", "Rahul") {}
	~TestReq10() { std::cout << "\n  deleting TestReq10"; }
	bool test()
	{
		_hostedLogger->work("The demo run demonstrates the requrements ");

		Message msg = "Req #10 -  Demonstrates that there are tests that show the above requirements are met with a automated test suite that is run with the test harness ";
		Path fileSpec = path_ + "/DemoReqs/RequirementsDemo.cpp";
		return TestUtilities::TestHelpers::showFileLines(fileSpec, 14, 49, msg);
	}
};