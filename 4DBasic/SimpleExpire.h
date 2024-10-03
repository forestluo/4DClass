///////////////////////////////////////////////////////////////////////////////
//
// SimpleExpire.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMPLE_EXPIRE_H_
#define _SIMPLE_EXPIRE_H_

#pragma once

////////////////////////////////////////////////////////////////////////////////
//
// Including
//
////////////////////////////////////////////////////////////////////////////////

#include "4DTime.h"

////////////////////////////////////////////////////////////////////////////////
//
// 时间常数
//
////////////////////////////////////////////////////////////////////////////////

#define NEVER_EXPIRE											((_LONG)-1)

////////////////////////////////////////////////////////////////////////////////
//
// SimpleExpire
//
////////////////////////////////////////////////////////////////////////////////

class CSimpleExpire : public C4DTime
{
private:
	//Expiration
	_LONG expiration;

public:
	CSimpleExpire(void);
	CSimpleExpire(_LONG expiration);
	virtual ~CSimpleExpire(void);

public:

	/**
	 * Whether is expired.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is expired.</p>
	 */
	_BOOL isExpired();

	/**
	 * Whether is expired.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is expired.</p>
	 */
	_BOOL isExpired(_LONG expiration);

	/**
	 * Get expiration.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Expiration in milliseconds.</p>
	 */
	_LONG getExpiration();

	/**
	 * Set expiration.
	 *
	 * @param expiration Expiration in milliseconds.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setExpiration(_LONG expiration);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMPLE_EXPIRE_H_
