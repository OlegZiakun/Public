/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include <map>

struct key
{
  key(int n, int p) :
	  num(n), pos(p) {};
  
  int num;
  int pos;
};

typedef std::map<char, key*> keyboard;

class Keyboard
{
public:
	Keyboard(void);
	~Keyboard(void);

public:
	std::string translate(const std::string &str);

private:
	void init(void);
	key *allocateKey(int num, int pos);

private:
	keyboard keyboardMap;
};

