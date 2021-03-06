#pragma once
///////////////////////////////////////////////////////////////////////
// Harness.cpp - The main start file that initializes the Harness	 //
//				 and the child processes.						     //
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
* This package provides the start function for the project
*
* Required Files:
* ---------------
*   Process.h
*   TestHarness.h
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

#include <iostream>
#include <string>
#include "TestHarness.h"
#include "../Process/Process.h"

using namespace Utilities;

int main(int argc, char* argv[])
{
	std::string port;
	if (argc < 2)
	{
		std::cout << "\n No default port given for Harness, using the value 8081";
		port = "8081";
	}
	else
		port = argv[1];

	std::string saveFileDir;
	if (argc < 3)
	{
		std::cout << "\n No default save file dir given for Harness, using the value ./ ";
		saveFileDir = "./dllFiles";
	}
	else
	{
		saveFileDir = argv[2];
	}
	std::string exeDir;
	
	if (argc < 4)
	{
		std::cout << "\n No default executables dir given for Harness, using the value ./ ";
		exeDir = "./";
	}
	else
	{
		exeDir = argv[3];
	}
	std::cout << port;
	std::cout << "\n The Process for the Main Harness";
	std::cout << "\n ====================================";
	std::stringstream convert(port);
	int port_int = 0;
	convert >> port_int;
	mpc::EndPoint endPoint("localhost", port_int);
	mpc::Comm comm(endPoint, "Harness");
	comm.setSaveFilePath(saveFileDir);
	LoggerUtilities::Logger logger;
	logger.AddStream(std::cout, "console");
	TestHarness testHarness(comm, logger);
	
	std::string appPath = exeDir + "WpfApp1.exe";

	Process p0;
	p0.application(appPath);
	p0.commandLine(" INDEMO");
	p0.create();

	Process p1;
	appPath = exeDir + "TestExecutive.exe";
	p1.application(appPath);
	p1.title("TestExecutive");
	p1.commandLine(" 8083 ../Harness/dllFiles/ localhost:8081");
	p1.create();


	Process p2;
	p2.application(appPath);
	p2.title("TestExecutive");
	p2.commandLine(" 8084 ../Harness/dllFiles/ localhost:8081");
	p2.create();

	std::cin.get();

	
}
