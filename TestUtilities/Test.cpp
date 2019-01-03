#pragma
/////////////////////////////////////////////////////////////////////
// Tests.cpp -  Definitoions of the functions in Test class //
// ver 1.0												           //
//                                                                 //
// Bhargav Rahul Surabhi, Syracuse University, Fall 2018           //
// email: brsurabh@syr.edu										   //
/////////////////////////////////////////////////////////////////////

#include "Test.h"

void TestUtilities::Test::acceptHostedLogger(TestUtilities::LoggerHostedResourcePtr hostedResource)
{
	_hostedLogger = hostedResource;
}

std::string TestUtilities::Test::getName()
{
	return name;
}

std::string TestUtilities::Test::getAuthor()
{
	return author;
}

TestUtilities::Test::Test(std::string name, std::string author) : name(name), author(author)
{
}

bool TestUtilities::Test::test()
{
	return false;
}

TestUtilities::LoggerHostedResourcePtr TestUtilities::Test::getHostedLogger()
{
	return _hostedLogger;
}
