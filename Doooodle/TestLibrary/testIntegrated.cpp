#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestIntegrated)
	{
	public:

		TEST_METHOD(testCheckCommandThroughLogic_Add)
		{
			Logic logic;
			string commandType = logic.getCommandType("add meeting from 2pm to 4pm tomorrow");
			string expected = "add";
			Assert::AreEqual(expected, commandType);
		}

		TEST_METHOD(testCheckCommandThroughLogic_Search)
		{
			Logic logic;
			string commandType = logic.getCommandType("search Wednesday");
			string expected = "search";
			Assert::AreEqual(expected, commandType);
		}

		TEST_METHOD(testCheckCommandThroughLogic_Add2)
		{
			Logic logic;
			string commandType = logic.receiveCommand("add Buy birthday present for Jim by 3 June");
			string expected = "Deadline task: Buy birthday present for Jim  by 3 Jun 23:59 successfully added.\n";
			Assert::AreEqual(expected, commandType);
		}
	};
} 