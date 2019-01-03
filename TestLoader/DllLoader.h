#pragma once
///////////////////////////////////////////////////////////////////////
// DllLoader.h - An implementation of ILoader to load tests from     //
//				 dll's												 //
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
* - DllLoader provides an implementation of the ITestLoader that loads all the tests from a dll
*
* Required Files:
* ---------------
*   ILoader.h
*	ITest.h
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
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include "ILoader.h"
#include "../TestUtilities/ITest.h"

namespace TestLoader
{

	class DllLoader : public ITestLoader
	{
	public:
		DllLoader();
		~DllLoader();

		// Inherited via ILoader
		virtual bool loadTests(const std::string& path) override;
		virtual TestUtilities::ITestsContainer* getTestContainer() override;

	private:
		TestUtilities::ITestsContainer* testsContainer;
	};
	
}
