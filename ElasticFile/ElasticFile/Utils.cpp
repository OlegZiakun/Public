/*
   Copyright (C) Oleg Ziakun
*/

#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
	randomStrings.clear();

	for (std::vector<PBYTE>::const_iterator it = randomStrings.begin(); it != randomStrings.end(); ++it)
		delete[] * it;
}

void Utils::ShowPerformanceTime(std::string msg)
{
	std::cout << msg << GetPerformanceTime() << " seconds" << std::endl;
}

void Utils::GetInput(std::string msg, int &i)
{
	bool isInputOk = false;

	while (!isInputOk)
	{
		std::cout << msg << std::endl << "> ";

		if (!(std::cin >> i) || i <= 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Wrong input, please try again" << std::endl;

			continue;
		}

		isInputOk = true;
	}
}

void Utils::RandomizeStrings(int len, int count)
{
	for (int i = 0; i < count; ++i)
	{
		PBYTE buffer = allocate<BYTE>(len);

		memcpy(buffer, RandomString(len).c_str(), len);
		randomStrings.push_back(buffer);
	}
}

size_t Utils::GetFileSize(std::string filename)
{
	struct stat stat_buf;
	int rc = stat(filename.c_str(), &stat_buf);

	return rc == 0 ? stat_buf.st_size : -1;
}

std::string Utils::GetFormatFileSize(std::string filename)
{
	std::string sizeStr;
    float floatSize;
    std::ostringstream ostringstream;
	float KB = 1024.0f, MB = KB * 1024.0f;	
	size_t size = GetFileSize(filename);
	
	ostringstream << size;

	if (size > KB && size <= MB)
	{
		floatSize = (static_cast<float> (size) / KB);
		ostringstream.precision(GetPresicion(floatSize));
		ostringstream << " " << GetByteString(size) + " (" << floatSize << " KB)";
	}
	else if (size > MB)
	{
		floatSize = (static_cast<float> (size) / MB);
		ostringstream.precision(GetPresicion(floatSize));
		ostringstream << " " << GetByteString(size) + " (" << floatSize << " MB)";
	}

	if (size <= KB)
		sizeStr = ostringstream.str() + " " + GetByteString(size);
	else
		sizeStr = ostringstream.str();

	return sizeStr;
}

int Utils::GetPresicion(float size)
{
	int presicion = 3;

	if (size >= 10.0 && size < 100.0)
		presicion = 4;
	else if (size >= 100.0 && size < 1000.0)
		presicion = 5;
	else if (size >= 1000.0)
		presicion = 6;

	return presicion;
}

std::string Utils::GetByteString(size_t size)
{
	std::string byteString = "byte";

	if (size > 1)
		byteString = "bytes";

	return  byteString;
}

bool Utils::AlowedValue(int m, int M, int N)
{
	bool isAlowedValue = true;
	const ULong MAXBytes = MaxSize();
	ULong totalBytes = static_cast <ULong> (m)* static_cast <ULong> (N);

	if (totalBytes > MAXBytes)
	{
		isAlowedValue = false;
		std::cout << "The maximum allowed size is " << MAXBytes << " 4 GB." << " You entered values that ecceeds the maximum. Please try again." << std::endl;
	}

	return isAlowedValue;
}

void Utils::ShowInfo(std::string filename, std::string sizeStr)
{
	std::cout << "Current File Size: " << GetFormatFileSize(filename) << std::endl;
	std::cout << "Amount of data which it stores: " << sizeStr << std::endl;
}

void Utils::WelcomeScreen(void)
{
	std::cout << "\tElastic File Program" << std::endl;
	std::cout << "The program scenario is:" << std::endl << std::endl;
	std::cout << "Step 1: create a new file with N records, each having a length of m, written consequently, as follows [m][m][m]...[m]. The records are random alphabetical strings (a-zA-Z)." << std::endl << std::endl;
	std::cout << "Step 2: insert another N records of length of M bytes each in between the records from the first pass, as follows: [m][M][m][M][m][M]...[m][M]. The records must again be random alphabetical strings (a-zA-Z)" << std::endl << std::endl;
	std::cout << "Step 3: to read every 10th record from the file and output the maximum string (alphabetical order)" << std::endl << std::endl;
	std::cout << "Step 4: to delete every even pair [m][M] from the file, i.e [m][M][m][M][m][M][m][M]..." << std::endl << std::endl;

	system("pause");
}

std::string Utils::RandomString(int len)
{
	std::string alphabetStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string randomStr;

	for (int i = 0; i < len; ++i)
		randomStr += alphabetStr[rand() % 52];

	return randomStr;
}
