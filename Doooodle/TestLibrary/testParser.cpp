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
			Assert::AreEqual(A, expected);
		}

	};
}