///////////////////////////////////////////////////////////////////////////////
//
// 4DDebug.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "4DDebug.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(compiler)
//Initialize
static C4DDebug debugger;

///////////////////////////////////////////////////////////////////////////////
//
// MemoryAllocHook
//
/////////////////////////////////////////////////////////////////////////////////

int MemoryAllocHook(int allocType,void *userData, size_t size, int blockType, 
					long requestNumber, const unsigned char *filename, int lineNumber)
{
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DDebug
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

C4DDebug::C4DDebug(void)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );
	_CrtSetAllocHook(MemoryAllocHook);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// C4DDebug
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

C4DDebug::~C4DDebug(void)
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}
