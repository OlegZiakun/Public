/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

class Utils
{
public:
	Utils(void);
	~Utils(void);

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
			criticalError("Bad memory allocation");
		}

		return allocatedPtr;
	}

	static void criticalError(const std::string &msg)
	{
		std::cout << std::endl << msg;
		exit(EXIT_FAILURE);
	}
};



