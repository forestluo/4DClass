///////////////////////////////////////////////////////////////////////////////
//
// KinectProcessAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectProcessAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "MSR_NuiApi.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define NUI_INSTANCE(p)										((INuiInstance *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CKinectProcessAttribute
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectProcessAttribute::CKinectProcessAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CKinectProcessAttribute
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectProcessAttribute::~CKinectProcessAttribute(void)
{
	//Destroy process.
	destroyProcess();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEvent
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CKinectProcessAttribute::getEvent() const
{
	//Return value.
	return nuiProcessEvent;
}

///////////////////////////////////////////////////////////////////////////////
//
// IncreaseTotal
//
///////////////////////////////////////////////////////////////////////////////

void CKinectProcessAttribute::increaseTotal(_INTEGER index)
{
	//Add total frame.
	totalFrames ++;
}

///////////////////////////////////////////////////////////////////////////////
//
// FrameBegin
//
///////////////////////////////////////////////////////////////////////////////

void CKinectProcessAttribute::frameBegin(_INTEGER index)
{
	//Perform FPS processing.
	int t = timeGetTime();
	//Check last time.
	if(lastFPStime == -1)
	{
		//Set last fps time.
		lastFPStime = t;
		//Set total frames.
		lastTotalFrames = totalFrames;
	}
	//Calculate time.
	int dt = t - lastFPStime;
	//Check result.
	if(dt > 1000)
	{
		//Set last fps time.
		lastFPStime = t;
		//Calculate delta.
		int frameDelta = totalFrames - lastTotalFrames;
		//Set last total frames.
		lastTotalFrames = totalFrames;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// NuiProcessThread
//
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CKinectProcessAttribute::nuiProcessThread()
{
	//Events.
	HANDLE events[1];
	// Configure events to be listened on
	events[0]= nuiProcessEvent;
	//events[1]= nextDepthFrameEvent;
	//events[2]= nextVideoFrameEvent;

#pragma warning(push)
	//Conditional expression is constant
#pragma warning(disable: 4127)
	//Main thread loop.
	while(_TRUE)
	{
		//Wait for an event to be signaled.
		DWORD index = WaitForMultipleObjects(sizeof(events)/sizeof(events[0]),events,FALSE,100);
		//If the stop event, stop looping and exit.
		if(index == 0) break;
		//Perform FPS processing.
		frameBegin(index);
		//Process signal events.
		switch(index)
		{
		case 1:
			//Nui_GotDepthAlert();
			increaseTotal(index);
			break;
		case 2:
			//Nui_GotVideoAlert();
			break;
		case 3:
			//Nui_GotSkeletonAlert();
			break;
		}
	}
#pragma warning(pop)

	//Return result.
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// NuiProcessThread
//
///////////////////////////////////////////////////////////////////////////////

DWORD WINAPI CKinectProcessAttribute::nuiProcessThread(LPVOID parameter)
{
#ifdef _DEBUG
	assert(parameter != _NULL);
#endif
	//Return result.
	return ((CKinectProcessAttribute *)parameter)->nuiProcessThread();
}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyProcess
//
///////////////////////////////////////////////////////////////////////////////

void CKinectProcessAttribute::destroyProcess()
{
	//Stop the Nui processing thread.
	if(nuiProcessEvent != _NULL)
	{
		//Signal the thread.
		SetEvent(nuiProcessEvent);
		//Wait for thread to stop.
		if(nuiProcess != _NULL)
		{
			//Wait process to shutdown.
			WaitForSingleObject(nuiProcess,INFINITE);
			//Close and clear handle.
			CloseHandle(nuiProcess); nuiProcess = _NULL;
		}
		//Close and clear handle.
		CloseHandle(nuiProcessEvent); nuiProcessEvent = _NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateProcess
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CKinectProcessAttribute::createProcess()
{
	//Start the Nui processing thread
	nuiProcessEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
#ifdef _DEBUG
	assert(nuiProcessEvent != _NULL && nuiProcessEvent != INVALID_HANDLE_VALUE);
#endif

	//Create process.
	nuiProcess = CreateThread(NULL,0,nuiProcessThread,this,0,NULL);
#ifdef _DEBUG
	assert(nuiProcess != _NULL);
#endif
	//Return true.
	return _TRUE;
}