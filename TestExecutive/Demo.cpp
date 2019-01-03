#pragma once
/////////////////////////////////////////////////////////////////////
// Demo.cpp - Demo the fuinctionalities pf the test executive	   //
//			  and the related packages							   //
// ver 1.1												           //
// Author: Bhargav Rahul Surabhi, Syracuse University, Fall 2018   //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include "TestExecutive.h"
#include <iostream>

#ifdef TEST_TEST_EXECUTIVE

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "\n  Please enter path to Project Directory\n";
		return 1;
	}
	std::string path = argv[1];

	TestExecutive testExecutive = TestExecutive(path);
	std::vector<std::string> dllPaths = testExecutive.LoadDllsfromPath();

	testExecutive.LoadAndRunTests(dllPaths);

	std::cout << "\n  Press enter to quit: ";
	std::cin.get();
	std::cout << "\n\n";
	return 0;
}

#endif // TEST_TEST_EXECUTIVE

