///////////////////////////////////////////////////////////////////////////////
//
// ListNodeContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _LIST_NODE_CONTAINER_H_
#define _LIST_NODE_CONTAINER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNode.h"
#include "4DContainer.h"
#include "ListNodeEnumeration.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class CListNode;
class CListNodeEnumeration;

///////////////////////////////////////////////////////////////////////////////
//
// ListNodeContainer
//
///////////////////////////////////////////////////////////////////////////////

class CListNodeContainer : public C4DContainer
{
private:
	/**
	 * Root of list.
	 */
	CListNode* root;

public:
	CListNodeContainer(void);
	CListNodeContainer(_INTEGER capacity);
	virtual ~CListNodeContainer(void);

protected:

	/**
	 * Add node to the tail of list.
	 *
	 * @param node Node for added.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addTailNode(CListNode* node);

	/**
	 * Add node to the head of list.
	 *
	 * @param node Node for added.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addHeadNode(CListNode* node);

	/**
	 * Remove node from the list.
	 *
	 * @param node Node for remove.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void removeNode(CListNode* node);

public:

	/**
	 * Delete node from the list.
	 *
	 * @param node Node for remove.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void deleteNode(CListNode* node);

public:

	/**
	 * Get object from the head of the list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Head object of the list.</p>
	 */
	_OBJECT getHead();

	/**
	 * Get object from the tail of the list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Tail object of the list.</p>
	 */
	_OBJECT getTail();

	/**
	 * Get object by index.
	 *
	 * @param index Index of object.
	 * @return
	 *     <p>Indexed object of the list.</p>
	 */
	_OBJECT getIndexed(_INTEGER index);

	/**
	 * Remove the object from the head of the list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Head object of the list.</p>
	 */
	_OBJECT removeHead();

	/**
	 * Remove the object from the tail of the list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Tail object of the list.</p>
	 */
	_OBJECT removeTail();

	/**
	 * Remove an object from list.
	 *
	 * @param object Object for removing.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void removeValue(_OBJECT object);

	/**
	 * Remove an object by index.
	 *
	 * @param index Index of object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_OBJECT removeIndexed(_INTEGER index);

	/**
	 * Add an object to the head of list.
	 *
	 * @param object Object for adding.
	 * @return
	 *     <p>Object chain representing this object.<p>
	 */
	void addHead(_OBJECT object);

	/**
	 * Add an object to the tail of list.
	 *
	 * @param object Object for adding.
	 * @return
	 *     <p>Object chain representing this object.<p>
	 */
	void addTail(_OBJECT object);

	/**
	 * Remove objects from this list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();

	/**
	 * Get enumeration of container.
	 *
	 * @param enumeration Enumeration.
	 * @return
	 *     <p>No results returned.</p>
	 */
	 void getEnumeration(CListNodeEnumeration* enumeration) const;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_LIST_NODE_CONTAINER_H_
