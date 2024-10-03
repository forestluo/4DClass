///////////////////////////////////////////////////////////////////////////////
//
// 4DPrint.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DPrint.h"

////////////////////////////////////////////////////////////////////////////////
//
// Special including files.
//
// Including the files for the specifal operation system.
//
// These including files are used for the specifal operation system.
//
////////////////////////////////////////////////////////////////////////////////

//ANSI C standard.
#include <stdarg.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//
// Defination for end of a line.
//
// Different system has different defination for end of a line.
//
////////////////////////////////////////////////////////////////////////////////

#define END_OF_LINE												L"\r\n"

///////////////////////////////////////////////////////////////////////////////
//
// C4DPrint
//
///////////////////////////////////////////////////////////////////////////////

C4DPrint::C4DPrint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ~C4DPrint
//
///////////////////////////////////////////////////////////////////////////////

C4DPrint::~C4DPrint(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// New line.
//
///////////////////////////////////////////////////////////////////////////////

const _STRING C4DPrint::lineSeprator()
{
	//Return result.
	return END_OF_LINE;
}

///////////////////////////////////////////////////////////////////////////////
//
// New line.
//
///////////////////////////////////////////////////////////////////////////////

void C4DPrint::newLine(FILE* lpFile)
{
#ifdef _DEBUG
	assert(lpFile != NULL);
#endif
	//Print end of line.
	fwprintf(lpFile,END_OF_LINE);
}

///////////////////////////////////////////////////////////////////////////////
//
// Print.
//
///////////////////////////////////////////////////////////////////////////////

_INT32 C4DPrint::print(FILE* lpFile,_STRING lpstrFormat,...)
{
	//Size.
	_INT32 nSize = 0;
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpFile != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Print variable arguments.
	nSize = vfwprintf(lpFile,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);
	//Return size.	
	return nSize;
}

///////////////////////////////////////////////////////////////////////////////
//
// Print line.
//
///////////////////////////////////////////////////////////////////////////////

_INT32 C4DPrint::printLine(FILE* lpFile,_STRING lpstrFormat,...)
{
	//Size.
	_INT32 nSize = 0;
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpFile != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Print variable arguments.
	nSize = vfwprintf(lpFile,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Print end of line.
	fwprintf(lpFile,END_OF_LINE);
	//Return size.
	return nSize;
}

///////////////////////////////////////////////////////////////////////////////
//
// Format.
//
///////////////////////////////////////////////////////////////////////////////

_STRING C4DPrint::format(_STRING lpstrContent,_INT32 nLength,_STRING lpstrFormat,...)
{
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpstrContent != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Format variable arguments.
	vswprintf(lpstrContent,nLength,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Move pointer.
	lpstrContent += wcslen(lpstrContent);
	//Return pointer.
	return lpstrContent;
}

////////////////////////////////////////////////////////////////////////////////
//
// Format line.
//
////////////////////////////////////////////////////////////////////////////////

_STRING C4DPrint::formatLine(_STRING lpstrContent,_INT32 nLength,_STRING lpstrFormat,...)
{
	//Parameter list.
	va_list argp;

#ifdef _DEBUG
	assert(lpstrContent != NULL && lpstrFormat != NULL);
#endif

	//Initialize variable arguments.
	va_start(argp,lpstrFormat);
	//Format variable arguments.
	vswprintf(lpstrContent,nLength,lpstrFormat,argp);
	//Reset variable arguments.
	va_end(argp);

	//Format end of line.
	wcscat_s(lpstrContent,nLength,END_OF_LINE);

	//Move pointer.
	lpstrContent += wcslen(lpstrContent);
	//Return pointer.
	return lpstrContent;
}


////////////////////////////////////////////////////////////////////////////////
//
// Is end with new line.
//
////////////////////////////////////////////////////////////////////////////////

_BOOL C4DPrint::endWithsNewLine(_STRING lpstrContent)
{
#ifdef _DEBUG
	assert(lpstrContent != NULL);
#endif
	//Add pointer.
	lpstrContent += wcslen(lpstrContent) - sizeof(END_OF_LINE);

	//Check end with new line.
	if(wcsncmp(lpstrContent,END_OF_LINE,wcslen(END_OF_LINE)) == 0)
	{
		//Return true.
		return _TRUE;
	}
	//Return false.
	return _FALSE;
}

////////////////////////////////////////////////////////////////////////////////
//
// Clear end with new line.
//
////////////////////////////////////////////////////////////////////////////////

void C4DPrint::clearEndWithNewLine(_STRING lpstrContent)
{
	_STRING lpstrEnd;

#ifdef _DEBUG
	assert(lpstrContent != NULL);
#endif
	//Move to end.
	lpstrEnd = lpstrContent + wcslen(lpstrContent);
	//Check result.
	while(lpstrEnd > lpstrContent)
	{
		//Backward.
		lpstrEnd -= wcslen(END_OF_LINE);

		//Check end with new line.
		if(wcsncmp(lpstrEnd,END_OF_LINE,wcslen(END_OF_LINE)) != 0)
		{
			//Break.
			break;
		}

		//Set end of line.
		*lpstrEnd = L'\0';
	}
}
