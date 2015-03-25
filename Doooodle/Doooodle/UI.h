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
	static const string MESSAGE_WELCOME;
	static const string MESSAGE_TOPFIVE;

	void printToUser(string);
	void printVectorToUser(vector<string>);

public:
	UI(void);
	~UI(void);
	void readMessage();
};
#endif



