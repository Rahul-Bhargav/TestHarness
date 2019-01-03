#pragma
/////////////////////////////////////////////////////////////////////
// Logger.cpp - Write the logger function implementations          //
// ver 1.1												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "Logger.h"


namespace LoggerUtilities
{
	// Initialize logger to have zero streams
	// Add a default out cout;
	Logger::Logger()
	{
		_streams = {};
		_defaultOut = &std::cout;
	}

	// Clear all the streams from the class
	Logger::~Logger()
	{
		_streams.clear();
	}

	// Add a Stream object into the vector of Streams.
	bool Logger::AddStream(Logger::Stream stream)
	{
		try
		{
			_streams.push_back(stream);
		}
		catch (const std::exception& ex)
		{
			*_defaultOut << "Cannot register the stream. - " << ex.what();
			return false;
		}
		return true;
	}

	// An overloaded function for the above AddStream function 
	bool Logger::AddStream(std::ostream& stream, std::string name = "sample_stream")
	{
		Stream str{ &stream, name };
		return AddStream(str);
	}

	// Find the Logger stream by name and then erase it
	bool Logger::RemoveStream(std::string name)
	{
		try
		{
			//Find the logger in the streams which have the same name
			auto it = std::find_if(_streams.begin(), _streams.end(), [&name](Stream stream) {return stream.name == name; });

			if (it != _streams.end())
			{
				_streams.erase(it);
			}
			else
			{
				*_defaultOut << "Cannot delete the registered stream.";
				return false;
			}
		}
		catch (const std::exception& ex)
		{
			*_defaultOut << "Cannot delete the registered stream. - " << ex.what();
			return false;
		}
		return true;
	}

	//Set the default out tos display logger errors
	void Logger::SetDefault(std::ostream& stream)
	{
		_defaultOut = &stream;
	}

	//Log function which loops through all the streams and streams the content.
	void Logger::Log(const std::string& content)
	{
		try
		{
			for (auto streamContainer : _streams)
			{
				*(streamContainer.stream) << content;
			}

		}
		catch (const std::exception& ex)
		{
			*_defaultOut << "One of the streams failed! - " << ex.what();
		}
	}

	//// TestLogger implementation

	// This method writes a test log based on the result, name and the author with the date and time of execution.
	void TestLogger::LogResult(std::string name, bool testResult, std::string author)
	{
		std::string result = testResult ? " PASSED " : " FAILED";
		Log("\n\n " + name + " has " + result + " \n Author : " + author + "  Time Executed: " + getCurrentTime() + "\n\n");
	}

	void TestLogger::LogResult(TestInfo& info)
	{
		if (info.isException)
		{
			LogException(info.name, info.author, *(info.ex));
			return;
		}

		std::string result = info.result ? " PASSED " : " FAILED";
		Log("\n\n " + info.name + " has " + result + " \n Author : " + info.author + "  Time Executed: " + getCurrentTime() + "\n\n");

	}

	// The time code written below is referenced from https://stackoverflow.com/a/27856440 , 
	// https://stackoverflow.com/questions/34857119/how-to-convert-stdchronotime-point-to-string/34858704
	// https://stackoverflow.com/questions/34857119/how-to-convert-stdchronotime-point-to-string/34858704
	std::string TestLogger::getCurrentTime() {
		auto timeNow = std::chrono::system_clock::now();
		std::time_t t = std::chrono::system_clock::to_time_t(timeNow);
		struct tm buf;
		localtime_s(&buf, &t);
		std::stringstream ss;
		ss << std::put_time(&buf, "%Y-%m-%d %X");
		return ss.str();
	}

	// This method writes a test log when the result is a success - includes name and the author with the date and time of execution.
	void TestLogger::LogSuccess(std::string name, std::string author)
	{
		LogResult(name, true, author);
	}

	// This method writes a test log when the result is a failure - includes name and the author with the date and time of execution.
	void TestLogger::LogFailure(std::string name, std::string author)
	{
		LogResult(name, false, author);
	}

	// This method writes a test log when the result is an exception - includes name and the author with the date and time of execution.
	void TestLogger::LogException(std::string name, std::string author, std::exception & ex)
	{
		LogResult(name, false, author);

		// Log the exception saperately
		Log("\n\n !!!An Exception has been thrown!!! \n " + std::string(ex.what()) + "\n\n");
	}

	// This method allows the logger to be used like a standard ostream with the operator '<<'
	ILogger & operator<<(ILogger & logger, const std::string& content)
	{
		logger.Log(content);
		return logger;
	}

	bool HostableTestLogger::execute(TestInfo value)
	{
		LogResult(value);
		return true;
	}

	bool HostableLogger::execute(const std::string& value)
	{
		Log(value);
		return true;
	}
}

#ifdef TEST_LOGGERUTILITIES
int main()
{
	Logger::TestLogger testLogger;

	testLogger.AddStream(std::cout, "Console Out");

	// Test the << operator
	testLogger << "Hello";

	testLogger.LogFailure("Failed test", "Self");
	testLogger.LogSuccess("Success test", "Self");

	std::exception ex("\n  -- this test always throws -- ");
	testLogger.LogException("TestThrows", "Self", ex);

	testLogger.LogResult("Success Test", true, "Self");

	std::exception ex("\n  -- this test always throws -- ");

}
#endif