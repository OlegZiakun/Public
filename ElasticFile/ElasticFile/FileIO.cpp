/*
   Copyright (C) Oleg Ziakun
*/

#include "FileIO.h"
#include <time.h> 

using namespace std;

FileIO::FileIO(void)
{
	SetMode();
}

FileIO::~FileIO(void)
{
	operations.clear();
}

void FileIO::Flush(FileHandle file, bool rewritable, int defaultOffset)
{
	if (operations.empty())
		return;

	FILE *tmpFile;
	string tmpFileName = "tmp.bin";

	tmpFile = FileOpen(tmpFileName, Operations::Append);

	if (tmpFile == NULL)
	{
		cout << "error creating file" << endl;
		return;
	}

	ULong offset = defaultOffset;
	bool rewrite = true;

	for (vector<Operations>::const_iterator it = operations.begin(); it != operations.end(); ++it)
	{
		switch ((*it).operation)
		{
		case Operations::Insert:
			Ins(file, tmpFile, it, offset);
			break;
		case Operations::Delete:
			Del(file, tmpFile, it);
			break;
		}
	}

	if (!FileClose(tmpFile))
		Utils::ErrorFile("closing temporary");

	if (!FileClose(file))
		Utils::ErrorFile("closing");

	operations.clear();

	if (rewritable)
	{
		if (rewrite)
		{
			if (!RewriteFile(fileName, tmpFileName))
				Utils::ErrorFile("rewriting");
		}
	}
}

bool FileIO::RewriteFile(string fileToRewrite, string fileToBeOrigin)
{
	bool isItOk[2] = { false, false };

	if (!remove(fileToRewrite.c_str()))
		isItOk[0] = true;

	if (!rename(fileToBeOrigin.c_str(), fileToRewrite.c_str()))
		isItOk[1] = true;

	return isItOk[0] & isItOk[1];
}

void FileIO::Ins(FileHandle fileOrigin, FileHandle fileTmp, vector<Operations>::const_iterator &it, ULong &offset)
{
	PBYTE buffer;
	int bufferSize = static_cast <unsigned int> ((*it).pos - offset);

	buffer = Utils::allocate<BYTE>(bufferSize);

	FileSetCursor(fileOrigin, offset, Operations::Begin);
	FileRead(fileOrigin, buffer, bufferSize);
	FileWrite(fileTmp, buffer, bufferSize, true);
	FileSetCursor(fileOrigin, (*it).pos, Operations::Begin);
	FileWrite(fileTmp, (*it).buffer, (*it).size, true);

	offset += (*it).pos - offset;

	delete[] buffer;
}

void FileIO::Del(FileHandle fileOrigin, FileHandle fileTmp, vector<Operations>::const_iterator &it)
{
	PBYTE buffer;

	buffer = Utils::allocate<BYTE>(static_cast<unsigned int> ((*it).size));

	FileSetCursor(fileOrigin, (*it).pos + (*it).size, Operations::Begin);
	FileRead(fileOrigin, buffer, (*it).size);
	FileWrite(fileTmp, buffer, (*it).size, true);

	delete[] buffer;
}

FileHandle FileIO::FileOpen(string fileName, Operations::OpenMode mode)
{
	FileHandle fileHandle;

	fopen_s(&fileHandle, fileName.c_str(), modeMap.find(mode)->second.c_str());
	return fileHandle;
}

bool FileIO::FileTruncate(FileHandle file, ULong cutSize)
{
	PBYTE buffer;
	FILE *tmpFile;
	ULong pos = FileGetCursor(file);
	string tmpFileName = "tmpTruncate.bin";
	ULong bufSize = 1024 * 1024;
	bool isItGood = true;

	tmpFile = FileOpen(tmpFileName, Operations::Create);

	if (tmpFile == NULL)
	{
		cout << "error creating file" << endl;
		return false;
	}

	buffer = Utils::allocate<BYTE>(bufSize);

	if (pos <= bufSize)
	{
		FileRead(file, buffer, pos);
		FileWrite(tmpFile, buffer, pos, true);
	}
	else
		WriteChunk(file, tmpFile, buffer, bufSize, pos / bufSize, pos % bufSize);

	ULong newPos = pos + cutSize;
	ULong numOfBytesToTheEnd = Utils().GetFileSize(fileName) - newPos;

	FileSetCursor(file, newPos, Operations::Begin);
	WriteChunkToTheEnd(file, tmpFile, numOfBytesToTheEnd, buffer, bufSize, numOfBytesToTheEnd / bufSize, numOfBytesToTheEnd % bufSize);

	delete[] buffer;

	if (!FileClose(tmpFile))
	{
		cout << "error closing temporary file" << endl;
		isItGood = false;
	}

	if (!FileClose(file))
	{
		cout << "error closing file" << endl;
		isItGood = false;
	}

	if (!RewriteFile(fileName, tmpFileName))
	{
		cout << "error rewriting file" << endl;
		isItGood = false;
	}

	return isItGood;
}

void FileIO::WriteChunk(FileHandle fileOrigin, FileHandle fileTmp, PBYTE buffer, ULong bufSize, ULong numOfIteraton, ULong numOfRemainingBytes)
{
	for (ULong i = 0; i < numOfIteraton; ++i)
	{
		FileRead(fileOrigin, buffer, bufSize);
		FileWrite(fileTmp, buffer, bufSize, true);
	}

	FileRead(fileOrigin, buffer, numOfRemainingBytes);
	FileWrite(fileTmp, buffer, numOfRemainingBytes, true);
}

// no required another logic

ULong FileIO::FileGetCursor(FileHandle file)
{
	return ftell(file);
}

ULong FileIO::FileRead(FileHandle file, PBYTE buf, size_t size)
{
	return fread(buf, size, 1, file);
}

void FileIO::SetFileName(string fileName)
{
	this->fileName = fileName;
}

ULong FileIO::FileWrite(FileHandle file, PBYTE buf, size_t size, bool overwrite)
{
	ULong numOfBytes = 0;

	if (overwrite)
		numOfBytes = fwrite(buf, size, 1, file);
	else
	{
		PBYTE buffer;
		FILE *tmpFile;
		ULong bufSize = 1024 * 1024;
		ULong pos = FileGetCursor(file);
		string tmpFileName = "tmpWrite.bin";
		tmpFile = FileOpen(tmpFileName, Operations::Create);

		if (tmpFile == NULL)
			Utils::ErrorFile("creating");

		buffer = Utils::allocate<BYTE>(bufSize);

		if (pos <= bufSize)
		{
			FileSetCursor(file, 0, Operations::Begin);
			FileRead(file, buffer, pos);
			FileWrite(tmpFile, buffer, pos, true);
		}
		else
			WriteChunk(file, tmpFile, buffer, bufSize, pos / bufSize, pos % bufSize);

		FileWrite(tmpFile, buf, size, true);
		FileSetCursor(file, pos, Operations::Begin);

		ULong numOfBytesToTheEnd = Utils().GetFileSize(fileName) - pos;
		WriteChunkToTheEnd(file, tmpFile, numOfBytesToTheEnd, buffer, bufSize, numOfBytesToTheEnd / bufSize, numOfBytesToTheEnd % bufSize);

		delete[] buffer;

		if (!FileClose(tmpFile))
			Utils::ErrorFile("closing temporary");

		if (!FileClose(file))
			Utils::ErrorFile("closing temporary");

		if (!RewriteFile(fileName, tmpFileName))
			Utils::ErrorFile("rewriting");

		file = FileOpen(fileName, Operations::Append);

		if (file == NULL)
			Utils::ErrorFile("creating");
	}

	return numOfBytes;
}

void FileIO::WriteChunkToTheEnd(FileHandle fileOrigin, FileHandle fileTmp, ULong numOfBytesToTheEnd, PBYTE Buffer, ULong bufSize, ULong numOfIteraton, ULong numOfRemainingBytes)
{
	if (numOfBytesToTheEnd <= bufSize)
	{
		FileRead(fileOrigin, Buffer, numOfBytesToTheEnd);
		FileWrite(fileTmp, Buffer, numOfBytesToTheEnd, true);
	}
	else
		WriteChunk(fileOrigin, fileTmp, Buffer, bufSize, numOfBytesToTheEnd / bufSize, numOfBytesToTheEnd % bufSize);
}

bool FileIO::FileSetCursor(FileHandle file, ULong offset, Operations::CursorMoveMode mode)
{
	bool isItGood = true;

	if (_fseeki64(file, offset, mode) != 0)
		isItGood = false;

	return isItGood;
}

bool FileIO::FileClose(FileHandle file)
{
	bool isItGood = true;

	if (fclose(file) != 0)
		isItGood = false;

	return isItGood;
}

void FileIO::SetMode(void)
{
	modeMap[Operations::Append] = "ab+";
	modeMap[Operations::Create] = "wb+";
	modeMap[Operations::Open] = "b";
	modeMap[Operations::Read] = "rb";
}

void FileIO::setOperation(Operations operations)
{
	this->operations.push_back(operations);
}

void FileIO::SetMaxString(FileHandle file, ULong pos, int size)
{
	PBYTE buffer = Utils::allocate<BYTE>(size);

	FileSetCursor(file, pos, Operations::Begin);
	FileRead(file, buffer, size);

	string str(buffer, buffer + size);

	if (maxString.compare(str) < 0)
		maxString = str;

	delete[] buffer;
}
