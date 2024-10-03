///////////////////////////////////////////////////////////////////////////////
//
// PhysicsTime.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsTime.h"
#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsTime
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsTime::CPhysicsTime(void)
{
	//Set first time.
	firstTime = _TRUE;
	haveTimer = _FALSE;

	//Create value.
	baseCount = new _LARGE_INTEGER();
#ifdef _DEBUG
	assert(baseCount != _NULL);
#endif

	//Create value.
	frequency = new _LARGE_INTEGER();
#ifdef _DEBUG
	assert(frequency != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsTime
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsTime::~CPhysicsTime(void)
{
	//Check base count.
	if(baseCount != _NULL)
	{
		//Delete value.
		delete (_LARGE_INTEGER *)baseCount;
		//Clear value.
		baseCount = (_LARGE_INTEGER *)_NULL;
	}
	//Check frequency.
	if(frequency != _NULL)
	{
		//Delete value.
		delete (_LARGE_INTEGER *)frequency;
		//Clear value.
		frequency = (_LARGE_INTEGER *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetTimeInMicroseconds
//
///////////////////////////////////////////////////////////////////////////////

_LONG CPhysicsTime::getTimeInMicroseconds()
{
	_LONG ticks;
	LARGE_INTEGER count;

	if(firstTime)
	{
		firstTime = _FALSE;
		haveTimer = QueryPerformanceFrequency((_LARGE_INTEGER *)frequency) ? _TRUE : _FALSE;
		QueryPerformanceCounter ((_LARGE_INTEGER *)baseCount);
	} 
	QueryPerformanceCounter(&count);
	count.QuadPart -= ((_LARGE_INTEGER *)baseCount)->QuadPart;
	ticks = _LONG (count.QuadPart * LONGLONG (1000000) / ((_LARGE_INTEGER *)frequency)->QuadPart);
	//Reutrn result.
	return ticks;
}
