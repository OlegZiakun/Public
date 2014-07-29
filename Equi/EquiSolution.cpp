/*
   Copyright (C) Oleg Ziakun
*/

#include "stdafx.h"
#include <stdarg.h>
#include "EquiSolution.h"

EquiSolution::EquiSolution()
{
}

EquiSolution::~EquiSolution()
{
}

bool EquiSolution::prepare(std::vector<int> &vector, int count, int first ...)
{
	if (count < 1)
		return false;

	va_list argPtr;
	va_start(argPtr, first);

	vector.push_back(first);

	while (--count)
		vector.push_back(va_arg(argPtr, int));

	va_end(argPtr);

	return true;
}

int EquiSolution::run(const std::vector<int> &a)
{
	n = a.size(); k = n;
	while (k--)
	{
		l = n, s = 0;
		while (l--) { k&&k == l ? --l : 0; l > k || k == n - 1 ? s += a[l] : s -= a[l]; }
		k == n - 1 ? s -= a[k] : 0;
		if (!s)
			return k;
	}
	return s;
}