///////////////////////////////////////////////////////////////////////////////
//
// ListNodeEnumeration.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _LIST_NODE_ENUMERATION_H_
#define _LIST_NODE_ENUMERATION_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNode.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class CListNode;

///////////////////////////////////////////////////////////////////////////////
//
// ListNodeEnumeration
//
///////////////////////////////////////////////////////////////////////////////

class CListNodeEnumeration
{
private:
	/**
	 * Root of list.
	 */
	CListNode* root;
	/**
	 * Next node.
	 */
	CListNode* next;

public:
	CListNodeEnumeration(void);
	CListNodeEnumeration(CListNode* root);
	virtual ~CListNodeEnumeration(void);

public:

	/**
	 * Set list root.
	 *
	 * @param root Root of list.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setListRoot(CListNode* root);

	/**
	 * Reset enumeration.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void reset();

	/**
	 * Tests if this enumeration contains more elements.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true if and only if this enumeration object
	 *     contains at least one more element to provide; false otherwise.</p>
	 */
	_BOOL hasMoreElements();

	/**
	 * Returns the next element of this enumeration if this enumeration object
	 * has at least one more element to provide.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>The next element of this enumeration.</p>
	 */
	CListNode* nextNode();

	/**
	 * Returns the next element of this enumeration if this enumeration object
	 * has at least one more element to provide.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>The next element of this enumeration.</p>
	 */
	_OBJECT nextElement();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_LIST_NODE_ENUMERATION_H_
