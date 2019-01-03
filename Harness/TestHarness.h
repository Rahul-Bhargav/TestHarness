#pragma once
/////////////////////////////////////////////////////////////////////////
// TestHarness.h - Defines the Mother that controls the flow of the	   //
//				   entire test harness.								   //
// ver 1.0                                                             //
// Bhargav Rahul Surabhi, CSE687-OnLine Object Oriented Design         //
// Fall 2017														   //
/////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package defines a TestHarness class.
*  - This class is responsible for directing the usage of the multiple TestHarness cores.
*  - The class uses 2 blocking queues to keep in mind what processes are available and what requests need to be done.
*
*  Required Files:
*  ---------------
*  Cpp11-BlockingQueue.h
*  TestRequest.h
*  Comm.h 
*  Message.h 
*  TestRequestMessage.h 
*  TestExecutive.h 
*  Logger.h 
*
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 13 Nov 2018
*  - first release
*
*/

#include "../CppCommWithFileXfer/Cpp11-BlockingQueue/Cpp11-BlockingQueue.h"
#include "../CppCommWithFileXfer/MsgPassingComm/Comm.h"
#include "../CppCommWithFileXfer/Message/Message.h"
#include "../TestUtilities/TestRequest.h"
#include "../TestUtilities/TestRequestMessage.h"
#include "../TestExecutive/TestExecutive.h"
#include "../LoggerUtilities/Logger.h"

namespace mpc = MsgPassingCommunication;

class TestHarness
{
private:
	BlockingQueue<TestRequestMessage> testRequests_;
	BlockingQueue<TestExecutiveMessage> testExecutives_;
	mpc::Comm& comm_;
	LoggerUtilities::Logger& logger_;
	std::thread recvThread;
public:
	mpc::Comm& comm();
	void sendMessage(mpc::Message msg);
	void recieveMessage(TestHarness* t);
	void onTestRequestRecieved(mpc::Message msg);
	void onTestExecutiveUpdate(mpc::Message msg);
	void checkAssignment();
	TestHarness(mpc::Comm& comm, LoggerUtilities::Logger logger);
	~TestHarness();
};
