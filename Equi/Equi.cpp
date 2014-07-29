/*
   Copyright (C) Oleg Ziakun
*/

// http://blog.codility.com/2011/03/solutions-for-task-equi.html

#include "stdafx.h"
#include "EquiSolution.h"

int _tmain(int argc, _TCHAR* argv[])
{
	EquiSolution equiSolution;
	std::vector<int> vector;

	if (equiSolution.prepare(vector, 7, -7, 1, 5, 2, -4, 3, 0))
		std::cout << equiSolution.run(vector) << std::endl;

	system("pause");

	return 0;
}

