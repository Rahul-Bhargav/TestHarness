#pragma once
/////////////////////////////////////////////////////////////////////////
// TestRequestMessage.h - Defines a class that holds a testRequest     //
//						  message that can be passed via comm.		   //
// ver 1.3                                                             //
// Bhargav Rahul Surabhi, CSE687-OnLine Object Oriented Design         //
// Fall 2017														   //
/////////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  This package defines a TestRequestMessage class.
*  - This class is responsible for containing a TestRequest message
*
*  Required Files:
*  ---------------
*  Message.h
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 13 Nov 2018
*  - first release
*
*/

#include "../CppCommWithFileXfer/Message/Message.h"
#include "../TestUtilities/TestRequest.h"

const std::string TEST_REQUEST = "testRequest";

namespace mpc = MsgPassingCommunication;

class TestRequestMessage : public mpc::Message
{
public:
	TestRequestMessage(TestRequest& testRequest) 
	{
		name(testRequest.name());
		attribute(TEST_REQUEST, testRequest.toString());
	}

	TestRequestMessage(TestRequest& testRequest, mpc::EndPoint to, mpc::EndPoint from) :Message(to, from)
	{
		name(testRequest.name());
		attribute(TEST_REQUEST, testRequest.toString());
	}

	void TestRequest(TestRequest& testRequest) 
	{
		name(testRequest.name());
		attribute(TEST_REQUEST, testRequest.toString());
	}

};
