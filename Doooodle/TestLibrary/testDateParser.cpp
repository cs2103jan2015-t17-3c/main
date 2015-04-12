#include "stdafx.h"
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{		
	TEST_CLASS(TestDateParser){
	public:
		
		TEST_METHOD(standardiseDate_1_Valid){
			DateParser dateparser;
			std::string input = "2015/02/03";
			int dummy=0;
			date d=dateparser.standardiseDate(input,input,input,dummy,dummy);
			date expectedD(2015,02,03);
			std::ostringstream oss1,oss2;
			oss1 << expectedD;
			std::string expected=oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_2_Valid)
		{
			DateParser dateparser;
			std::string input = "March";
			std::string input1 = "3";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input1, dummy, dummy);
			boost::gregorian::date expectedD(2015, 03, 03);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_3_Valid)
		{
			DateParser dateparser;
			std::string input = "dec";
			std::string input1 = "2";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input1, input, input, dummy, dummy);
			boost::gregorian::date expectedD(2015, 12, 02);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_4_Valid)
		{
			DateParser dateparser;
			std::string input = "2015/02/28";
			int dummy=0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(2015, 02, 28);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_5_Valid)
		{
			DateParser dateparser;
			std::string input = "2100/12/31";
			int dummy=0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(2100, 12, 31);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_6_Invalid)
		{
			DateParser dateparser;
			std::string input = "2015*02*28";
			int dummy=0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(not_a_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_7_Invalid)
		{
			DateParser dateparser;
			std::string input = "1899/03/22";
			int dummy=0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(not_a_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_8_Invalid)
		{
			DateParser dateparser;
			std::string input = "2017/04/31";
			int dummy=0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(max_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_9_Invalid)
		{
			DateParser dateparser;
			std::string input = "Feb";
			std::string input1 = "29";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input1, dummy, dummy);
			boost::gregorian::date expectedD(max_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_10_Invalid)
		{
			DateParser dateparser;
			std::string input = "wed";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(not_a_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		//Valid until 18 April
		TEST_METHOD(standardiseDate_11_Valid)
		{
			DateParser dateparser;
			std::string input = "saturday";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input, input, input, dummy, dummy);
			boost::gregorian::date expectedD(2015,4,18);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_12_Valid)
		{
			DateParser dateparser;
			std::string input = "0505";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(2015,5,5);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_13_Valid)
		{
			DateParser dateparser;
			std::string input = "20160622";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(2016, 6, 22);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(standardiseDate_14_Invalid)
		{
			DateParser dateparser;
			std::string input = "20160631";
			int dummy = 0;
			boost::gregorian::date d = dateparser.standardiseDate(input);
			boost::gregorian::date expectedD(max_date_time);
			std::ostringstream oss1, oss2;
			oss1 << expectedD;
			std::string expected = oss1.str();
			oss2 << d;
			std::string actual = oss2.str();
			Assert::AreEqual(expected, actual);
		}
		TEST_METHOD(completeRecurring_15_Valid)
		{
			DateParser dateparser;
			date d1 = { 2015, 4, 24 };
			date d2 = { 2015, 4, 25 };
			ptime t1;
			std::vector<date> expectVecEndDate;
			std::vector<date> expectVecStartDate;
			std::string frequency = "weekly";
			std::vector<date> vecStartDate;
			std::vector<date> vecEndDate;
			std::vector <ptime> vecStartTime;
			std::vector<ptime> vecEndTime;
			vecStartTime.push_back(t1);
			vecEndTime.push_back(t1);
			int recurrence=3;
			int interval=2; 
			date finishDate = { 2015, 8, 8 };
			vecStartDate.push_back(d1);
			expectVecStartDate.push_back(d1);
			vecEndDate.push_back(d2);
			expectVecEndDate.push_back(d2);
			dateparser.completeRecurring(frequency,vecStartDate,vecEndDate,vecStartTime,vecEndTime,recurrence,interval,finishDate);
			std::ostringstream oss1, oss2;
			for (int i = 0; i < recurrence; i++){
				d1 = d1 + weeks(interval);
				d2 = d2 + weeks(interval);
				expectVecStartDate.push_back(d1);
				expectVecEndDate.push_back(d2);
			}
			for (int i = 0; i < vecEndDate.size(); i++){
				oss1 << expectVecStartDate[i];
				oss2 << vecStartDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
				oss1 << expectVecEndDate[i];
				oss2 << vecEndDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
			}
		}
		TEST_METHOD(completeRecurring_16_Valid)
		{
			DateParser dateparser;
			date d1 = { 2015, 4, 24 };
			date d2 = { 2015, 4, 25 };
			ptime t1;
			std::vector<date> expectVecEndDate;
			std::vector<date> expectVecStartDate;
			std::string frequency = "every year";
			std::vector<date> vecStartDate;
			std::vector<date> vecEndDate;
			std::vector <ptime> vecStartTime;
			std::vector<ptime> vecEndTime;
			vecStartTime.push_back(t1);
			vecEndTime.push_back(t1);
			int recurrence = 4;
			int interval = 4;
			date finishDate = { 2020, 8, 8 };
			vecStartDate.push_back(d1);
			expectVecStartDate.push_back(d1);
			vecEndDate.push_back(d2);
			expectVecEndDate.push_back(d2);
			dateparser.completeRecurring(frequency, vecStartDate, vecEndDate, vecStartTime, vecEndTime, recurrence, interval, finishDate);
			std::ostringstream oss1, oss2;
			for (int i = 0; i < recurrence; i++){
				d1 = d1 + years(interval);
				d2 = d2 + years(interval);
				expectVecStartDate.push_back(d1);
				expectVecEndDate.push_back(d2);
			}
			for (int i = 0; i < vecEndDate.size(); i++){
				oss1 << expectVecStartDate[i];
				oss2 << vecStartDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
				oss1 << expectVecEndDate[i];
				oss2 << vecEndDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
			}
		}
		TEST_METHOD(completeRecurring_17_Valid)
		{
			DateParser dateparser;
			date d1 = { 2015, 6, 24 };
			date d2 = { 2015, 6, 25 };
			ptime t1;
			std::vector<date> expectVecEndDate;
			std::vector<date> expectVecStartDate;
			std::string frequency = "monthly";
			std::vector<date> vecStartDate;
			std::vector<date> vecEndDate;
			std::vector <ptime> vecStartTime;
			std::vector<ptime> vecEndTime;
			vecStartTime.push_back(t1);
			vecEndTime.push_back(t1);
			int recurrence = -1;
			int interval = 1;
			date finishDate = { 2020, 8, 8 };
			vecStartDate.push_back(d1);
			expectVecStartDate.push_back(d1);
			vecEndDate.push_back(d2);
			expectVecEndDate.push_back(d2);
			dateparser.completeRecurring(frequency, vecStartDate, vecEndDate, vecStartTime, vecEndTime, recurrence, interval, finishDate);
			std::ostringstream oss1, oss2;
			for (int i = 0; i < 24; i++){
				d1 = d1 + months(interval);
				d2 = d2 + months(interval);
				expectVecStartDate.push_back(d1);
				expectVecEndDate.push_back(d2);
			}
			for (int i = 0; i < vecEndDate.size(); i++){
				oss1 << expectVecStartDate[i];
				oss2 << vecStartDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
				oss1 << expectVecEndDate[i];
				oss2 << vecEndDate[i];
				Assert::AreEqual(oss1.str(), oss2.str());
			}
		}
	};
}