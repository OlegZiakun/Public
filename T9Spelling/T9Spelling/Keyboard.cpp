/*
   Copyright (C) Oleg Ziakun
*/

#include "Keyboard.h"
#include "Utils.h"
#include <iostream>

Keyboard::Keyboard(void)
{
	init();
}

Keyboard::~Keyboard(void)
{
	for(keyboard::const_iterator it = keyboardMap.begin(); it != keyboardMap.end(); ++it) 
		delete (*it).second;		  

	keyboardMap.clear();
}

void Keyboard::init(void)
{
	std::string alphaString = "abcdefghijklmnopqrstuvwxyz";
	int posCount;

	keyboardMap[' '] = allocateKey(0, 1);

	for(size_t i = 0, num = 2; i < alphaString.length();)
	{	
		(num == 7 || num == 9) ? posCount = 4 : posCount = 3;

		for(int pos = 1; pos <= posCount; ++pos)
			keyboardMap[alphaString[i++]] = allocateKey(num, pos);

		++num;
	}	
}

std::string Keyboard::translate(const std::string &str)
{
	std::string outputString;
	Utils utils;

	for(size_t i = 0; i < str.length(); ++i)
	{
		if(i > 0)
			if(keyboardMap[str[i - 1]]->num == keyboardMap[str[i]]->num) outputString += " ";

		for(int j = 0; j < keyboardMap[str[i]]->pos; ++j)			
			outputString += utils.intToStr(keyboardMap[str[i]]->num);		
	}

	return outputString;
}

key *Keyboard::allocateKey(int num, int pos)
{
	key *keyInfo;

	try 
	{ 
		keyInfo = new key(num, pos);
	}
	catch(std::bad_alloc&) 
	{ 
		Utils().criticalErrorMsg("Bad memory allocation"); 
	}

	return keyInfo;
}