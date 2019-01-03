#pragma once
///////////////////////////////////////////////////////////////////////
// Logger.h - Provides a Logger implementaion with multiple streams  //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Projects #1, CSE687 - Object Oriented Design         //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - Logger - Basic implementation for the ILogger using vector streams and a default stream to show errors.
* - TestLogger - This implementation of the logger allows us to log the the test results, log success, log failure and log exceptions.
* - HostableTestLogger - This implementation of the logger inherits TestLogger and IHostable with a string
* - HostableLogger - This implementation of the logger inherits TestLogger and IHostable with TestInfo
*
* Required Files:
* ---------------
*   IHostable.h
*	ILogger.h
*
* Maintenance History:
* --------------------
* ver 2.0 : 9 Oct 2018
* - Have Hostable loggers
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
#include "ILogger.h"

namespace LoggerUtilities
{

	class Logger : public ILogger
	{
	public:
		Logger();
		~Logger();
		struct Stream
		{
			std::ostream* stream;
			std::string name;
		};
		virtual void Log(const std::string& content) override;
		virtual bool AddStream(std::ostream& stream, std::string name);
		virtual bool AddStream(Stream stream);
		virtual void SetDefault(std::ostream& stream);
		virtual bool RemoveStream(std::string name);
	private:
		std::vector<Stream> _streams;
		std::ostream* _defaultOut;
	};

	ILogger& operator<< (ILogger& logger, const std::string& content);

	class TestLogger : public Logger
	{
	public:
		void LogResult(std::string testName, bool testResult, std::string author);

		void LogResult(TestInfo& info);

		std::string getCurrentTime();

		void LogSuccess(std::string testName, std::string author);

		void LogFailure(std::string testName, std::string author);

		void LogException(std::string testName, std::string author, std::exception& ex);
	};

	class HostableLogger : public Logger, public HostedUtilities::IHostable<const std::string&>
	{
		// Inherited via IHostable
		virtual bool execute(const std::string& value) override;
	};

	class HostableTestLogger : public TestLogger, public HostedUtilities::IHostable<TestInfo>
	{
		// Inherited via IHostable
		virtual bool execute(TestInfo value) override;
	};
}
