///////////////////////////////////////////////////////////////////////////////
//
// KinectProcessAttribute.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KINECT_PROCESS_ATTRIBUTE_H_
#define _KINECT_PROCESS_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectInstanceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// KinectProcessAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CKinectProcessAttribute :
	public virtual CKinectInstanceAttribute
{
private:

	/**
	 * Total frames.
	 */
	_INTEGER totalFrames;
	/** 
	 * Last FPS time.
	 */
	_INTEGER lastFPStime;
	/** 
	 * Last total frames.
	 */
	_INTEGER lastTotalFrames;

private:

	/** 
	 * Nui process.
	 */
	_OBJECT nuiProcess;
	/** 
	 * Nui process event.
	 */
	_OBJECT nuiProcessEvent;

public:
	CKinectProcessAttribute(void);
	virtual ~CKinectProcessAttribute(void);

protected:

	/** 
	 * Get event.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Event.</p>
	 */
	_OBJECT getEvent() const;

protected:

	/** 
	 * Destroy process.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void destroyProcess();

	/** 
	 * Create process.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL createProcess();

protected:

	/** 
	 * Increase total.
	 *
	 * @param index Index of event.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increaseTotal(_INTEGER index);

	/** 
	 * Begin of a frame.
	 *
	 * @param index Index of event.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void frameBegin(_INTEGER index);

	/**
	 * Nui process thread.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Result of thread.</p>
	 */
	virtual DWORD WINAPI nuiProcessThread();

public:

	/**
	 * Nui process thread.
	 *
	 * @param parameter Parameter of thread.
	 * @return
	 *     <p>Result of thread.</p>
	 */
	static DWORD WINAPI nuiProcessThread(LPVOID parameter);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_KINECT_PROCESS_ATTRIBUTE_H_