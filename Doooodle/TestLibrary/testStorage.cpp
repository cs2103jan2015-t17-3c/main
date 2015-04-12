#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace boost::gregorian;
using namespace boost::posix_time;

namespace TestLibrary
{
	TEST_CLASS(TestStorage)
	{
	public:
		TEST_METHOD(testAddDeadlineTask)
		{
			date d(2015, 3, 25);
			Storage storage;
			ptime t( date(d), hours(22) + minutes(0));
			std::string A = "task";
			std::string expected="Deadline task: task by 25 Mar 22:00 successfully added.\n";
			std::string actual = storage.addDeadlineTask(A, d, t);
			Assert::AreEqual(expected, actual);	
		}
		TEST_METHOD(testAddNormalTask)
		{
			date d(2015, 3, 25);
			Storage storage;
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			std::string A = "task";
			std::string expected = "Normal task: task [25 Mar 22:00]-[25 Mar 23:00] successfully added.\n";
			std::string actual = storage.addNormalTask(A, d,d, t1,t2);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testAddFloatingTask)
		{
			Storage storage;
			std::string A = "task";
			std::string expected = "Floating task: task successfully added.\n";
			std::string actual = storage.addFloatingTask(A);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveDeadlineSize)
		{
			Storage storage;
			int expected = 0;
			int actual = storage.retrieveDeadlineSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveNormalSize)
		{
			Storage storage;
			int expected = 0;
			int actual = storage.retrieveNormalSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveFloatingSize)
		{
			Storage storage;
			int expected = 0;
			int actual = storage.retrieveFloatingSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveFloatingSize1)
		{
			Storage storage;
			std::string A = "task";
			storage.addFloatingTask(A);
			int expected = 1;
			int actual = storage.retrieveFloatingSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveDeadlineSize1)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			storage.addDeadlineTask(A,d,t1);
			int expected = 1;
			int actual = storage.retrieveDeadlineSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveNormalSize1)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addNormalTask(A, d, d,t1,t2);
			int expected = 1;
			int actual = storage.retrieveNormalSize();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveTopList)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addNormalTask(A, d, d, t1, t2);
			int expected = 1;
			std::vector<std::string> temp = storage.retrieveTopList();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveTopList1)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addDeadlineTask(A, d, t2);
			int expected = 1;
			std::vector<std::string> temp = storage.retrieveTopList();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveTopList0)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addFloatingTask(A);
			int expected = 0;
			std::vector<std::string> temp = storage.retrieveTopList();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveTopListEmpty)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			int expected = 0;
			std::vector<std::string> temp = storage.retrieveTopList();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveFloatingTask)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addFloatingTask(A);
			int expected = 1;
			std::vector<std::string> temp = storage.retrieveFloatingTask();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveFloatingTaskDetails)
		{
			Storage storage;
			std::string A = "task";
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			ptime t2(date(d), hours(23) + minutes(0));
			storage.addFloatingTask(A);
			std::string expected = "01. task                     ";
			std::vector<std::string> temp = storage.retrieveFloatingTask();
			std::string actual = temp[0];
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testCDfail)
		{
			Storage storage;
			std::string A = "whatever";
			std::string expected = "SetCurrentDirectory failed\n";
			std::string actual = storage.changeDirectory(A);;
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testCDsuccess)
		{
			Storage storage;
			std::string A = "C:\ ";
			std::string expected = "Set current directory to C: ";
			std::string actual = storage.changeDirectory(A);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDeleteTask)
		{
			Storage storage;
			std::string A = "task";
			storage.addFloatingTask(A);
			std::string expected = "task is successfully deleted.\n";
			std::string actual = storage.deleteTask(1);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDeleteTaskfail)
		{
			Storage storage;
			std::string A = "task";
			std::string expected = "Wrong index.\n";
			std::string actual = storage.deleteTask(1);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testCompleteTaskfail)
		{
			Storage storage;
			std::string A = "task";
			std::string expected = "Wrong index.\n";
			std::string actual = storage.completeTask(1);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testCompleteTask)
		{
			Storage storage;
			std::string A = "task";
			storage.addFloatingTask(A);
			std::string expected = "task is successfully archived.\n";
			std::string actual = storage.completeTask(1);
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testSearchTask)
		{
			Storage storage;
			date nonDate(not_a_date_time);
			ptime nonTime(not_a_date_time);
			std::string A = "task";
			storage.addFloatingTask(A);
			int expected = 1;
			std::vector<std::string> temp = storage.searchTask("ta",nonDate,nonTime);
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testSearchTaskNotFound)
		{
			Storage storage;
			date nonDate(not_a_date_time);
			ptime nonTime(not_a_date_time);
			std::string A = "task";
			int expected = 0;
			std::vector<std::string> temp = storage.searchTask("ta", nonDate, nonTime);
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testUndoAdd)
		{
			Storage storage;
			date nonDate(not_a_date_time);
			ptime nonTime(not_a_date_time);
			std::string A = "task";
			storage.addFloatingTask(A);
			std::string expected = "Undo is successfully performed.\n";
			std::string actual = storage.undoAdd();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testUndoDelete)
		{
			Storage storage;
			date nonDate(not_a_date_time);
			ptime nonTime(not_a_date_time);
			std::string A = "task";
			storage.addFloatingTask(A);
			storage.deleteTask(1);
			std::string expected = "Undo is successfully performed.\n";
			std::string actual = storage.undoDelete();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testUndoComplete)
		{
			Storage storage;
			date nonDate(not_a_date_time);
			ptime nonTime(not_a_date_time);
			std::string A = "task";
			storage.addFloatingTask(A);
			storage.completeTask(1);
			std::string expected = "Undo is successfully performed.\n";
			std::string actual = storage.undoComplete();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testRetrieveColourIndex)
		{
			Storage storage;
			date d(2015, 3, 25);
			ptime t1(date(d), hours(22) + minutes(0));
			std::string A = "task";
			storage.addDeadlineTask(A,d,t1);
			int expected = 0;
			std::vector<int> temp = storage.retrieveColourIndex();
			int actual = temp.size();
			Assert::AreEqual(expected, actual);
		}

		
	};
}
