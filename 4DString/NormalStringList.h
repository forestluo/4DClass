///////////////////////////////////////////////////////////////////////////////
//
// NormalStringList.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _NORMAL_STRING_LIST_H_
#define _NORMAL_STRING_LIST_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// NormalStringList
//
///////////////////////////////////////////////////////////////////////////////

class CNormalStringList
{
private:
	/** 
	 * Container.
	 */
	_OBJECT container;

public:
	CNormalStringList(void);
	virtual ~CNormalStringList(void);

public:

	/**
	 * Clear all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();

public:

	/**
	 * Add count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of string.</p>
	 */
	_INTEGER getCount() const;

public:

	/**
	 * GetString
	 *
	 * @param index Index.
	 * @return
	 *     <p>Value of string.</p>
	 */
	CNormalString& getString(_INTEGER index);

	/**
	 * GetString
	 *
	 * @param index Index.
	 * @return
	 *     <p>Value of string.</p>
	 */
	const CNormalString& getString(_INTEGER index) const;

public:

	/**
	 * Add string.
	 *
	 * @param string String for adding.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addString(const CNormalString& string);

	/**
	 * Remove string.
	 *
	 * @param string String for removing.
	 * @return
	 *     <p>Return true, if there is a string.</p>
	 */
	_BOOL removeString(const CNormalString& string);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_NORMAL_STRING_LIST_H_
