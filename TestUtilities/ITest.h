#pragma once
///////////////////////////////////////////////////////////////////////
// ITest.h - Provides the interface for writing the tests			 //
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
* - ITest	Provides an interface for the user to implement a test and execute them using the test harness
*
* Required Files:
* ---------------
*   IHostedResource.h
*	Logger.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 11 Oct 2018
* - refactored to a different file and namespace
* ver 1.0 : 3 Sep 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - Maybe add a class that accepts a hosted resource
*/


#include "../HostedUtilities/IHostedResource.h"
#include "../LoggerUtilities/ILogger.h"
#include <string>
#include <memory>

namespace TestUtilities
{
	using LogHostedResource = HostedUtilities::IHostedResource<const std::string&>;
	using LoggerHostedResourcePtr = std::shared_ptr<LogHostedResource>;
	class ITest
	{
	public:
		virtual bool  test() = 0;
		virtual ~ITest() {};
		virtual std::string getName() = 0;
		virtual std::string getAuthor() = 0;
		virtual void acceptHostedLogger(LoggerHostedResourcePtr hostedResource) = 0;
		virtual LoggerHostedResourcePtr getHostedLogger() = 0;
	};
}
