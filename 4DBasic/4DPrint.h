///////////////////////////////////////////////////////////////////////////////
//
// 4DPrint.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_PRINT_H_
#define _4D_PRINT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DPrint
//
///////////////////////////////////////////////////////////////////////////////

class C4DPrint
{
public:
	C4DPrint(void);
	virtual ~C4DPrint(void);

public:

	/**
	 * Get line seprator.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Line seprator of current system.</p>
	 */
	static const _STRING lineSeprator();

public:

	/**
	 * New line.
	 *
	 * @param lpFile File pointer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void newLine(FILE* lpFile);

	/**
	 * Print.
	 *
	 * @param lpFile File pointer.
	 * @param lpstrFormat Format string.
	 * @return
	 *     <p>Length of string.</p>
	 */
	static _INTEGER print(FILE* lpFile,_STRING lpstrFormat,...);

	/**
	 * Print line.
	 *
	 * @param lpFile File pointer.
	 * @param lpstrFormat Format string.
	 * @return
	 *     <p>Length of string.</p>
	 */
	static _INTEGER printLine(FILE* lpFile,_STRING lpstrFormat,...);

	/**
	 * Format.
	 *
	 * @param lpstrContent Content string.
	 * @param lpstrFormat Format string.
	 * @return
	 *     <p>End of string.</p>
	 */
	static _STRING format(_STRING lpstrContent,_INT32 nLength,_STRING lpstrFormat,...);
	
	/**
	 * Format line.
	 *
	 * @param lpstrContent Content string.
	 * @param lpstrFormat Format string.
	 * @return
	 *     <p>End of string.</p>
	 */
	static _STRING formatLine(_STRING lpstrContent,_INT32 nLength,_STRING lpstrFormat,...);

	/**
	 * Whether is ended with new line.
	 *
	 * @param lpstrContent Content string.
	 * @return
	 *     <p>Return true, if is ended with new line.</p>
	 */
	static _BOOL endWithsNewLine(_STRING lpstrContent);

	/**
	 * Clear end of new line.
	 *
	 * @param lpstrContent Content string.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void clearEndWithNewLine(_STRING lpstrContent);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_PRINT_H_