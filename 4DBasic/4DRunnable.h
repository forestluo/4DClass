///////////////////////////////////////////////////////////////////////////////
//
// 4DRunnable.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _4D_RUNNABLE_H_
#define _4D_RUNNABLE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// 4DRunnable
//
///////////////////////////////////////////////////////////////////////////////

class C4DRunnable
{
public:
	//Quiet
	static const _INTEGER quiet;
	//Accerelated
	static const _INTEGER accelerated;
	//Running
	static const _INTEGER running;
	//Decelerated
	static const _INTEGER decelerated;
	//Stopped
	static const _INTEGER stopped;

private:
	/**
	 * Name of thread.
	 */
	CNormalString name;

public:
	C4DRunnable(void);
	C4DRunnable(_STRING name);
	virtual ~C4DRunnable(void);

	/**
	 * Get name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Name of runnable.</p>
	 */
	_STRING getName();

	/**
	 * Set name.
	 *
	 * @param name Name of runnable.
	 * @return
	 *     <p>No results return.</p>
	 */
	void setName(_STRING name);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_4D_RUNNABLE_H_
