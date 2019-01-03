#pragma once
///////////////////////////////////////////////////////////////////////
// Test.h - An implementation of ITest  							 //
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
* - Test	Provides an concrete implementation of the Itest with Name, Author and a basic 
*			implementation of acceptHostedResource
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
#include "ITest.h"
#include <string>
namespace TestUtilities
{
	class Test : public ITest
	{
	public:
		Test(std::string name = "AnonymousTest", std::string author="AnonymousAuthor");
		std::string author;
		std::string name;
		LoggerHostedResourcePtr _hostedLogger;

		virtual bool test() override;
		virtual LoggerHostedResourcePtr getHostedLogger() override;
		virtual void acceptHostedLogger(LoggerHostedResourcePtr hostedResource) override;

		// Inherited via ITest
		virtual std::string getName() override;

		// Inherited via ITest
		virtual std::string getAuthor() override;
	};
}

