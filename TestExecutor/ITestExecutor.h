#pragma once
///////////////////////////////////////////////////////////////////////
// ITestExecutor.h - Provides the interface for executing tests      //
//					 form a testContainer							 //
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
* - ITestExecutor	Provides an interface for the user to implement a testexecutor that runs all the tests and gives the result.
*
** Required Files:
* ---------------
*   ITestsContainer.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 11 Oct 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - Maybe add a class that accepts a hosted resource
*/
#include "../TestUtilities/ITestsContainer.h"
#include <memory>

namespace TestExecutor
{
	using ITRPtr = TestUtilities::ITestsContainer*;
	class ITestExecutor
	{
	public:
		virtual bool runTests(ITRPtr testContainer) = 0;
		virtual ~ITestExecutor() {};
	};

}