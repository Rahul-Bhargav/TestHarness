#pragma once
///////////////////////////////////////////////////////////////////////
// ILogger.h - Provides a Logger implementaion with multiple streams //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Projects #1,#2, CSE687 - Object Oriented Design      //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - Ilogger - Provides an interface for Logger.
* - TestInfo - Provides a struct to hold the test result details
*
* Maintenance History:
* --------------------
* ver 2.0 : 9 Oct 2018
* - Added TestInfo
* ver 1.0 : 3 Sep 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../HostedUtilities/IHostable.h"

namespace LoggerUtilities
{
	struct TestInfo
	{
		TestInfo(std::string name, std::string author, bool result) : name(name), author(author), result(result) {}
		TestInfo(std::string name, std::string author, bool result, bool isException, std::exception* ex) : name(name), author(author), result(result), isException(isException), ex(ex) {}

		std::string name;
		std::string author;
		bool result;
		bool isException = false;
		std::exception* ex = nullptr;
	};

	class ILogger
	{
	public:
		virtual void Log(const std::string& content) = 0;
		virtual ~ILogger() {};
	};
}
