#pragma once
/////////////////////////////////////////////////////////////////////
// Test.cpp - Test stub for the IHostedResource					   //
// ver 1.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_TEST_HOSTEDUTILITIES

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../HostedUtilities/IHostable.h"

class A : public HostedUtilities::IHostable<std::string>
{
public:
	A()
	{
		std::cout << "class A";
	};

	bool execute(std::string value) override
	{
		std::cout << value;
	};
};

int main()
{
	A a;
	HostedUtilities::IHostable<std::string>* b = &a;
	b->execute("test");
	std::cin.get();
}

#endif // TEST_TEST_HOSTEDUTILITIES

