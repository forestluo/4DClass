///////////////////////////////////////////////////////////////////////////////
//
// KeyListNodeContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KEY_LIST_NODE_CONTAINER_H_
#define _KEY_LIST_NODE_CONTAINER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// KeyListNodeContainer
//
///////////////////////////////////////////////////////////////////////////////

class CKeyListNodeContainer : public CListNodeContainer
{
public:
	CKeyListNodeContainer(void);
	CKeyListNodeContainer(_INTEGER capacity);
	virtual ~CKeyListNodeContainer(void);

public:

	/**
	 * Add an object to the head of list.
	 *
	 * @param key Key of object.
	 * @param object Object for adding.
	 * @return
	 *     <p>Object chain representing this object.<p>
	 */
	_OBJECT addHead(_LONG key,_OBJECT object);

	/**
	 * Add an object to the tail of list.
	 *
	 * @param key Key of object.
	 * @param object Object for adding.
	 * @return
	 *     <p>Object chain representing this object.<p>
	 */
	_OBJECT addTail(_LONG key,_OBJECT object);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KEY_LIST_NODE_CONTAINER_H_
