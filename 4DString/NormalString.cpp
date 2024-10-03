///////////////////////////////////////////////////////////////////////////////
//
// NormalString.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalString.h"
#include "StringRecycleBin.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCD")
//Recycle bin.
static CStringRecycleBin stringBin;

///////////////////////////////////////////////////////////////////////////////
//
// CNormalString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString::CNormalString(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CNormalString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString::CNormalString(const _STRING string)
	: C4DString(string)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CNormalString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString::CNormalString(const CNormalString& string)
	: C4DString(string)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ~CNormalString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString::~CNormalString(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

CNormalString& CNormalString::operator = (const CNormalString& string)
{
	//Equal.
	C4DString::operator = (string);
	//Return result.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CNormalString::operator == (const CNormalString& string) const
{
	//Return result.
	return C4DString::operator == (string);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CNormalString::operator != (const CNormalString& string) const
{
	//Return result.
	return C4DString::operator != (string);
}

///////////////////////////////////////////////////////////////////////////////
//
// Recycle
//
///////////////////////////////////////////////////////////////////////////////

void CNormalString::recycle()
{
	//Recycle string.
	stringBin.recycle(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Create
//
///////////////////////////////////////////////////////////////////////////////

CNormalString* CNormalString::create()
{
	//Return result.
	return (CNormalString *)stringBin.create();
}

///////////////////////////////////////////////////////////////////////////////
//
// MallocString
//
///////////////////////////////////////////////////////////////////////////////

CNormalString* CNormalString::create(_STRING string)
{
	//Get string.
	CNormalString* newString = create();
#ifdef _DEBUG
	assert(newString != _NULL);
#endif
	//Append.
	newString->append(string);
	//Return result.
	return newString;
}
