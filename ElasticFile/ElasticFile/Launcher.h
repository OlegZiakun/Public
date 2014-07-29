/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"
#include "FileIO.h"

class Launcher
{
public:
	Launcher();
	~Launcher();

public:
	void GetInput();
	void CreateFile();
	void GeneratingFileWithRandomStrings();
	void InsertingRecords();
	void ReadEvery10thRecord();
	void DeleteEveryEvenPair();

private:
	std::string fileName = "file.bin";
	int iterations, tailIterations;
	bool periodicalFlushing = false;
	bool isAlowedValue = false;
	const int randomStrCount = 1000;
	/*
	reserveSize is responsible for data caching, so that a smaller value will increase the number of disk read/write operations and reduce the program speed,
	and vice versa increasing this value will reduce the number of disk read/write operations, which, in turn, will increase the programs speed.
	However, please note that too large values ​​can lead to a shortage of memory, and the completion of the program. Now is set the optimal value.
	*/
	int reserveSize = 10000000;
	FileIO *fileIO;
	FILE *file;
	Utils utils;
	int m, M, N;
};

