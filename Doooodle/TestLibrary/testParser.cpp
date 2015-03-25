#include "stdafx.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{		
	TEST_CLASS(TestParser)
	{
	public:
		
		TEST_METHOD(testProcessCommand)
		{
			Parser parser;
			boost::gregorian::date d1,d2;
			boost::posix_time::ptime t1, t2;
			string A="add meeting from 10pm to 11pm", B, C;
			int D;
			parser.processCommand(A, B, C, d1, d2, t1, t2, D);
			string expectedB = "add";
			string expectedC = "meeting";
			boost::gregorian::date expectedD1(not_a_date_time);
			boost::gregorian::date expectedD2(day_clock::local_day());
			int expectedD = -1;
			boost::posix_time::ptime expectedT1(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(22) + boost::posix_time::minutes(0));
			boost::posix_time::ptime expectedT2(boost::gregorian::date(boost::gregorian::day_clock::local_day()), boost::posix_time::hours(23) + boost::posix_time::minutes(0));
			Assert::AreEqual(expectedB,B);
			Assert::AreEqual(expectedC, C);
//			Assert::AreEqual(expectedD1, d1);
	//		Assert::AreEqual(expectedD2, d2);
		//	Assert::AreEqual(expectedT1, t1);
			//Assert::AreEqual(expectedT2, t2);
			Assert::AreEqual(expectedD, D);
		}

	};
}