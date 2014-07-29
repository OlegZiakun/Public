/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "LogReader.h"

class CLogReaderLauncher
{
public:
	CLogReaderLauncher(size_t bs);
	~CLogReaderLauncher();

public:
	void Open(const char *fileName);
	void SetFilter(const char *filter);
	void Flush();

private:
	CLogReader logReader;
	const size_t bufSize;
	char *buf;
};

