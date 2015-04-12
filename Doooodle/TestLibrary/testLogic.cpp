//@author A0108562H
#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary {
	TEST_CLASS(testLogic) {
	public:
		//Black Box integrated testing for Logic
		TEST_METHOD(receiveCommand_1_Error) {
			Logic logic;	
			std::string displayMessage = logic.receiveCommand("");
			std::string expected = "ERROR!";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_2_addNormalTask) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			std::string expected = "Normal task: meeting [31 Dec 14:00]-[31 Dec 16:00] successfully added.\n";
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_3_addFloatingTask) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add swimming");
			std::string expected = "Floating task: swimming successfully added.\n";
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_4_addNormalTask) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			std::string expected = "Normal task: bintan holiday [24 Aug      ]-[28 Aug      ] successfully added.\n";
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_5_DeleteBoundary1) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			displayMessage = logic.receiveCommand("delete 0");
			std::string expected = "Wrong index.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_6_DeleteBoundary2) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			displayMessage = logic.receiveCommand("delete 5");
			std::string expected = "Wrong index.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}


		TEST_METHOD(receiveCommand_7_Delete) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			displayMessage = logic.receiveCommand("delete 1");
			std::string expected = "bintan holiday is successfully deleted.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_8_Search) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			displayMessage = logic.receiveCommand("search aug");
			std::string expected = " ";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_9_Complete) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			displayMessage = logic.receiveCommand("complete 1");
			std::string expected = "bintan holiday is successfully archived.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_10_CompleteBoundary1) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			displayMessage = logic.receiveCommand("complete 0");
			std::string expected = "Wrong index.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_11_CompleteBoundary2) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			displayMessage = logic.receiveCommand("complete 5");
			std::string expected = "Wrong index.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_12_Undo) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add bintan holiday 24 aug to 28 aug");
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("add swimming");
			logic.receiveCommand("complete 3");
			displayMessage = logic.receiveCommand("undo");
			std::string expected = "Undo is successfully performed.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_13_UndoBoundary) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add meeting 31 December 2pm to 4pm");
			logic.receiveCommand("undo");
			displayMessage = logic.receiveCommand("undo");
			std::string expected = "Nothing to undo!";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_14_AddDeadlineTask) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add project submission by 10 Nov");
			std::string expected = "Deadline task: project submission by 10 Nov 23:59 successfully added.\n";
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_15_AddRecurringTask1) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add gym workout 30 apr; weekly; 4");
			std::string expected = "Recurring Task is successfully added!\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_16_AddRecurringTask2) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("add gym workout 30 apr; weekly2; 0730");
			std::string expected = "Recurring Task is successfully added!\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}
		
		TEST_METHOD(receiveCommand_17_DeleteRecurringTask) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add gym workout 30 apr; weekly; 4");
			displayMessage = logic.receiveCommand("delete 1");
			std::string expected = "Recurring task is successfully deleted.\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_18_EditRecurringTask) {
			Logic logic;
			std::string displayMessage;
			logic.receiveCommand("add gym workout 30 apr; weekly; 4");
			displayMessage = logic.receiveCommand("edit 1 cardio workout");
			std::string expected = "task is successfully edited\n";
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_19_UndoAddRecurringTask) {
			Logic logic;
			logic.receiveCommand("add gym workout 30 apr; weekly; 4");
			logic.receiveCommand("undo");
			int size = logic.getDeadlineSize();
			int expected = 0;
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(receiveCommand_20_UndoDeleteRecurringTask) {
			Logic logic;
			logic.receiveCommand("add gym workout 30 apr; weekly; 4");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("undo");
			int size = logic.getDeadlineSize();
			int expected = 5;
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(receiveCommand_21_DisplayBoundary) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("display archiv");
			std::string expected = "ERROR!";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_22_DisplayArchive) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("display archive");
			std::string expected = " ";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_23_DisplayNormal) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("display normal");
			std::string expected = " ";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(receiveCommand_24_displayDeadline) {
			Logic logic;
			std::string displayMessage = logic.receiveCommand("display deadline");
			std::string expected = " ";
			Assert::AreEqual(expected, displayMessage);
		}

		TEST_METHOD(getNormalSize_25) {
			Logic logic;
			logic.receiveCommand("add cycling 1 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 2 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 3 jun 2pm to 4pm");
			logic.receiveCommand("add homework 1 jun 2pm");
			logic.receiveCommand("add homework 2 jun 2pm");
			logic.receiveCommand("add homework 3 jun 2pm");
			logic.receiveCommand("add homework 4 jun 2pm");
			logic.receiveCommand("add homework 5 jun 2pm");
			logic.receiveCommand("add shopping for Jack");
			logic.receiveCommand("add shopping for John");
			int size = logic.getNormalSize();
			int expected = 3;
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(getFloatingSize_26) {
			Logic logic;
			logic.receiveCommand("add cycling 1 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 2 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 3 jun 2pm to 4pm");
			logic.receiveCommand("add homework 1 jun 2pm");
			logic.receiveCommand("add homework 2 jun 2pm");
			logic.receiveCommand("add homework 3 jun 2pm");
			logic.receiveCommand("add homework 4 jun 2pm");
			logic.receiveCommand("add homework 5 jun 2pm");
			logic.receiveCommand("add shopping for Jack");
			logic.receiveCommand("add shopping for John");
			int size = logic.getFloatingSize();
			int expected = 2;
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(getDeadlineSize_27) {
			Logic logic;
			logic.receiveCommand("add cycling 1 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 2 jun 2pm to 4pm");
			logic.receiveCommand("add cycling 3 jun 2pm to 4pm");
			logic.receiveCommand("add homework 1 jun 2pm");
			logic.receiveCommand("add homework 2 jun 2pm");
			logic.receiveCommand("add homework 3 jun 2pm");
			logic.receiveCommand("add homework 4 jun 2pm");
			logic.receiveCommand("add homework 5 jun 2pm");
			logic.receiveCommand("add shopping for Jack");
			logic.receiveCommand("add shopping for John");
			int size = logic.getDeadlineSize();
			int expected = 5;
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			logic.receiveCommand("delete 1");
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(getNormalSize_28_Boundary) {
			Logic logic;
			int size = logic.getNormalSize();
			int expected = 0;
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(getFloatingSize_29_Boundary) {
			Logic logic;
			int size = logic.getFloatingSize();
			int expected = 0;
			Assert::AreEqual(expected, size);
		}

		TEST_METHOD(getDeadlineSize_30_Boundary) {
			Logic logic;
			int size = logic.getDeadlineSize();
			int expected = 0;
			Assert::AreEqual(expected, size);
		}
	};
}
