#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestTimeParser)
	{
	public:

		TEST_METHOD(standardTime_1_Valid)
		{
			TimeParser timeparser;
			std::string input = "22:04";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(22) + boost::posix_time::minutes(4));
			std::ostringstream  oss1, oss2;
			oss1 << expectedT;
			std::string expected = oss1.str();
			oss2 << t;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(standardTime_2_Invalid)
		{
			TimeParser timeparser;
			std::string input = "25:01";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(max_date_time);
			std::ostringstream  oss1, oss2;
			oss1 << expectedT;
			std::string expected = oss1.str();
			oss2 << t;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(standardTime_3_Invalid)
		{
			TimeParser timeparser;
			std::string input = "23*22";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(not_a_date_time);
			std::ostringstream  oss1, oss2;
			oss1 << expectedT;
			std::string expected = oss1.str();
			oss2 << t;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(standardTime_4_Invalid)
		{
			TimeParser timeparser;
			std::string input = "23:66";
			boost::posix_time::ptime t = timeparser.standardTime(input);
			boost::posix_time::ptime expectedT(max_date_time);
			std::ostringstream  oss1, oss2;
			oss1 << expectedT;
			std::string expected = oss1.str();
			oss2 << t;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

	};
}