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

		TEST_METHOD(testGetUserCommand)
		{
			Parser parser;
			string A, B, C, D;
			parser.processCommand("add meeting at 14:00", A, B, C, D);
			string expected = "meeting";
			Assert::AreEqual(expected,B);
		}

	};
}