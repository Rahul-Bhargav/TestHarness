////////////////////////////////////////////////////////////////////////////
// DllLoader.cpp : implementation and testing for DllLoader.h             //
// ver 2.0                                                                //
//                                                                        //
// Application : OOD F18 Project 2										  //
// Platform    : VS17 Community - Windows 10 Professional x64             //
// Author      : Bhargav Rahul Surabhi, Syracuse University,			  //
//               brsurabh@syr.edu										  //
// Source      : Ammar Salman, EECS Department, Syracuse University       //
//               313/788-4694, hoplite.90@hotmail.com                     //
////////////////////////////////////////////////////////////////////////////

#ifndef UNICODE
#define UNICODE


#include "DllLoader.h"
#include <iostream>
#include <fstream>

namespace TestLoader
{
	//----< string converter using std C++ >-----------------------------

	std::wstring toWstring(const std::string& s)
	{
		std::wstring wstr;
		for (auto ch : s)
		{
			wstr += (wchar_t)ch;
		}
		return wstr; 
	}

	DllLoader::DllLoader()
	{
	}

	DllLoader::~DllLoader()
	{
	}

	TestUtilities::ITestsContainer* DllLoader::getTestContainer()
	{
		return testsContainer;
	}

	bool DllLoader::loadTests(const std::string& path)
	{
		std::ifstream f(path.c_str());
		bool gf = f.good();
		std::cout << "\n File Exists: " << gf;
		HMODULE hmod = LoadLibrary(toWstring(path).c_str()); // load DLL
		if (!hmod) return false;  // check if DLL was properly loaded

		  // check if the DLL contains get_ITests() function ...
		  // in other words, check if the DLL complies with the protocol

		//using ITC = TestUtilities::ITestsContainer * (*)();  // using instead of typedef

		using SpITC = TestUtilities::ITestsContainer* (*)();
		SpITC get_ItestContainer = (SpITC)GetProcAddress(hmod, "get_TestContainer");
		if (!get_ItestContainer) return false;

		// execute get_ITests() to get the collection of tests
		testsContainer = get_ItestContainer();
		if (testsContainer) { // check if tests is nullptr before attempting to get its tests collection
			return true;
		}

		// this will only be reached if get_ITests() returned nullptr in which case the 
		// TestDriver DLL contains no tests to execute.
		return false;
	}
}
#endif // UNICODE

#ifdef TEST_DLL_LOADER

#include <iostream>
#include <iomanip>
#include <memory>

//----< uses TestUtilities Infrastructure >--------------------------
using namespace TestLoader;
using namespace std;

int main() {
	cout << "\n  Testing DLL Loader";
	cout << "\n ====================";

	DllLoader loader;

	cout << "\n  Loading '../Debug/TestDriver1.dll' which is a single-test TestDriver...";

	bool loaded = loader.loadTests("../x64/Debug/CodeUtilitiesTest.dll");
	if (!loaded) {
		cout << " failed to load dll or failed to load tests.\n    Terminating...\n";
		return -1;
	}

	cout << " successfully loaded";
	cout << "\n    Extracted tests:\n";

	cout << "\n\n";
	return 0;
}

#endif
