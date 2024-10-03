///////////////////////////////////////////////////////////////////////////////
//
// SimpleFlowmeter.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMPLE_FLOWMETER_H_
#define _SIMPLE_FLOWMETER_H_

#pragma once

////////////////////////////////////////////////////////////////////////////////
//
// Including
//
////////////////////////////////////////////////////////////////////////////////

#include "SimpleExpire.h"

////////////////////////////////////////////////////////////////////////////////
//
// 流量常数
//
////////////////////////////////////////////////////////////////////////////////

#define FLUX_UNLIMITED											((_INT32)-1)

////////////////////////////////////////////////////////////////////////////////
//
// SimpleFlowmeter
//
////////////////////////////////////////////////////////////////////////////////

class CSimpleFlowmeter : public CSimpleExpire
{
private:
	//Total Count
	_LONG count;

	//Max Flux
	_INTEGER maximumFlux;
	//Peak Flux
	_INTEGER peakFlux;
	//Current Flux
	_INTEGER currentFlux;

	//Accumulate
	_INTEGER accumulate;

public:
	CSimpleFlowmeter(void);
	CSimpleFlowmeter(_INTEGER flux);
	virtual ~CSimpleFlowmeter(void);

public:

	/**
	 * Clear all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();

	/**
	 * Set flux.
	 *
	 * @param flux Maximum flux.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFlux(_INTEGER flux);

	/**
	 * Check remains.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if there is no flux.</p>
	 */
	_BOOL isFull();

	/**
	 * Reset flowmeter.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void reset();

	/**
	 * Reset flowmeter.
	 *
	 * @param timestamp Timestamp.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void reset(_LONG timestamp);

	/**
	 * Increase.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increase();

	/**
	 * Increase.
	 *
	 * @param total Total count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void increase(_INTEGER total);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMPLE_FLOWMETER_H_
