///////////////////////////////////////////////////////////////////////////////
//
// 4DTime.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_TIME_H_
#define _4D_TIME_H_

#pragma once

////////////////////////////////////////////////////////////////////////////////
//
// Including
//
////////////////////////////////////////////////////////////////////////////////

#include "4DLock.h"

////////////////////////////////////////////////////////////////////////////////
//
// 时间常数
//
////////////////////////////////////////////////////////////////////////////////

#define MILLISECOND												1
#define SECOND													1000 * MILLISECOND
#define MINUTE													60 * SECOND
#define HOUR													60 * MINUTE
#define DAY														24 * HOUR
#define MONTH													30 * DAY
#define YEAR													365 * DAY

////////////////////////////////////////////////////////////////////////////////
//
// 4DTime
//
////////////////////////////////////////////////////////////////////////////////

class C4DTime : public C4DLock
{
private:
	//Millisecond
	_LONG milliseconds;

public:
	C4DTime(void);
	C4DTime(_LONG milliseconds);
	virtual ~C4DTime(void);

public:

	/**
	 * Initialize time.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void initializeTime();

	/**
	 * Get timestamp.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Milliseconds.</p>
	 */
	_LONG getTimestamp();

	/**
	 * Set timestamp.
	 *
	 * @param milliseconds Milliseconds of time.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setTimestamp(_LONG milliseconds);

public:

	/**
	 * Get milliseconds.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Time in milliseconds.</p>
	 */
	static _LONG getMilliseconds();

	/**
	 * Get performance counters.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Performance counters.</p>
	 */
	static _LONG getPerformanceCounters();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_TIME_H_
