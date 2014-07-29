/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"
#include "Token.h"
#include "LineList.h"

class CLogReader
{
public:
	CLogReader(void);
	~CLogReader(void);

public:
	bool Open(const char *fileName);
	void Close(void);
	bool SetFilter(const char *filter);
	bool GetNextLine(char *buf, const int bufsize);

private:
	bool ParseFilter(void);
	void GetFilterLine(char *lexema, char *buf, const int bufsize);
	void PushBackToken(const char *str, int count);
	void ClearTokens(void);
	int  StrPos(const char *haystack, const char *needle);
	bool GetHeadChunk(char *lexema, const char *phrase, char *buf, const int bufsize);
	bool GetNextChunk(char *lexema, const Token *token, char *buf, const int bufsize);
	bool GetTailChunk(char *lexema, const Token *token, char *buf, const int bufsize);
	int  GetHeadSymbolCount(const char *str);
	int  GetTailSymbolCount(const char *str);
	bool IsAsteriskSeparator(const char *token, const char *nextToken);
	void ReverseTrancate(char *str, int start);
	void CheckJustWildcards(void);
	void SetJustWord(char *lexema, char *buf, const int bufsize);
	void SetJustWildcards(char *lexema, char *buf, const int bufsize);
	void ClearMembers();
	inline void CheckSize(char *lexema, const unsigned int bufsize) { if (strlen(lexema) > bufsize) lexema[bufsize] = 0; };

private:	
	Token *headToken;
	Token *currentToken;
	Token *previousToken;
	LineList lineList;
    std::ifstream file;
	bool justWord;
	bool justWildcards;
	bool endOfStr;
	const char *currentFilter;
	int headSymbolCount;
	int tailSymbolCount;
	int wildcardsCount;
	int maxHeadCount;
	char *summarizedStr;
	char *lexema;
	char *seps;
	char *tmpBuf;
};
