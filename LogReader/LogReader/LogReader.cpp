/*
   Copyright (C) Oleg Ziakun
*/

#include "StdAfx.h"
#include "LogReader.h"
#include "Utils.h"

CLogReader::CLogReader(void) :
headToken(NULL),
justWord(false),
justWildcards(true),
summarizedStr(NULL),
lexema(NULL),
seps(NULL),
tmpBuf(NULL),
endOfStr(false),
maxHeadCount(-1)
{
}

CLogReader::~CLogReader(void)
{
	ClearTokens();
	lineList.Clear();
	ClearMembers();
}

bool CLogReader::Open(const char *fileName)
{
	file.open(fileName);
	return file.is_open();
}

void CLogReader::Close(void)
{
	file.close();
}

bool CLogReader::SetFilter(const char *filter)
{
	currentFilter = filter;

	const int sepsSize = strlen(SEPARATORS) + 1;

	seps = Utils::allocate<char>(sepsSize);
	strcpy_s(seps, sepsSize, SEPARATORS);

	return ParseFilter();
}

bool CLogReader::GetNextLine(char *buf, const int bufsize)
{
	if (bufsize < minSize)
	{
		std::cout << "Buffer size too small. Please increase it to " << minSize << " Thank you.\n";
		return false;
	}

	if (!summarizedStr)
	{
		summarizedStr = Utils::allocate<char>(bufsize);
		lexema = Utils::allocate<char>(bufsize);
		tmpBuf = Utils::allocate<char>(bufsize);
	}

	if (!justWord && !justWildcards)
	{
		lineList.Take(buf);

		if (buf[0] != 0)
			return true;
	}

	if (file.good())
	{
		while (true)
		{
			file.getline(lexema, bufsize);

			if (justWord || justWildcards)
				GetFilterLine(lexema, buf, bufsize);
			else
			{
				endOfStr = false;

				while (!endOfStr)
				{
					GetFilterLine(lexema, tmpBuf, bufsize);

					if (strlen(tmpBuf) > 0)
						lineList.PushBack(tmpBuf);
				}

				lineList.Take(buf);
			}

			if (buf[0] != 0 || file.eof())
				break;
		}
	}
	else
		return false;

	if (buf[0] == 0)
		return false;

	return true;
}

void CLogReader::GetFilterLine(char *lexema, char *buf, const int bufsize)
{
	if (justWord)
	{
		SetJustWord(lexema, buf, bufsize);
		return;
	}

	if (justWildcards)
	{
		SetJustWildcards(lexema, buf, bufsize);
		return;
	}

	const char *phrase = NULL;

	buf[0] = 0;
	phrase = strstr(lexema, headToken->str);

	if (phrase != NULL)
	{
		if (!GetHeadChunk(lexema, phrase, buf, bufsize))
			FAILED;
	}
	else
	{
		endOfStr = true;
		FAILED;
	}

	currentToken = headToken;

	while (currentToken)
	{
		if (currentToken->next)
		{
			ReverseTrancate(lexema, StrPos(lexema, currentToken->str) + strlen(currentToken->str));

			if (lexema != NULL)
			{
				if (!GetNextChunk(lexema, currentToken, buf, bufsize))
					FAILED;
			}
			else
				FAILED;
		}
		else
		{
			if (!GetTailChunk(lexema, currentToken, buf, bufsize))
				FAILED;
		}

		currentToken = currentToken->next;
	}
}

bool CLogReader::GetHeadChunk(char *lexema, const char *phrase, char *buf, const int bufsize)
{
	CheckSize(lexema, bufsize);

	const int count = StrPos(lexema, headToken->str);
	int i, j = 0;

	if (headSymbolCount == UNLIMITED)
	{
		i = 0;
		summarizedStr[count] = 0;
	}
	else
	{
		i = count - headSymbolCount;

		if (maxHeadCount < count)
			maxHeadCount = count;

		summarizedStr[headSymbolCount] = 0;
	}

	if (headSymbolCount >maxHeadCount)
	{
		endOfStr = true;
		return false;
	}

	if (i == count && headSymbolCount == UNLIMITED)
	{
		endOfStr = true;
		return false;
	}

	for (i; i < count; ++i, ++j)
		summarizedStr[j] = lexema[i];

	int length = strlen(summarizedStr);

	strcat_s(summarizedStr, bufsize, phrase);
	summarizedStr[strlen(headToken->str) + length] = 0;
	strcpy_s(buf, bufsize, summarizedStr);

	return true;
}

bool CLogReader::GetNextChunk(char *lexema, const Token *token, char *buf, const int bufsize)
{
	CheckSize(lexema, bufsize);

	int i, j = 0;
	bool everythingIsFine = true;
	const int count = StrPos(lexema, token->next->str);

	if (count == -1)
		return false;

	if (token->count == UNLIMITED)
	{
		i = 0;
		summarizedStr[count] = 0;
	}
	else
	{
		i = count - token->count;
		summarizedStr[token->count] = 0;
	}

	if (i == 0)
	{
		for (i; i < count; ++i, ++j)
			summarizedStr[j] = lexema[i];

		int length = strlen(summarizedStr);

		strcat_s(summarizedStr, bufsize, strstr(lexema, token->next->str));

		summarizedStr[strlen(token->next->str) + length] = 0;
		strcat_s(buf, bufsize, summarizedStr);
	}
	else
		everythingIsFine = false;

	return everythingIsFine;
}

bool CLogReader::GetTailChunk(char *lexema, const Token *token, char *buf, const int bufsize)
{
	CheckSize(lexema, bufsize);

	const char *tailPhrase = strstr(lexema, token->str);
	int count = strlen(tailPhrase);
	int i = strlen(token->str), j = 0;
	int index = count - i;

	if (tailSymbolCount == UNLIMITED)
		summarizedStr[index] = 0;
	else
	{
		count = i + tailSymbolCount;
		summarizedStr[tailSymbolCount] = 0;
	}

	if (index > tailSymbolCount || tailSymbolCount == UNLIMITED)
	{
		for (i; i < count; ++i, ++j)
			summarizedStr[j] = tailPhrase[i];

		strcat_s(buf, bufsize, summarizedStr);
	}
	else if (index == tailSymbolCount)
		return true;
	else
		return false;

	endOfStr = true;

	return true;
}

void CLogReader::ReverseTrancate(char *str, int start)
{
	const int size = strlen(str) + 1;
	char *tmpStr = Utils::allocate<char>(size);

	strcpy_s(tmpStr, size, str);

	for (int i = start, j = 0; i < size; ++i, ++j)
		str[j] = tmpStr[i];

	int trancateSize = size - start;

	if (trancateSize < 0)
		trancateSize = 0;

	str[trancateSize] = 0;

	delete[] tmpStr;
}

bool CLogReader::ParseFilter(void)
{
	if (currentFilter == NULL || !strcmp(currentFilter, ""))
	{
		std::cout << "Filter line is empty. Please enter a filter.\n";
		return false;
	}

	if (strcspn(currentFilter, seps) == strlen(currentFilter))
	{
		justWord = true;
		return true;
	}

	CheckJustWildcards();

	if (justWildcards)
		return true;

	const int minFilterLength = minSize / 4;

	if (strlen(currentFilter) > minFilterLength)
	{
		std::cout << "Filter is too long.\n";
		return false;
	}

	char *token, *nextToken;
	const int size = strlen(currentFilter) + 1;
	char *analyzingFilter = Utils::allocate<char>(size);

	headSymbolCount = GetHeadSymbolCount(currentFilter);
	tailSymbolCount = GetTailSymbolCount(currentFilter);

	strcpy_s(analyzingFilter, size, currentFilter);
	token = strtok_s(analyzingFilter, seps, &nextToken);

	while ((token != NULL))
	{
		int count = GetHeadSymbolCount(nextToken);

		if (IsAsteriskSeparator(token, nextToken))
			count = UNLIMITED;

		PushBackToken(token, count);
		token = strtok_s(NULL, seps, &nextToken);
	}

	delete[] analyzingFilter;

	return true;
}

void CLogReader::PushBackToken(const char *str, int count)
{
	currentToken = Utils::allocate<Token>();

	if (headToken == NULL)
	{
		headToken = currentToken;
		headToken->next = NULL;

		strcpy_s(headToken->str, sizeof(headToken->str), str);

		if (count == UNLIMITED)
			headToken->count = count;
		else
			headToken->count = count + 1;
	}
	else
	{
		previousToken->next = currentToken;
		currentToken->next = NULL;

		strcpy_s(currentToken->str, sizeof(currentToken->str), str);

		if (count == UNLIMITED)
			currentToken->count = count;
		else
			currentToken->count = count + 1;
	}

	previousToken = currentToken;
}

void CLogReader::ClearTokens(void)
{
	Token* tmp;
	currentToken = headToken;

	while (currentToken)
	{
		tmp = currentToken->next;
		delete currentToken;
		currentToken = tmp;
	}
}

int CLogReader::StrPos(const char *haystack, const char *needle)
{
	const char *p = strstr(haystack, needle);

	if (p)
		return p - haystack;

	return -1;
}

int CLogReader::GetHeadSymbolCount(const char *str)
{
	int symbolCount = 0;

	if (str[0] != seps[0] && str[0] != seps[1])
		return symbolCount;

	for (size_t i = 0; i < strlen(str); ++i)
	{
		if (str[i] == seps[0])
		{
			symbolCount = UNLIMITED;
			break;
		}
		else if (str[i] == seps[1])
			++symbolCount;
		else if (str[0] != seps[0] || str[0] != seps[1])
			return symbolCount;
	}

	return symbolCount;
}

int CLogReader::GetTailSymbolCount(const char *str)
{
	int symbolCount = 0;
	const int size = strlen(str) - 1;

	for (size_t i = size; i >= 0; --i)
	{
		if (str[i] == seps[0])
		{
			symbolCount = UNLIMITED;
			break;
		}
		else if (str[i] == seps[1])
			++symbolCount;
		else if (str[size] != seps[0] || str[size] != seps[1])
			return symbolCount;
	}

	return symbolCount;
}

bool CLogReader::IsAsteriskSeparator(const char *token, const char *nextToken)
{
	bool is = false;
	const int size = (strlen(currentFilter) - strlen(nextToken));
	const int filterSize = strlen(currentFilter) + 1;
	char *checkToken = Utils::allocate<char>(filterSize);
	char *checkFilterToken = Utils::allocate<char>(filterSize);

	strcpy_s(checkFilterToken, filterSize, currentFilter);
	strcpy_s(checkToken, filterSize, token);
	strcat_s(checkToken, filterSize, "*");

	checkFilterToken[size] = 0;

	if (strstr(checkFilterToken, checkToken) != NULL)
		is = true;

	delete[] checkToken;
	delete[] checkFilterToken;

	return is;
}

void CLogReader::CheckJustWildcards(void)
{
	wildcardsCount = 0;

	for (size_t i = 0; i < strlen(currentFilter); ++i)
	{
		if (currentFilter[i] == seps[0]) wildcardsCount = UNLIMITED;
		else if (currentFilter[i] == seps[1])
		{
			if (wildcardsCount > UNLIMITED)
				++wildcardsCount;
		}
		else
		{
			justWildcards = false;
			return;
		}
	}
}

void CLogReader::SetJustWord(char *lexema, char *buf, const int bufsize)
{
	const char *justPhrase;
	justPhrase = strstr(lexema, currentFilter);

	if (justPhrase == NULL)
		FAILED;

	strcpy_s(buf, bufsize, justPhrase);
	buf[strlen(currentFilter)] = 0;
}

void CLogReader::SetJustWildcards(char *lexema, char *buf, const int bufsize)
{
	if (wildcardsCount != UNLIMITED)
	{
		const int length = strlen(lexema);

		if (wildcardsCount <= length)
		{
			char *tmp = Utils::allocate<char>(length + 1);

			strcpy_s(tmp, bufsize, lexema);

			for (int i = 0; i < wildcardsCount; ++i)
				lexema[i] = tmp[i];

			lexema[wildcardsCount] = 0;
			delete[]  tmp;
		}
		else
			FAILED;
	}

	strcpy_s(buf, bufsize, lexema);
}

void CLogReader::ClearMembers()
{
	delete[] summarizedStr;
	delete[] lexema;
	delete[] seps;
	delete[] tmpBuf;
}

