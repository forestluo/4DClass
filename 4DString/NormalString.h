///////////////////////////////////////////////////////////////////////////////
//
// NormalString.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _NORMAL_STRING_H_
#define _NORMAL_STRING_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DString.h"

///////////////////////////////////////////////////////////////////////////////
//
// NormalString
//
///////////////////////////////////////////////////////////////////////////////

class CNormalString : public C4DString
{
public:
	CNormalString(void);
	CNormalString(const _STRING string);
	CNormalString(const CNormalString& string);
	virtual ~CNormalString(void);

	CNormalString& operator = (const CNormalString& string);

	_BOOL operator == (const CNormalString& string) const;
	_BOOL operator != (const CNormalString& string) const;

public:

	/**
	 * Recycle string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>String value.</p>
	 */
	virtual void recycle();

	/**
	 * Create string.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>String value.</p>
	 */
	static CNormalString* create();

	/**
	 * Create string.
	 *
	 * @param string Content of string.
	 * @return
	 *     <p>String value.</p>
	 */
	static CNormalString* create(_STRING string);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_NORMAL_STRING_H_
