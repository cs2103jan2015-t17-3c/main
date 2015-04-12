//@author A0115016X -unused
#ifndef UI_H_
#define UI_H_

#include "Logic.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>

class UI {

private:
	
	Logic logic;
	static const std::string MESSAGE_ADD;
	static const std::string MESSAGE_DEFAULT;
	static const std::string MESSAGE_DEFAULT_CHECK;
	static const std::string MESSAGE_WELCOME;
	static const std::string MESSAGE_TOPTEN;
	static const std::string MESSAGE_FLOAT;
	static const std::string MESSAGE_SEARCH;
	static const std::string MESSAGE_CHECK;
	static const std::string MESSAGE_CATEGORICAL_TASK1;
	static const std::string MESSAGE_CATEGORICAL_TASK2;
	static const std::string MESSAGE_CHECK_ADD;
	static const std::string MESSAGE_CHECK_DELETE;
	static const std::string MESSAGE_CHECK_SEARCH;
	static const std::string MESSAGE_CHECK_EDIT;
	static const std::string MESSAGE_CHECK_ARCHIVE;

	void printToUser(std::string);
	void printVectorToUser(std::vector<std::string>);
	void printEmptyLine(int);
	void printSearchLine(int);
	//bool checkOverdue(std::string);

public:
	UI(void);
	~UI(void);
	void readMessage();
};
#endif



