#pragma once
/////////////////////////////////////////////////////////////////////
// TestHarnes.cpp - defines all the functions of the 			   //
//						 TestHarnes.h							   //
// ver 1.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include "TestHarness.h"

mpc::Comm& TestHarness::comm()
{
	return comm_;
}

void TestHarness::sendMessage(mpc::Message msg)
{
	comm_.postMessage(msg);
}

void TestHarness::recieveMessage(TestHarness* t)
{
	mpc::Message msg;
	std::cout << "\n Started Listening on recv thread ";
	while (true)
	{
		msg = comm_.getMessage();
		std::cout << "\n  Harness recvd  message \"" << msg.name() << "\"";
		if (msg.command() == "stop")
			break;
		if (msg.containsKey(TEST_REQUEST))
		{
			t->onTestRequestRecieved(msg);
		}
		if (msg.containsKey(TEST_EXECUTIVE_STATUS))
		{
			t->onTestExecutiveUpdate(msg);
		}
	}
}

void TestHarness::onTestRequestRecieved(mpc::Message msg)
{
	TestRequestMessage* testReqMsg = (TestRequestMessage*)(&msg);
	std::cout << "\n Enqueueing a testRequest from " <<  msg.from().toString();
	testRequests_.enQ(*testReqMsg);
	checkAssignment();
}

void TestHarness::onTestExecutiveUpdate(mpc::Message msg)
{
	TestExecutiveMessage* testExecutiveMsg = (TestExecutiveMessage*)(&msg);
	std::cout << "\n Enqueueing a test executive from " << msg.from().toString();
	testExecutives_.enQ(*testExecutiveMsg);
	checkAssignment();
}

void TestHarness::checkAssignment()
{
	if (testExecutives_.size() > 0 && testRequests_.size() >0)
	{
		auto testReqMsg = testRequests_.deQ();
		auto testExecutiveMsg = testExecutives_.deQ();

		mpc::Message msg;
		msg.to(testExecutiveMsg.from());
		msg.from(testReqMsg.from());
		msg.attribute(TEST_REQUEST, testReqMsg.value(TEST_REQUEST));

		std::cout << "\n Assigning test Requestfrom " << msg.from().toString() << " to executive at" << msg.to().toString();
		sendMessage(msg);
	}
}

TestHarness::TestHarness(mpc::Comm & comm, LoggerUtilities::Logger logger): comm_(comm), logger_(logger)
{
	comm.start();
	std::function<void()> tproc = [&]() { recieveMessage(this); };
	recvThread = std::thread(tproc);
	recvThread.detach();
}


TestHarness::~TestHarness()
{
	comm_.stop();
}
