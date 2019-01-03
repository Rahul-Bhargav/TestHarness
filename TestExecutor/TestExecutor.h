#pragma once
///////////////////////////////////////////////////////////////////////
// TestExecutor.h - An implementation of ITestExecutor to run tests  //
//				    from an ITestContainer							 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - TestExecutor	Provides an implementation of the Itest  executor that synchronously runs 
*					all the tests from a TestContainer
*
* Required Files:
* ---------------
*   ITestExecutor.h
*	Logger.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none planned
*/

#include "ITestExecutor.h"
#include "../LoggerUtilities/Logger.h"
namespace TestExecutor
{
	using SptrHostableLogger = std::shared_ptr<LoggerUtilities::HostableTestLogger>;
	class TestExecutor : public ITestExecutor
	{
	public:
		TestExecutor(SptrHostableLogger hostableLogger);
		~TestExecutor();

		bool RunSingleTest(TestUtilities::TestPtr  test);

		// Inherited via ITestExecutor
		virtual bool runTests(ITRPtr testContainer) override;
	private:
		SptrHostableLogger _hostableLogger;
	};
}
