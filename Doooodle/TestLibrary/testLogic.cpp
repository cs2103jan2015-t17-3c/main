#include "stdafx.h"
/*include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(testLogic) {
	public:
		
		TEST_METHOD(TestLastCommandIsSearch_1) {
			Logic logic;
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[0]->commandType = "add";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[1]->commandType = "delete";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[2]->commandType = "undo";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[3]->commandType = "edit";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[4]->commandType = "add";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[5]->commandType = "search";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[6]->commandType = "delete";
			Assert::IsFalse(logic.lastCommandIsSearch());
		}

		TEST_METHOD(TestLastCommandIsSearch_2) {
			Logic logic;
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[0]->commandType = "add";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[1]->commandType = "delete";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[2]->commandType = "undo";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[3]->commandType = "edit";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[4]->commandType = "add";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[5]->commandType = "delete";
			logic.commandDetails.push_back(new CommandDetails());
			logic.commandDetails[6]->commandType = "search";
			Assert::IsTrue(logic.lastCommandIsSearch());
		}

		TEST_METHOD(TestIsSearch_1) {
			Logic logic;
			Assert::IsFalse(logic.isSearch("add meeting from 3pm to 5pm"));
		}

		TEST_METHOD(TestIsSearch_2) {
			Logic logic;
			Assert::IsFalse(logic.isSearch("search swimming"));
		}

	};
}*/