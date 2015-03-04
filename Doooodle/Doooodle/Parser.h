
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