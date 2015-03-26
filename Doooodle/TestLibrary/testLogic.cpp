#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(testLogic) {
	public:

		TEST_METHOD(TestIsSearch_1) {
			Logic logic;
			Assert::IsFalse(logic.isSearch("add meeting from 3pm to 5pm"));
		}

		TEST_METHOD(TestIsSearch_2) {
			Logic logic;
			Assert::IsTrue(logic.isSearch("search swimming"));
		}

		TEST_METHOD(TestIsSearch_3) {
			Logic logic;
			Assert::IsFalse(logic.isSearch("searc swimming"));
		}

		TEST_METHOD(TestExecuteTask_1) {
			Logic logic;
			string displayMessage = logic.executeTask(Logic::TASK_TYPE::SEARCH, 0);
			string expected = " ";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(TestExecuteTask_2) {
			Logic logic;
			string displayMessage = logic.executeTask(Logic::TASK_TYPE::UNDO, 0);
			string expected = "Undo is successfully performed";
			Assert::AreEqual(expected, displayMessage);
		}

		/*
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
		*/

	};
}
