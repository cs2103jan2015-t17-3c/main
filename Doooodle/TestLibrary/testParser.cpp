#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{		
	TEST_CLASS(TestParser)
	{
	public:
		
		TEST_METHOD(testGetCommandType)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add abc", A, B, C, D);
			string expected = "add";
			Assert::AreEqual(expected,A);
		}

		TEST_METHOD(testGetUserTask)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add meeting at 14:00", A, B, C, D);
			string expected = "meeting";
			Assert::AreEqual(expected,B);
		}

		TEST_METHOD(testGetStartDetail1)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add meeting from 14:00 to 15:00", A, B, C, D);
			string expected = "14:00";
			Assert::AreEqual(expected, C);
		}


		TEST_METHOD(testGetStartDetail2)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add meeting by today", A, B, C, D);
			string expected = "";
			Assert::AreEqual(expected, C);
		}

		TEST_METHOD(testGetEndDetail1)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add submit work by today", A, B, C, D);
			string expected = "today";
			Assert::AreEqual(expected, D);
		}

		TEST_METHOD(testGetEndDetail2)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add meeting with bob from 14:00 to 15:00", A, B, C, D);
			string expected = "15:00";
			Assert::AreEqual(expected, D);
		}
	};
}