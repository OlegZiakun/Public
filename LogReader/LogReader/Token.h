/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

struct Token 
{
	Token() : count(0) {}

	int count;
	char str[64];
	Token *next;
};

