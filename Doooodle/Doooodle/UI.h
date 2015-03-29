#ifndef UI_H_
#define UI_H_

#include "Logic.h"
#include <boost/date_time.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class UI {

private:
	
	Logic logic;
	static const string MESSAGE_ADD;
	static const string MESSAGE_DEFAULT;
	static const string MESSAGE_DEFAULT_CHECK;
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_TOPTEN;
	static const string MESSAGE_FLOAT;
	static const string MESSAGE_SEARCH;
	static const string MESSAGE_CHECK;
	static const string MESSAGE_CHECK_ADD;
	static const string MESSAGE_CHECK_DELETE;
	static const string MESSAGE_CHECK_SEARCH;
	static const string MESSAGE_CHECK_EDIT;
	static const string MESSAGE_CHECK_ARCHIVE;
	static const int NUMBER_OF_TOTAL_LINES;
	static const int NUMBER_OF_SEARCH_LINES;
	void printToUser(string);
	void printVectorToUser(vector<string>);
	void printEmptyLine(int);
	void printSearchLine(int);
	bool checkOverdue(string);

public:
	UI(void);
	~UI(void);
	void readMessage();
};
#endif



