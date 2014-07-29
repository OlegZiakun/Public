/*
   Copyright (C) Oleg Ziakun
*/

#include "Launcher.h"

Launcher::Launcher()
{
	fileIO = Utils::allocate<FileIO>();
}

Launcher::~Launcher()
{
	delete fileIO;
}

void Launcher::GetInput()
{
	utils.WelcomeScreen();

	while (!isAlowedValue)
	{
		utils.GetInput("Enter the length for the first pass", m);
		utils.GetInput("Enter the length for the second pass", M);
		utils.GetInput("Enter the number of iterations>", N);

		isAlowedValue = utils.AlowedValue(m, M, N);
	}
}

void Launcher::CreateFile()
{
	fileIO->SetFileName(fileName);

	file = fileIO->FileOpen(fileName, Operations::Create);

	if (file == NULL)
		Utils::ErrorFile("creating");
}

void Launcher::GeneratingFileWithRandomStrings()
{
	std::cout << "Step 1: generating file with random strings..." << std::endl;

	const int randomStrCount = 1000;

	utils.RandomizeStrings(m, randomStrCount);
	utils.StartOfPerformance();

	for (int i = 0; i < N; ++i)
		fileIO->FileWrite(file, utils.GetRandomString(), m, true);

	if (!fileIO->FileClose(file))
		Utils::ErrorFile("closing");

	std::cout << "Step 1 done" << std::endl;

	utils.EndOfPerformance();
	utils.ShowPerformanceTime("Performance time for \"generated file\": ");
	utils.ShowInfo(fileName, utils.GetFormatFileSize(fileName));
}

void Launcher::InsertingRecords()
{
	std::cout << "Step 2: inserting records..." << std::endl;

	if (N < reserveSize)
		reserveSize = N;
	else
	{
		iterations = N / reserveSize;
		tailIterations = N % reserveSize;
		periodicalFlushing = true;
	}

	fileIO->GetOperations().reserve(reserveSize);
	utils.RandomizeStrings(M, randomStrCount);

	utils.StartOfPerformance();

	Operations operation(Operations::Insert);

	if (periodicalFlushing)
	{
		int offset = 0;
		bool rewritable = false;

		for (int i = 0; i < iterations; ++i)
		{
			file = fileIO->FileOpen(fileName, Operations::Read);

			if (file == NULL)
				Utils::ErrorFile("reading");

			for (int j = 1; j <= reserveSize; ++j)
			{
				operation.setOperation((j * m) + offset, utils.GetRandomString(), M);
				fileIO->setOperation(operation);
			}

			if (i == (iterations - 1) && tailIterations == 0)
				rewritable = true;

			fileIO->Flush(file, rewritable, offset);

			offset += (reserveSize * m);
		}

		if (tailIterations > 0)
		{
			file = fileIO->FileOpen(fileName, Operations::Read);

			if (file == NULL)
				Utils::ErrorFile("reading");

			for (int i = 1; i <= tailIterations; ++i)
			{
				operation.setOperation((i * m) + offset, utils.GetRandomString(), M);
				fileIO->setOperation(operation);
			}

			fileIO->Flush(file, true, offset);
		}

	}
	else
	{
		file = fileIO->FileOpen(fileName, Operations::Read);

		if (file == NULL)
			Utils::ErrorFile("reading");

		for (int i = 1; i <= N; ++i)
		{
			operation.setOperation(i * m, utils.GetRandomString(), M);
			fileIO->setOperation(operation);
		}

		fileIO->Flush(file);
	}

	utils.EndOfPerformance();

	std::cout << "Step 2 done" << std::endl;

	utils.ShowPerformanceTime("Performance time for \"insert into file\": ");

	std::ostringstream amountStr;

	amountStr << (M * N);
	utils.ShowInfo(fileName, amountStr.str().c_str());
}

void Launcher::ReadEvery10thRecord()
{
	file = fileIO->FileOpen(fileName, Operations::Read);

	if (file == NULL)
		Utils::ErrorFile("creating");

	const int numToAnalyze = 10;

	std::cout << "Step 3: read every 10th record..." << std::endl;

	if (numToAnalyze > N)
		std::cout << "The file is to small to perform task: \"to read every 10th record from the file and output the maximum string (alphabetical order)\"" << std::endl;
	else
	{
		fileIO->InitMaxString();
		utils.StartOfPerformance();

		for (int i = 1; i <= N; ++i)
		{
			if ((i % numToAnalyze) == 0)
				fileIO->SetMaxString(file, i / 2 * (m + M) - M, M);
		}

		utils.EndOfPerformance();

		std::cout << "Step 3 done" << std::endl;

		utils.ShowPerformanceTime("Performance time for \"read every 10th record\": ");
		std::cout << "The maximum string is: " << fileIO->GetMaxString() << std::endl;
		utils.ShowInfo(fileName, utils.GetFormatFileSize(fileName));
	}

	if (!fileIO->FileClose(file))
		Utils::ErrorFile("closing");
}

void Launcher::DeleteEveryEvenPair()
{
	std::cout << "Step 4: delete every even pair [m][M] from the file, i.e [m][M][m][M][m][M][m][M]..." << std::endl;

	Operations operation(Operations::Delete);
	int pairToDeleteSize = m + M;

	utils.StartOfPerformance();

	if (periodicalFlushing)
	{
		bool rewritable = false;
		int offset = 0;

		for (int i = 0; i < iterations; ++i)
		{
			file = fileIO->FileOpen(fileName, Operations::Read);
			if (file == NULL)Utils::ErrorFile("creating");

			for (int j = 0; j < reserveSize; j += 2)
			{
				operation.setOperation(j * pairToDeleteSize + offset, NULL, pairToDeleteSize);
				fileIO->setOperation(operation);
			}

			if (i == (iterations - 1) && tailIterations == 0)
				rewritable = true;

			fileIO->Flush(file, rewritable);
			offset += reserveSize;
		}

		if (tailIterations > 0)
		{
			file = fileIO->FileOpen(fileName, Operations::Read);

			if (file == NULL)
				Utils::ErrorFile("creating");

			for (int i = 0; i < tailIterations; i += 2)
			{
				operation.setOperation(i * pairToDeleteSize + offset, NULL, pairToDeleteSize);
				fileIO->setOperation(operation);
			}

			fileIO->Flush(file);
		}
	}
	else
	{
		file = fileIO->FileOpen(fileName, Operations::Read);

		if (file == NULL)
			Utils::ErrorFile("creating");

		for (int i = 0; i < N; i += 2)
		{
			operation.setOperation(i * pairToDeleteSize, NULL, pairToDeleteSize);
			fileIO->setOperation(operation);
		}

		fileIO->Flush(file);
	}


	utils.EndOfPerformance();

	std::cout << "Step 4 done" << std::endl;
	utils.ShowPerformanceTime("Performance time for \"delete every even pair\": ");
	utils.ShowInfo(fileName, utils.GetFormatFileSize(fileName));
}

