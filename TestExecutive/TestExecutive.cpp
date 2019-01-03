#pragma once
#include "TestExecutive.h"

//#ifndef TEST_TEST_EXECUTIVE

int main(int argc, char* argv[])
{
	std::cout << "\n  Starting TestExecutive";
	std::cout << "\n ===============================================";

	std::string port;
	if (argc < 2)
	{
		std::cout << "\n No port given for Executive, using the value 8083";
		port = "8083";
	}
	else
		port = argv[1];

	std::string dir_Path;
	if (argc < 3)
	{
		std::cout << "\n No deafult dir path given for Executive, using the value ./dllFiles/ ";
		dir_Path = "./dllFiles/";
	}
	else
		dir_Path = argv[2];

	mpc::EndPoint harnessEp;
	std::string endPoint;
	if (argc < 4)
	{
		std::cout << "\n address for the test harness is not given 35";
		return 1;
	}
	endPoint = argv[3];
	harnessEp = mpc::EndPoint::fromString(endPoint);
	std::stringstream convert(port);
	int port_int = 0;
	convert >> port_int;
	
	mpc::EndPoint ep("localhost", port_int);
	mpc::Comm comm(ep, "TestExecutive" + port);

	TestExecutive t(dir_Path, comm, ep, harnessEp);
	std::cin.get();
	
}

//#endif // !TEST_TEST_EXECUTIVE
