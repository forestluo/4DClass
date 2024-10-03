///////////////////////////////////////////////////////////////////////////////
//
// SimpleThread.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMPLE_THREAD_H_
#define _SIMPLE_THREAD_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DRunnable.h"

///////////////////////////////////////////////////////////////////////////////
//
// SimpleThread
//
///////////////////////////////////////////////////////////////////////////////

class CSimpleThread : public C4DRunnable
{
	friend _INTEGER StandardThreadProcess(_OBJECT argument);

private:
	/**
	 * Handle of thread.
	 */
	_OBJECT handle;
	/**
	 * Status.
	 */
	_INTEGER status;
	/**
	 * Wait time.
	 */
	_LONG waitTime;

public:
	CSimpleThread(void);
	CSimpleThread(_STRING name);
	virtual ~CSimpleThread(void);

protected:

	/**
	 * Set status of thread.
	 *
	 * @param status Status of thread.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setStatus(_INTEGER status);

protected:

	/**
	 * Startup.
	 *
	 * @param waiting Whether waiting.
	 * @return
	 *     <p>Return true, if startup.</p>
	 */
	_BOOL startup(_BOOL waiting);

	/**
	 * Shutdown.
	 *
	 * @param waiting Whether waiting.
	 * @return
	 *     <p>Return true, if shutdown.</p>
	 */
	_BOOL shutdown(_BOOL waiting);

	/**
	 * Wait thread into a specified status.
	 *
	 * @param thread Thread for waiting.
	 * @param status Specified status.
	 * @param milliseconds Millseconds for waiting.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	static _BOOL waitStatus(CSimpleThread* thread,_INTEGER status,_LONG milliseconds);

protected:

	/**
	 * Preprocess.
	 *
	 * <p>It should be override.</p>
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Return true, if routine is all right.</p>
	 */
	virtual _BOOL preprocess();

	/**
	 * Do process.
	 *
	 * <p>It should be override.</p>
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Return true, if thread is all right.</p>
	 */
	virtual _BOOL process();

	/**
	 * Postprocess.
	 *
	 * <p>It should be override.</p>
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>Return true, if routine is all right.</p>
	 */
	virtual _BOOL postprocess();

public:

	/**
	 * Startup.
	 *
	 * @param waiting Whether waiting.
	 * @return
	 *     <p>Return true, if startup.</p>
	 */
	virtual _BOOL startup();

	/**
	 * Shutdown.
	 *
	 * @param waiting Whether waiting.
	 * @return
	 *     <p>Return true, if shutdown.</p>
	 */
	virtual void shutdown();

	/**
	 * Check whether a thread is in running status.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return ture, if thread is in running status.</p>
	 */
	_BOOL isRunning();

	/**
	 * Check whether a thread is already stopped.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if thread is in stopped status.</p>
	 */
	_BOOL isStopped();

	/**
	 * Get status of thread.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Status of process.</p>
	 */
	_INTEGER getStatus();

	/**
	 * Get wait time.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Wait time in milliseconds.</p>
	 */
	_LONG getWaitTime();

	/**
	 * Set wait time.
	 *
	 * @param milliseconds Milliseconds.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setWaitTime(_LONG milliseconds);

	/**
	 * Sleep milliseconds.
	 *
	 * @param milliseconds Milliseconds.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void sleepMilliseconds(_LONG milliseconds);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMPLE_THREAD_H_
