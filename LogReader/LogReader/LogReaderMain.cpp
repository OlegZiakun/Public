/*
   Copyright (C) Oleg Ziakun
*/

#include "stdafx.h"
#include "LogReaderLauncher.h"

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage: LogReader.exe <regular expression> <file name>" << std::endl;
		std::cout << "Please note: if you are use spaces in the filter line take the filter in quotes" << std::endl;
		std::cout << "You can find results in res.txt file in program directory" << std::endl;
		
		system("pause");

		return 0;
	}

	CLogReaderLauncher logReaderLauncher(1024);

	logReaderLauncher.Open(argv[2]);
	logReaderLauncher.SetFilter(argv[1]);

	std::cout << "working...\n";

	logReaderLauncher.Flush();

	system("pause");

	return 0;
}

