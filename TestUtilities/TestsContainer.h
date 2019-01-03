#pragma once

///////////////////////////////////////////////////////////////////////
// TestContainer.h - Implementation of an ITestsContainer	 		 //
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
* - TestsContainer		Basic implementation for the ItestCOntainer using Vectors
*
* Required Files:
* ---------------
*   Test.h
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
#include "ITestsContainer.h"

namespace TestUtilities
{
	class TestsContainer : public ITestsContainer
	{
	public:
		TestsContainer();
		~TestsContainer();
		// Inherited via ITestsContainer
		virtual bool addTest(TestPtr item) override;
		virtual bool deleteTest(std::string name) override;
		virtual bool clearTests() override;
		virtual const TestPtrVec AllTests() override;

	private:
		TestPtrVec _tests;
	};
}
