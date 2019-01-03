#pragma once
///////////////////////////////////////////////////////////////////////
// TestExecutive.h - Contains the implementaiotn required for the    //
//					 Hosted resource the TestExecutive that			 //
//					 controls the flow of tests						 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides classes:
* - TestExecutiveMessage Provides a class that extends Message and can contain the status of the testExecutive.
* - HostedLogger		Provides an concrete implementation of the IHostedResource with string
* - HostedTestLogger	Provides an concrete implementation of the IHostedResource with test info
* - TestExecutive		Provides a class to contain all the paths to the dll and control the flow of all the test loading and execution with instances of logger
*WIN
*   IHostedResource.h
*   Logger.h
*   DllLoader.h
*   TestExecutor.h
*   FileUtilities.h
*	Message.h
*	Base64Helper.h
*	Message.h
*	Comm.h
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
#include "../HostedUtilities/IHostedResource.h"
#include "../LoggerUtilities/Logger.h"
#include "../TestLoader/DllLoader.h"
#include "../TestExecutor/TestExecutor.h"
#include "../TestUtilities/TestRequest.h"
#include "../FileUtilities/FileUtilities.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include <string>
#include<iostream>
#include<memory>
#include "../TestUtilities/Base64Helper.h"


namespace mpc = MsgPassingCommunication;
const std::string TEST_EXECUTIVE_STATUS = "testExecutiveStatus";
const std::string TEST_EXECUTIVE_READY = "testExecutiveReady";
using DLLs = std::vector<std::string>;

class TestExecutiveMessage : public mpc::Message
{
public:
	TestExecutiveMessage(std::string readyStatus, mpc::EndPoint to, mpc::EndPoint from): mpc::Message(to,from)
	{
		attribute(TEST_EXECUTIVE_STATUS, TEST_EXECUTIVE_READY);
	}
};

class HostedLogger : public HostedUtilities::IHostedResource<const std::string&>
{
public:
	// Inherited via IHostedResource
	virtual void work(const std::string& value) override
	{
		hostableLogger->execute(value);
	};
	virtual void setValue(HostedUtilities::IHostable<const std::string&>& value) override
	{
		hostableLogger = &value;
	};
private:
	HostedUtilities::IHostable<const std::string&>* hostableLogger;
};

class HostedTestLogger : public HostedUtilities::IHostedResource<LoggerUtilities::TestInfo>
{
public:
	// Inherited via IHostedResource
	virtual void work(LoggerUtilities::TestInfo& value) override
	{
		hostableLogger->execute(value);
	};
	virtual void setValue(HostedUtilities::IHostable<LoggerUtilities::TestInfo>& value) override
	{
		hostableLogger = &value;
	};
private:
	HostedUtilities::IHostable<LoggerUtilities::TestInfo>* hostableLogger;
};

class TestExecutive
{
public:
	TestExecutive(std::string path, mpc::Comm& comm, mpc::EndPoint endPoint, mpc::EndPoint harnessEndpoint) : _directoryPath(path), _comm(comm), _self(endPoint), _harness(harnessEndpoint)
	{
		_comm.setSendFilePath("./");
		_comm.start();
		sendReadyMessage();
		RecieveMessages();
		//LoadAndRunSingleTest("../Harness/dllFiles/CodeUtilitiesTest.dll");
	};

	void RecieveMessages()
	{
		mpc::Message msg;
		while (true)
		{
			msg = _comm.getMessage();
			if (msg.command() == "stop")
				break;
			onTestRequestRecieved(msg);
		}
	}

	void sendReadyMessage()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		TestExecutiveMessage testExecMsg(TEST_EXECUTIVE_READY, _harness, _self);
		testExecMsg.name("testExecutiveMessage");
		_comm.postMessage(testExecMsg);
	}

	void sendResults(std::string log)
	{
		mpc::Message msg;
		msg.to(_client);
		msg.from(_self);
		msg.name("Test result");
		auto encoded = b64encode(log);
		msg.attribute("log", encoded);
		msg.attribute("requestName", currentTestRequest.name());
		_comm.postMessage(msg);
	}

	void onTestRequestRecieved(mpc::Message msg)
	{
		TestRequest testRequest;
		testRequest = TestRequest::fromString(msg.value("testRequest"));
		currentTestRequest = testRequest;
		_client = msg.from();
		_dlls = testRequest.request();
		LoadAndRunTests();
	}

	std::vector<std::string> LoadDllsfromPath()
	{
		return FileSystem::Directory::getFiles(_directoryPath, "*.dll");
	}

	void LoadAndRunTestsAtDirectory(std::vector<std::string> paths) 
	{
		std::ostringstream ostrstream;
		for(std::string path: paths)
		{
			LoadAndRunSingleTest(_directoryPath + path, ostrstream);
		}
	}

	void LoadAndRunTests()
	{
		std::ostringstream ostrstream;

		for (std::string dll : _dlls)
		{
			LoadAndRunSingleTest(_directoryPath + dll, ostrstream);
		}
		sendResults(ostrstream.str());
		sendReadyMessage();
	}

	const mpc::Comm & comm()
	{
		return _comm;
	}

	void LoadAndRunSingleTest(std::string path, std::ostringstream& log) 
	{
		TestLoader::DllLoader loader = TestLoader::DllLoader();
		std::ostringstream resultLog;
		auto isLoaded = loader.loadTests(path);
		if (!isLoaded)
		{
			std::cout << " \n \n !!! Tests not loaded !!!";
			return;
		}

		auto testContainer = loader.getTestContainer();
		TestUtilities::TestPtrVec tests = testContainer->AllTests();

		//Create new Hostable logger
		LoggerUtilities::HostableLogger logger = LoggerUtilities::HostableLogger();
		logger.AddStream(std::cout, "console");

		std::string fileSpec = "./LogFile.txt";
		std::ofstream outfileStrm(fileSpec, std::ios::out);


		//Make the Hosted logger a shared pointer
		TestUtilities::LoggerHostedResourcePtr loggerHosterResource = TestUtilities::LoggerHostedResourcePtr(new HostedLogger());
		loggerHosterResource->setValue(logger);
		for (TestUtilities::TestPtr test : tests)
		{
			test->acceptHostedLogger(loggerHosterResource);
		}
		auto testLogger = std::shared_ptr<LoggerUtilities::HostableTestLogger>(new LoggerUtilities::HostableTestLogger());
		testLogger->AddStream(std::cout, "console");
		if (outfileStrm.good())
			testLogger -> AddStream(outfileStrm, "FileStream");
		testLogger->AddStream(log, "string stream");

		TestExecutor::TestExecutor executor = TestExecutor::TestExecutor(testLogger);
		bool result = executor.runTests(testContainer);
		delete testContainer;
	}

private:
	std::string _directoryPath;
	DLLs _dlls;
	mpc::Comm& _comm;
	mpc::EndPoint _client;
	mpc::EndPoint _self;
	mpc::EndPoint _harness;
	TestRequest currentTestRequest;
};
