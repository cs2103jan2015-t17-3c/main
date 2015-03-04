
#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Parser {

private:
	static const string DELIMITERS;
	static const string TIME_INDICATORS[];
	static const int NO_OF_TIME_INDICATORS;

	string getCommandType(string);
	string getUserTask(string);
	string getStartDetail(string);
	string getEndDetail(string);


public:
	Parser();
	~Parser();
	void processCommand(string,string&,string&,string&,string&);
};

#endif