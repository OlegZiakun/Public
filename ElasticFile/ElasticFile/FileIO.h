/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"
#include "Utils.h"
#include "Operations.h"

class FileIO
{
public:
	FileIO(void);
	~FileIO(void);

public:
	FileHandle FileOpen(std::string fileName, Operations::OpenMode mode);
	ULong FileGetCursor(FileHandle file);
	ULong FileRead(FileHandle file, PBYTE buf, size_t size);
	bool FileSetCursor(FileHandle file, ULong offset, Operations::CursorMoveMode mode);
	ULong FileWrite(FileHandle file, PBYTE buf, size_t size, bool overwrite);
	bool FileTruncate(FileHandle file, ULong cutSize);
	bool FileClose(FileHandle file);
	void setOperation(Operations operations);
	void SetFileName(std::string fileName);
	void Flush(FileHandle file, bool rewritable = true, int defaultOffset = 0);
	void SetMaxString(FileHandle file, ULong pos, int size);

public:
	inline void InitMaxString(void) { maxString.clear(); }
	inline std::string GetMaxString(void) const { return maxString; }
	inline std::vector<Operations> GetOperations() const { return operations; }

private:
	void SetMode(void);
	void Ins(FileHandle fileOrigin, FileHandle fileTmp, std::vector<Operations>::const_iterator &it, ULong &offset);
	void Del(FileHandle fileOrigin, FileHandle FileTmp, std::vector<Operations>::const_iterator &it);
	bool RewriteFile(std::string fileToRewrite, std::string fileToBeOrigin);
	void WriteChunk(FileHandle fileOrigin, FileHandle fileTmp, PBYTE buffer, ULong bufSize, ULong numOfIteraton, ULong numOfRemainingBytes);
	void WriteChunkToTheEnd(FileHandle fileOrigin, FileHandle fileTmp, ULong numOfBytesToTheEnd, PBYTE Buffer, ULong bufSize, ULong numOfIteraton, ULong numOfRemainingBytes);

private:
	std::map<Operations::OpenMode, std::string> modeMap;
	std::list<std::string> stringList;
	std::string fileName;
	std::vector<Operations> operations;
	std::string maxString;
};