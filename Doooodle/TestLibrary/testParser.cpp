#include "stdafx.h"
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibrary
{
	TEST_CLASS(TestParser){
public:

	TEST_METHOD(testProcessCommand_1_add){
		Parser parser;
		std::ostringstream oss1;
		std::ostringstream oss2;
		std::ostringstream oss3;
		std::ostringstream oss4;
		std::ostringstream oss5;
		std::ostringstream oss6;
		std::ostringstream oss7;
		std::ostringstream oss8;
		std::string input="add project due by 6 June";
		std::string commandType;
		std::string userTask;
		date d1;
		date d2;
		ptime t1;
		ptime t2;
		int num;
		parser.processCommand(input, commandType, userTask, d1, d2, t1, t2, num);
		std::string expectCommandType="add";
		std::string expectUserTask="project due";
		date expectD1;
		date expectD2{2015,6,6};
		ptime expectT1;
		ptime expectT2{ expectD2, hours(23) + minutes(59) + seconds(59) };
		int expectNum=-1;
		oss1<<d1;
		oss2<<d2;
		oss3<<t1;
		oss4<<t2;
		oss5<<expectD1;
		oss6<<expectD2;
		oss7<<expectT1;
		oss8<<expectT2;
		Assert::AreEqual(expectNum, num);
		Assert::AreEqual(expectCommandType, commandType);
		Assert::AreEqual(expectUserTask, userTask);
		Assert::AreEqual(expectNum, num);
		Assert::AreEqual(oss1.str(), oss5.str());
		Assert::AreEqual(oss2.str(), oss6.str());
		Assert::AreEqual(oss3.str(), oss7.str());
		Assert::AreEqual(oss4.str(), oss8.str());
	}
	};
}