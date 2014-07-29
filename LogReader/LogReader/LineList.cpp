/*
   Copyright (C) Oleg Ziakun
*/

#include "stdafx.h"
#include "LineList.h"
#include "Utils.h"

LineList::LineList() :
header(NULL)
{
}

LineList::~LineList()
{
}

void LineList::PushBack(const char *pStr)
{
	current = Utils::allocate<LineList>();

	if (header == NULL)
	{
		header = current;
		header->next = NULL;
		strcpy_s(header->str, sizeof(header->str), pStr);
	}
	else
	{
		previous->next = current;
		current->next = NULL;
		strcpy_s(current->str, sizeof(current->str), pStr);
	}

	previous = current;
};

void LineList::Take(char *pStr)
{
	if (header == NULL)
	{
		pStr[0] = 0;
		return;
	}

	strcpy_s(pStr, sizeof(header->str), header->str);

	LineList *tmp = header;

	header = header->next;
	delete tmp;
};

void LineList::Clear(void)
{
	current = header;

	LineList *tmp;

	while (current)
	{
		tmp = current->next;
		delete current;
		current = tmp;
	}
};
