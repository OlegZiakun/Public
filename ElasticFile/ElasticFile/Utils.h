/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"

class Utils
{
public:
	Utils();
	~Utils();

public:
	template <typename T> static T* allocate(const size_t size = 0)
	{
		T *allocatedPtr;

		try
		{
			if (size > 0)
				allocatedPtr = new T[size];
			else
				allocatedPtr = new T;

		}
		catch (std::bad_alloc&)
		{
			std::cout << "Bad memory allocation";
			exit(EXIT_FAILURE);
		}

		return allocatedPtr;
	}

public:
	void ShowPerformanceTime(std::string msg);
	void GetInput(std::string msg, int &i);
	void RandomizeStrings(int len, int count);
	size_t GetFileSize(std::string filename);
	std::string GetFormatFileSize(std::string filename);
	int GetPresicion(float size);
	std::string GetByteString(size_t size);
	bool AlowedValue(int m, int M, int N);
	void ShowInfo(std::string filename, std::string sizeStr);
	void WelcomeScreen(void);
	std::string RandomString(int len);

public:
	static void ErrorFile(std::string msg) { std::cout << "error " << msg << " file" << std::endl; exit(EXIT_FAILURE); }

public:
	inline const ULong MaxSize(void) const { return 4294967295; } // 4 GB
	inline PBYTE GetRandomString(void) const { return randomStrings.at(rand() % (randomStrings.size() - 1)); }
	inline void StartOfPerformance(void) { start = clock(); }
	inline void EndOfPerformance(void) { end = clock(); }
	inline float GetPerformanceTime(void) { clock_t performanceTime = end - start; return (static_cast<float> (performanceTime)) / CLOCKS_PER_SEC; }

private:
	clock_t start;
	clock_t end;
	std::vector<PBYTE> randomStrings;
	std::string maxString;
};

