///////////////////////////////////////////////////////////////////////////////
//
// 4DString.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "4DPrint.h"
#include "4DString.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
using namespace std;

#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAX_UNICODE_SIZE									4096
#define INSTANCE(a)											(*((wstring *)(a)))

#define _STRING_LENGTH										256
typedef _CHAR												_STATICSTRING[_STRING_LENGTH];

///////////////////////////////////////////////////////////////////////////////
//
// C4DString
//
///////////////////////////////////////////////////////////////////////////////

C4DString::C4DString(void)
{
	//Allocate.
	value = new wstring();
#ifdef _DEBUG
	assert(value != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DString
//
///////////////////////////////////////////////////////////////////////////////

C4DString::C4DString(const _STRING string)
{
#ifdef _DEBUG
	assert(string != _NULL);
#endif
	//Allocate.
	value = new wstring(string);
#ifdef _DEBUG
	assert(value != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DString
//
///////////////////////////////////////////////////////////////////////////////

C4DString::C4DString(const C4DString& string)
{
	//Allocate.
	value = new wstring();
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string.value != _NULL);
#endif
	//Set value.
	INSTANCE(value) = INSTANCE(string.value);
}

///////////////////////////////////////////////////////////////////////////////
//
// ~C4DString
//
///////////////////////////////////////////////////////////////////////////////

C4DString::~C4DString(void)
{
	//Check value.
	if(value != _NULL)
	{
		//Delete.
		delete (wstring *)value;
		//Clear value.
		value = (wstring *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

C4DString& C4DString::operator = (const C4DString& string)
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string.value != _NULL);
#endif
	//Set value.
	INSTANCE(value) = INSTANCE(string.value);
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DString::operator == (const C4DString& string) const
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string.value != _NULL);
#endif
	//Return result.
	return INSTANCE(value) == INSTANCE(string.value);
}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DString::operator != (const C4DString& string) const
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string.value != _NULL);
#endif
	//Return result.
	return INSTANCE(value) != INSTANCE(string.value);
}

///////////////////////////////////////////////////////////////////////////////
//
// Length
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER C4DString::length() const
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Return result.
	return INSTANCE(value).length();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCString
//
///////////////////////////////////////////////////////////////////////////////

const _STRING C4DString::getCString() const
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Return result.
	return (_STRING)INSTANCE(value).c_str();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetAnsiString
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER C4DString::getAnsiString(_BYTE* buffer,_INTEGER maxSize) const
{
	//Get length.
	_INTEGER wLength = length();
	//Default block.
	_BYTE block[MAX_UNICODE_SIZE];
	//Clear block.
	memset(block,0,MAX_UNICODE_SIZE * sizeof(_BYTE));

#ifdef _DEBUG
	assert(buffer != _NULL && 2 * wLength < MAX_UNICODE_SIZE);
#endif
	//Reset bytes.
	memset(buffer,0,maxSize * sizeof(_BYTE));
	//Copy bytes.
	memcpy(block,getCString(),wLength * sizeof(WCHAR));
	//Convert unicode to ANSI bytes.
	_INTEGER nNeeded = WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,(LPCWSTR)block,wLength,NULL,0,NULL,NULL);
	//Check needed length.
	if(nNeeded >= maxSize) return _FALSE;
	//Convert unicode to ANSI bytes.
	return WideCharToMultiByte(CP_ACP,WC_COMPOSITECHECK,(LPCWSTR)block,wLength,(LPSTR)buffer,nNeeded,NULL,NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// Equals
//
///////////////////////////////////////////////////////////////////////////////

_BOOL C4DString::equals(C4DString* string) const
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string != _NULL);
	assert(string->value != _NULL);
#endif
	//Return result.
	return INSTANCE(value) == INSTANCE(string->value);
}

///////////////////////////////////////////////////////////////////////////////
//
// Tab
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::tab()
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(L"\t");
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Skip
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::skip()
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(L" ");
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Line
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::line()
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(C4DPrint::lineSeprator());
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_BYTE byteValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%d",byteValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_SHORT shortValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%d",shortValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_INTEGER integerValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%d",integerValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_BOOL booleanValue)
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(booleanValue ? L"true" : L"false");
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_CHAR charValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%c",charValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_LONG longValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%u",longValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_FLOAT floatValue)
{
	//Format.
	_STATICSTRING format;
	//Clear format.
	memset(format,0,sizeof(_STATICSTRING));
	//Format.
	swprintf(format,sizeof(_STATICSTRING),L"%f",floatValue);

#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(format);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(_STRING stringValue)
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(stringValue != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(stringValue);
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// Append
//
///////////////////////////////////////////////////////////////////////////////

C4DString* C4DString::append(C4DString* string)
{
#ifdef _DEBUG
	assert(value != _NULL);
	assert(string != _NULL);
#endif
	//Append value.
	INSTANCE(value).append(string->getCString());
	//Return this.
	return this;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void C4DString::clearAll()
{
#ifdef _DEBUG
	assert(value != _NULL);
#endif
	//Return result.
	return INSTANCE(value).clear();
}

///////////////////////////////////////////////////////////////////////////////
//
// HashCode
//
///////////////////////////////////////////////////////////////////////////////

_LONG C4DString::hashCode(const _STRING string)
{
	//Hash code.
	_LONG hashCode = 0;

#ifdef _DEBUG
	assert(string != _NULL);
#endif

	//Do while.
	for(_UINT32 i = 0;i < wcslen(string);i ++)
	{
		//Get hash code.
		hashCode = (hashCode * 16777619) ^ string[i];
	}
	////////////////////////////////////////////////////
	//
	//Add the effect of length to the hash code.
	//
	//Get length.
	_UINT32 length = wcslen(string);
	//Do while.
	for(_UINT32 i = 0;i < sizeof(int);i ++)
	{
		//Add length as a byte.
		hashCode = (hashCode * 16777619) ^ ((length >> (8 * i)) & 0xff);
	}
	//
	////////////////////////////////////////////////////
	//Return result.
	return hashCode;
}
