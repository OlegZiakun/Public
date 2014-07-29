/*
   Copyright (C) Oleg Ziakun
*/

#include "Utils.h"
#include <sstream>
#include <string>

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}

void Utils::getInput(const std::string &msg, int &i, int lowLimit, int highLimit) 
{ 
	if(lowLimit >= highLimit)
	{
		std::cout << "low limit >= high limit, please correct" << std::endl;
		exit(EXIT_FAILURE);
	}

	bool isInputOK = false;

	while(!isInputOK)
	{
		std::cout << msg << " " << "> "; 

		if(!(std::cin >> i) || i < lowLimit || i > highLimit)	
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Wrong input, please try again, you need enter a digit >= " << lowLimit << " and <= " << highLimit << std::endl;

			continue;
		}

		isInputOK = true;
	}

	std::cin.ignore();
} 

void Utils::getInput(const std::string &msg, std::string &str, size_t limit) 
{ 
	bool isInputOK = false;

	while(!isInputOK)
	{
		std::cout << msg << " " << "> "; 	
		std::getline(std::cin, str);

		if(!isStringAllowed(str) || (str.length() > limit))	
		{
			std::cin.clear();
			std::cout << "Wrong input, each message will consist of only lowercase characters a-z and space characters ' ' and length of message in characters >= " << limit << ". Please try again." << std::endl;

			continue;
		}

		isInputOK = true;
	}
} 

bool Utils::isStringAllowed(const std::string &str)
{
	bool isAllowed;

	for(size_t i = 0; i < str.length(); ++i)	
	{
		char letter = str[i];

		if((isalpha(letter) && !isupper(letter)) || isspace(letter)) 
			isAllowed = true;
		else
		{
			isAllowed = false;
			break;
		}
	}

	return isAllowed;
}

std::string Utils::intToStr(int num)
{
	std::ostringstream ostringStream;
	ostringStream << num;
	return ostringStream.str();
}

void Utils::printCase(int caseNum, const std::string &outputStr)
{
	std::cout << "Case #" << Utils().intToStr(caseNum) << ": "  << outputStr << std::endl; 
}

void Utils::criticalErrorMsg(const std::string &msg)
{
	std::cout << std::endl << msg; 
	exit(EXIT_FAILURE);
}