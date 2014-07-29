/*
   Copyright (C) Oleg Ziakun
*/

#pragma once

#include "stdafx.h"

class Operations
{
public:
	enum OpenMode { Append, Create, Open, Read };
	enum CursorMoveMode { Begin = SEEK_SET, Current = SEEK_CUR, End = SEEK_END };
	enum Operation { Insert, Delete };

	Operations(Operation o) : operation(o) {}
	~Operations() {}

	friend class FileIO;
	inline void setOperation(ULong pos, PBYTE buffer, ULong size) { this->pos = pos; this->buffer = buffer; this->size = size; }

private:
	Operation operation;
	PBYTE buffer;
	ULong pos;
	ULong size;
};

