/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"

class LineList
{
public:
	LineList();
	~LineList();

public:	
	void PushBack(const char *pStr);
	void Take(char *pStr);
	void Clear(void);

private:
	LineList *header;
	LineList *current;
	LineList *previous;
    LineList *next;
	char str[minSize];
};

