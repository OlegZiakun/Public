/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"

class EquiSolution
{
public:
	EquiSolution();
	~EquiSolution();

public:
	bool prepare(std::vector<int> &vector, int count, int first, ...);
	int run(const std::vector <int> &a);
	
private:
	int k, l, n, s = 0;
};

