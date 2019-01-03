#pragma once

///////////////////////////////////////////////////////////////////////
// ITestsContainer.h - Facilities for single-user test harness		 //
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
* - ITestsContainer	-	Provides an interface for containing multiple tests
*
* Required Files:
* ---------------
*   ITest.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 3 Sep 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/

#include <vector>
#include <memory>
#include <string>
#include "ITest.h"

namespace TestUtilities
{
	using TestPtr = std::shared_ptr<ITest>;

	using TestPtrVec = std::vector<TestPtr>;

	class ITestsContainer
	{
	public:
		virtual bool addTest(TestPtr item) = 0;
		virtual bool deleteTest(std::string name) = 0;
		virtual bool clearTests() = 0;
		virtual const TestPtrVec AllTests() = 0;
	};
}

#ifdef IN_DLL
extern "C" {
	__declspec(dllexport) TestUtilities::ITestsContainer* get_TestContainer();
}
#endif
