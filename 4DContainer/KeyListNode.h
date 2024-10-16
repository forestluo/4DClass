///////////////////////////////////////////////////////////////////////////////
//
// KeyListNode.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _KEY_LIST_NODE_H_
#define _KEY_LIST_NODE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNode.h"

///////////////////////////////////////////////////////////////////////////////
//
// KeyListNode
//
///////////////////////////////////////////////////////////////////////////////

class CKeyListNode : public CListNode
{
private:
	/**
	 * Key.
	 */
	_LONG key;

public:
	CKeyListNode(void);
	CKeyListNode(_LONG key,_OBJECT value);
	virtual ~CKeyListNode(void);

public:

	/**
	 * Get key.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Key of object.</p>
	 */
	_LONG getKey();

	/**
	 * Set key.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setKey(_LONG key);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_KEY_LIST_NODE_H_