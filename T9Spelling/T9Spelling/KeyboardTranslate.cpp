/*
   Copyright (C) Oleg Ziakun
*/

#include "stdafx.h"
#include "Keyboard.h"
#include "Utils.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Keyboard keyboard;
	Utils utils;
	int numOfCases;
	int lowCasesLimit = 1;
	int highCasesLimit = 100;
	int msgLimit = 1000;

	utils.getInput("The number of cases:", numOfCases, lowCasesLimit, highCasesLimit);

	for (int i = 1; i <= numOfCases; ++i)
	{
		std::string inputString;
		std::string outputString;

		utils.getInput("Enter case #" + utils.intToStr(i), inputString, msgLimit);

		outputString = keyboard.translate(inputString);
		utils.printCase(i, outputString);
	}

	system("pause");
	return 0;
}

