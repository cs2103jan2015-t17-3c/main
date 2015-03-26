#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{		
	TEST_CLASS(TestDateParser)
	{
	public:
		
		TEST_METHOD(testDateParserValid1)
		{
			DateParser dateparser;
			string input = "2015/02/03";
			boost::gregorian::date d=dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(2015,02,03);
			ostringstream oss1,oss2;
			oss1 << expectedD;
			string expected=oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDateParserValid2)
		{
			DateParser dateparser;
			string input = "2015/02/28";
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(2015, 02, 28);
			ostringstream oss1, oss2;
			oss1 << expectedD;
			string expected = oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDateParserValid3)
		{
			DateParser dateparser;
			string input = "2100/12/31";
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(2100, 12, 31);
			ostringstream oss1, oss2;
			oss1 << expectedD;
			string expected = oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDateParserInvalid1)
		{
			DateParser dateparser;
			string input = "2015*02*28";
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(not_a_date_time);
			ostringstream oss1, oss2;
			oss1 << expectedD;
			string expected = oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDateParserInvalid2)
		{
			DateParser dateparser;
			string input = "2014/03/22";
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(not_a_date_time);
			ostringstream oss1, oss2;
			oss1 << expectedD;
			string expected = oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(testDateParserInvalid3)
		{
			DateParser dateparser;
			string input = "2017/04/31";
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(max_date_time);
			ostringstream oss1, oss2;
			oss1 << expectedD;
			string expected = oss1.str();
			oss2 << d;
			string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}

	};
}