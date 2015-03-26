#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestStorage)
	{
	public:

		TEST_METHOD(testAddDeadlineTask)
		{
			boost::gregorian::date d(2015, 3, 25);
			Storage storage;
			boost::posix_time::ptime t(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(22) + boost::posix_time::minutes(0));
			string A = "task";
			string expected="Deadline task: task by 2015-Mar-25 22:00 successfully added.\n";
			string actual = storage.addDeadlineTask(A, d, t);
			Assert::AreEqual(expected, actual);
			
		}

	};
}
