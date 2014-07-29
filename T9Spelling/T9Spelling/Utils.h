/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include <string>
#include <iostream>

class Utils
{
public:
	Utils(void);
	~Utils(void);

public:
	void getInput(const std::string &msg, int &i, int lowLimit, int highLimit);
	void getInput(const std::string &msg, std::string &str, size_t limit);
	std::string intToStr(int num);
	void printCase(int caseNum, const std::string &outputStr);
	void criticalErrorMsg(const std::string &msg);

private:
	bool isStringAllowed(const std::string &str);	
};



