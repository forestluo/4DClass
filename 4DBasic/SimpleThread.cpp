///////////////////////////////////////////////////////////////////////////////
//
// SimpleThread.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleThread.h"
#include "4DTime.h"
#include "4DPrint.h"
#include "SimpleExpire.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <process.h>

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleThread
//
///////////////////////////////////////////////////////////////////////////////

CSimpleThread::CSimpleThread(void)
	: C4DRunnable(L"CSimpleThread")
{
	//Set default value.
	handle = _NULL;
	//Set wait time.
	waitTime = MILLISECOND;
	//Status.
	status = C4DRunnable::quiet;
}

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleThread
//
///////////////////////////////////////////////////////////////////////////////

CSimpleThread::CSimpleThread(_STRING name)
	: C4DRunnable(name)
{
	//Set default value.
	handle = _NULL;
	//Set wait time.
	waitTime = MILLISECOND;
	//Status.
	status = C4DRunnable::quiet;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CSimpleThread
//
///////////////////////////////////////////////////////////////////////////////

CSimpleThread::~CSimpleThread(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// IsRunning
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::isRunning()
{
	//Return result.
	return status == C4DRunnable::running;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsStopped
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::isStopped()
{
	//Return result.
	return status == C4DRunnable::stopped;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetStatus
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CSimpleThread::getStatus()
{
	//Return result.
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetStatus
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleThread::setStatus(int status)
{
	//Set status.
	this->status = status;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWaitTime
//
///////////////////////////////////////////////////////////////////////////////

_LONG CSimpleThread::getWaitTime()
{
	//Return result.
	return waitTime;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetWaitTime
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleThread::setWaitTime(_LONG milliseconds)
{
	//Set value.
	if(milliseconds >= 0) waitTime = milliseconds;
}

///////////////////////////////////////////////////////////////////////////////
//
// SleepMilliseconds
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleThread::sleepMilliseconds(_LONG milliseconds)
{
#ifdef _DEBUG
	assert(milliseconds >= 0);
#endif
	//Sleep for milliseconds.
	::Sleep((_UINT32)milliseconds);
}

///////////////////////////////////////////////////////////////////////////////
//
// WaitStatus
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::waitStatus(CSimpleThread* thread,_INTEGER status,_LONG milliseconds)
{
#ifdef _DEBUG
	assert(thread != _NULL);
#endif
	//Wait thread.
	CSimpleExpire expiration(milliseconds);
	//Check status.
	while(thread->getStatus() != status)
	{
		//Check timeout.
		if(expiration.isExpired())
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"CSimpleThread::waitStatus : fail to wait status(%d) !",status);
#endif
			break;
		}
		//Sleep for a moment.
		sleepMilliseconds(MILLISECOND);
	}
	//Return result.
	return thread->getStatus() == status;
}

///////////////////////////////////////////////////////////////////////////////
//
// Preprocess
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::preprocess()
{
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Process
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::process()
{
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Postprocess
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::postprocess()
{
	//Return true.
	return _TRUE;
}

////////////////////////////////////////////////////////////////////////////////
//
// StandardThreadProcess
//
////////////////////////////////////////////////////////////////////////////////

_INTEGER StandardThreadProcess(_OBJECT argument)
{
	//Thread.
	CSimpleThread* thread;
#ifdef _DEBUG
	assert(argument != _NULL);
#endif
	//Get thread.
	thread = (CSimpleThread *)argument;

	//Set status of thread.
	thread->setStatus(C4DRunnable::running);
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"CSimpleThread::StandardThreadProcess(%s) : running !",thread->getName());
#endif
	//Running
	while(thread->isRunning())
	{
		//Preprocess.
		if(!thread->preprocess())
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"SimpleThread::StandardThreadProcess(%s) : preprocess break !",thread->getName());
#endif
			break;
		}

		//Do process.
		if(!thread->process())
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"SimpleThread::StandardThreadProcess(%s) : process break !",thread->getName());
#endif
			break;
		}

		//Postprocess.
		if(!thread->postprocess())
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"SimpleThread::StandardThreadProcess(%s) : postprocess break !",thread->getName());
#endif
			break;
		}

		//Get wait time.
		_LONG waitTime = thread->getWaitTime();
		//Check wait time.
		if(waitTime > 0) CSimpleThread::sleepMilliseconds(waitTime);
	}

	//Set status of thread.
	thread->setStatus(C4DRunnable::decelerated);
	/*
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"SimpleThread::StandardThreadProcess(%s) : jumped out !",thread->getName());
#endif
	*/

	//Set status of thread.
	thread->setStatus(C4DRunnable::stopped);
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"SimpleThread::StandardThreadProcess(%s) : stopped !",thread->getName());
#endif
	//Return 0.
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// Startup
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::startup()
{
	//Return result.
	return startup(_TRUE);
}

///////////////////////////////////////////////////////////////////////////////
//
// Startup
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::startup(_BOOL waiting)
{
	//Check status.
	if(getStatus() != C4DRunnable::quiet && handle != _NULL)
	{
#ifdef _DEBUG
		C4DPrint::printLine(stdout,
			L"CSimpleThread::startup(%s) : invalid status(%d) of thread !",getName(),status);
#endif
		return _FALSE;
	}
	//Set status.
	setStatus(C4DRunnable::accelerated);
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"CSimpleThread::startup(%s) : accerelated !",getName());
#endif

	//Thread id.
	DWORD dwThreadId;
	//Call CreateThread() function.
    handle = CreateThread(
						NULL,					// no security attributes
						0,						// use default stack size
						(LPTHREAD_START_ROUTINE)StandardThreadProcess,	// thread function
						this,					// argument to thread function
						0,						// use default creation flags
						&dwThreadId);			// returns the pThread identifier
 	//Check result.
	if(handle == NULL)
	{
#ifdef _DEBUG
		C4DPrint::printLine(stdout,
			L"CSimpleThread::startup(%s) : fail to create thread !",getName());
#endif
		return _FALSE;
	}
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"CSimpleThread::startup(%s) : startup !",getName());
#endif
	//Check waiting.
	if(!waiting)
	{
#ifdef _DEBUG
		C4DPrint::printLine(stdout,
			L"CSimpleThread::startup(%s) : skip waiting !",getName());
#endif
	}
	else
	{
		//Wait status.
		if(!waitStatus(this,C4DRunnable::running,MINUTE))
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"CSimpleThread::startup(%s) : wait for a long time !",getName());
#endif
			return _FALSE;
		}
	}
	//Return true.
	return _TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Shutdown
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleThread::shutdown()
{
	//Shutdown.
	shutdown(_TRUE);
	//Check result.
	if(isStopped())
	{
		//Clear handle.
		handle = _NULL;
		//Set status.
		setStatus(C4DRunnable::quiet);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Shutdown
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimpleThread::shutdown(_BOOL waiting)
{
	//Check status.
	if(getStatus() != C4DRunnable::running || handle == _NULL)
	{
#ifdef _DEBUG
		C4DPrint::printLine(stdout,
			L"CSimpleThread::shutdown(%s) : invalid status(%d) of thread !",getName(),status);
#endif
		return _FALSE;
	}

	//Set status of thread.
	setStatus(C4DRunnable::decelerated);
#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"CSimpleThread::shutdown(%s) : decelerated !",getName());
#endif
	//Check waiting.
	if(waiting)
	{
		//Wait status.
		if(!waitStatus(this,C4DRunnable::stopped,MINUTE))
		{
#ifdef _DEBUG
			C4DPrint::printLine(stdout,
				L"CSimpleThread::shutdown(%s) : fail to waiting !",getName());
#endif
			return _FALSE;
		}
	}
	else
	{
#ifdef _DEBUG
		C4DPrint::printLine(stdout,
			L"CSimpleThread::shutdown(%s) : skip waiting !",getName());
#endif
	}

#ifdef _DEBUG
	C4DPrint::printLine(stdout,
		L"CSimpleThread::shutdown(%s) : it has been shutdown !",getName());
#endif
	//Return true.
	return _TRUE;
}
