#ifndef UI_H_
#define UI_H_

#include "Logic.h"
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

	void printToUser(string);

public:
	UI(void);
	~UI(void);
	void readMessage();
};
#endif



