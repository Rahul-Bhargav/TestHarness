#pragma once
///////////////////////////////////////////////////////////////////////
// ILoader.h - Provides the interface for loading the tests			 //
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
* - ILoader	Provides an interface for the user to implement a test loader that returns an ITestContainer
*
* Required Files:
* ---------------
*   ITest.h
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
#include<vector>
#include<string>
#include"../TestUtilities/TestsContainer.h"

namespace TestLoader
{
	class ITestLoader
	{
	public:
		virtual bool loadTests(const std::string& path) = 0;
		virtual TestUtilities::ITestsContainer* getTestContainer() = 0;
		virtual ~ITestLoader() {};
	};
}