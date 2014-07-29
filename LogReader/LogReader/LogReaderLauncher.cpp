/*
   Copyright (C) Oleg Ziakun
   */

#include "stdafx.h"
#include "LogReaderLauncher.h"
#include "Utils.h"

CLogReaderLauncher::CLogReaderLauncher(size_t bs) :
bufSize(bs)
{
	buf = Utils::allocate<char>(bufSize);
}

CLogReaderLauncher::~CLogReaderLauncher()
{
	delete[] buf;
}

void CLogReaderLauncher::Open(const char *fileName)
{
	if (!logReader.Open(fileName))
	{
		std::cout << "File " << fileName << " not exists." << std::endl;
		system("pause");

		exit(EXIT_FAILURE);
	}
}

void CLogReaderLauncher::SetFilter(const char *filter)
{
	if (!logReader.SetFilter(filter))
	{
		std::cout << "Sorry, the filter is wrong. Please note: use \"?\" and \"*\" symbols to set a filter. Please try again. Good luck!" << std::endl;

		logReader.Close();
		system("pause");

		exit(EXIT_FAILURE);
	}
}

void CLogReaderLauncher::Flush()
{
	std::ofstream resultFile;
	char fileName[8] = "res.txt";
	resultFile.open(fileName);

	if (!resultFile.is_open())
	{
		std::cout << "Failed to open file to write result to." << std::endl;
		system("pause");

		exit(EXIT_FAILURE);
	}

	while (logReader.GetNextLine(buf, bufSize))
		resultFile << buf << std::endl;

	logReader.Close();
	resultFile.close();

	std::cout << "**** Done! Please check file " << fileName << " in program directory. ****" << std::endl;
}
