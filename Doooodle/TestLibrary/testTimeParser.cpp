#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestTimeParser)
	{
	public:

		TEST_METHOD(testTimeParserValid1)
		{
			TimeParser timeparser;
			string input = "22:04";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(22) + boost::posix_time::minutes(4));
			ostringstream oss1, oss2;
			oss1 << expectedT;
			string expected = oss1.str();
			oss2 << t;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(testTimeParserValid2)
		{
			TimeParser timeparser;
			string input = "25:01";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(22) + boost::posix_time::minutes(4));
			ostringstream oss1, oss2;
			oss1 << expectedT;
			string expected = oss1.str();
			oss2 << t;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

	};
}