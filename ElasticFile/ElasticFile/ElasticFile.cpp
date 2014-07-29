/*
   Copyright (C) Oleg Ziakun
*/

#include "stdafx.h"
#include "FileIO.h"
#include "Launcher.h"

int main(int argc, char* argv[])
{
	Launcher launcher;

	launcher.GetInput();
	launcher.CreateFile();

	launcher.GeneratingFileWithRandomStrings();
	launcher.InsertingRecords();
	launcher.ReadEvery10thRecord();
	launcher.DeleteEveryEvenPair();

	system("pause");

	return 0;
}