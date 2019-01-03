#pragma once
#define IN_DLL
/////////////////////////////////////////////////////////////////////
// Tests.cpp - Demonstrate CodeUtilities operations				   //
// ver 1.1            using single-user TestHarness                //
// Author	 - Bhargav Rahul Surabhi, Syracuse University, Masters //
//			   Fall 2018.
// Source     - Jim Fawcett, CSE687-Object Oriented Design,		   //
//			   Fall 2018										   //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  CodeUtil_Tests provides four tests, one for each class or, in some
*  cases, part of a class.  These run in the single-user TestHarness,
*  which Project #1 develops.
*
*  All of the CodeUtility tests are defined in this CodeUtil_Tests.h file.
*  They are executed in the main function in Proj1_TestDriver.cpp.
*
*
*  Required Files:
*  ---------------
*  CodeUtilities.h,S
*  Test.h
*  TestContainer.h
*
*  Maintenance History:
*  --------------------
*  ver 1.0 : 13 Oct 2018
*  - first release
*/

#include "../Utilities/CodeUtilities/CodeUtilities.h"
#include "../TestUtilities/Test.h"
#include "../TestUtilities/TestsContainer.h"

class ProcessCmdLineTests : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Tests all the functionalitites of the class ProcessCmdLine class.
	*  Test Procedure:
	*  - Inittialize the ProcessCmdLine with proper argc argv values and test if the resultant object returns the correct values passed
	*/
public:
	ProcessCmdLineTests() :Test("ProcessCmdLine", "Rahul") {};
	bool test()
	{
		const char *list[] = { "123", "abc", "XYZ", "/1", "3" };
		char** argv = const_cast<char**>(list);					// Had to remove the const because I am using the string literal
		std::ostringstream out;
		Utilities::ProcessCmdLine processCmdline(5, argv, out);

		//Test Path
		auto path = processCmdline.path();
		processCmdline.showPath();
		_hostedLogger->work("\n path = " + out.str());
		out.str("");
		out.clear();
		bool testPathResult = path.compare("123");

		//Test Options
		processCmdline.option(4);
		auto options = processCmdline.options();
		processCmdline.showOptions();
		_hostedLogger->work("\n options = " + out.str()); 
		out.str("");
		out.clear();
		bool testOptionsResult = true;

		//Test Pattern
		auto patterns = processCmdline.patterns();
		processCmdline.showPatterns();
		_hostedLogger->work("\n patterns = " + out.str());
		out.str("");
		out.clear();
		bool testPattern = patterns[0] == "XYZ";

		//Test MaxItems
		auto maxItems = processCmdline.maxItems();
		processCmdline.showMaxItems();
		_hostedLogger->work("\n max items = " + out.str());
		out.str("");
		out.clear();
		bool testMaxItem = maxItems == 3;

		return testPathResult && testOptionsResult && testPattern && testMaxItem;
	}
private:

};

class ConverterTests : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Tests all the functionalitites of the class Converter.
	*  Test Procedure:
	*  - Inittialize the Converter with an int template and convert it to string
	*/
public:
	ConverterTests() : TestUtilities::Test("ConverterTests", "Rahul") {}
	bool test()
	{
		Utilities::Converter<int> intConverter;
		std::string stringVal = intConverter.toString(45);
		bool  testToString = stringVal == "45";
		int value = intConverter.toValue("45");
		bool testToValue = 45 == value;
		return testToString && testToValue;
	}
};


class BoxTests : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Tests the working of the box class with a int template.
	*  Test Procedure:
	*  - Wrap the int with a Box class and check the return values
	*/
public:
	BoxTests() : TestUtilities::Test("BoxTests", "Rahul") {}
	bool test()
	{
		Utilities::Box<int> boxedint(45);

		int a = boxedint;
		bool testReturn = a == 45;

		boxedint = 56;
		bool testAssign = boxedint == 56;

		return testAssign && testReturn;
	}
};


class PersistFactoryTest : public TestUtilities::Test
{
	/*
	*  Test Description:
	*    Tests the working of the Persistent Facotry class with a std::string.
	*  Test Procedure:
	*  - wrap the string in a persistent factory and get the XML notation to compare the persistence
	*/
public:
	PersistFactoryTest() : TestUtilities::Test("PersistentFactoryTest", "Rahul") {}
	bool test()
	{
		Utilities::PersistFactory<std::string> stringPersistFacotry("lorem ipsum");
		std::string a = stringPersistFacotry;

		bool testSemanticsPreservation = stringPersistFacotry.append("ad") == "lorem ipsumad";

		std::string xml = stringPersistFacotry.toXml("String");
		bool testToXML = "<String>lorem ipsumad</String>";
		return testSemanticsPreservation && testToXML;
	}
};


//Export these tests

__declspec(dllexport) TestUtilities::ITestsContainer* get_TestContainer()
{
	TestUtilities::ITestsContainer* testsContainer = new TestUtilities::TestsContainer();
	TestUtilities::TestPtr test = TestUtilities::TestPtr(new ProcessCmdLineTests());
	TestUtilities::TestPtr convTest = TestUtilities::TestPtr(new ConverterTests());
	TestUtilities::TestPtr boxTests = TestUtilities::TestPtr(new BoxTests());
	TestUtilities::TestPtr persistFactoryTest = TestUtilities::TestPtr(new PersistFactoryTest());
	testsContainer->addTest(test);
	testsContainer->addTest(convTest);
	testsContainer->addTest(boxTests);
	testsContainer->addTest(persistFactoryTest);

	return testsContainer;
}
