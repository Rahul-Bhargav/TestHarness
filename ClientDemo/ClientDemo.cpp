#pragma once
///////////////////////////////////////////////////////////////////////
// ClientDemo.cpp - A client that sends test requests and files      //
//																	 //
// ver 1.0                                                           //
// Language:    C++, Visual Studio 2017                              //
// Application: Most Projects, CSE687 - Object Oriented Design       //
// Author:      Bhargav Rahul Surabhi, Syracuse University,			 //
//              brsurabh@syr.edu									 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides functions that send and recieve tests and their results
*
* Required Files:
* ---------------
*   Comm.h
*   TestRequestMessage.h
*   FileSystem.h
*   Base64Helper.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 11 Nov 2018
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none planned
*/

#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../TestUtilities/TestRequestMessage.h"
#include <iostream>
#include <thread>
#include <functional>
#include <windows.h> 
#include "../Utilities/FileSystem/FileSystem.h"
#include "../TestUtilities/Base64Helper.h"

using namespace MsgPassingCommunication;

void sendMessage(Comm& comm, EndPoint source, EndPoint dest) {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	Message msg;
	msg.to(dest);
	msg.from(source);
	msg.value("sendingFile");
	msg.name("DllFile");
	msg.file("CodeUtilitiesTest.dll");
	comm.postMessage(msg);

	Message msg2;
	msg2.to(dest);
	msg2.from(source);
	msg2.value("sendingFile");
	msg2.name("DllFile - DemoReqs");
	msg2.file("DemoReqs.dll");
	comm.postMessage(msg2);

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	TestRequest testRequest;
	testRequest.name("Test1");
	testRequest.author("Rahul");
	testRequest.date("11-16-2018");
	testRequest.addDll("CodeUtilitiesTest.dll");
	TestRequestMessage testReqMessage(testRequest, dest, source);
	comm.postMessage(testReqMessage);

	TestRequest testRequest2;
	testRequest2.name("Test1");
	testRequest2.author("Rahul");
	testRequest2.date("11-16-2018");
	testRequest2.addDll("DemoReqs.dll");
	TestRequestMessage testReqMessage2(testRequest2, dest, source);
	comm.postMessage(testReqMessage2);
}

void recvMessage(Comm& comm) 
{
	while (true)
	{
		Message msg = comm.getMessage();
		if (msg.containsKey("log"))
		{
			std::cout << "\n The result of the tests were " << msg.value("result") << "\n";
			std::string decoded = b64decode(msg.value("log"));
			std::cout << decoded;
		}
	}
}

int main(int argc, char* argv[])
{
	std::cout << "\n  Demonstrating Peer1 in Peer-To-Peer Comm Demo";
	std::cout << "\n ===============================================";

	if (argc < 2)
	{
		std::cout << "\n  Please enter path to directory for files to send \n";
		return 1;
	}
	std::string path = argv[1];


	::SetConsoleTitle(L"ClientDemo");

	EndPoint epPeer1("localhost", 8082);
	EndPoint epPeer2("localhost", 8081);

	Comm comm(epPeer1, "Peer1");
	comm.start();

	comm.setSendFilePath(path);
	comm.setSaveFilePath("./");

	std::function<void()> recvProc = [&]() { recvMessage(comm); };
	std::thread recvThread(recvProc);
	recvThread.detach();

	sendMessage(comm, epPeer1, epPeer2);
	std::cin.get();
	comm.stop();
	std::cout << "\n\n";
	return 0;
}
