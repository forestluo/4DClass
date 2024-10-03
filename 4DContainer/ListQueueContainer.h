///////////////////////////////////////////////////////////////////////////////
//
// ListQueueContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _LIST_QUEUE_CONTAINER_H_
#define _LIST_QUEUE_CONTAINER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNode.h"
#include "4DContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Declaration
//
///////////////////////////////////////////////////////////////////////////////

class CListNode;

///////////////////////////////////////////////////////////////////////////////
//
// ListQueueContainer
//
///////////////////////////////////////////////////////////////////////////////

class CListQueueContainer : public C4DContainer
{
private:
	/**
	 * Root of list.
	 */
	CListNode* root;

	/**
	 * Read position.
	 */
	CListNode* readPosition;
	/**
	 * Write position.
	 */
	CListNode* writePosition;

public:
	CListQueueContainer(void);
	CListQueueContainer(_INTEGER capacity);
	virtual ~CListQueueContainer(void);

private:

	/**
	 * Remove node from the list.
	 *
	 * @param node Node for remove.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void deleteNode(CListNode* node);

	/**
	 * Remove node from the list.
	 *
	 * @param node Node for remove.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void removeNode(CListNode* node);

	/**
	 * Add node to the head of list.
	 *
	 * @param node Node for added.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addHeadNode(CListNode* node);

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
	 * Remove the object from the head of the list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Head object of the list.</p>
	 */
	_OBJECT removeHead();

	/**
	 * Add an object to the tail of list.
	 *
	 * @param object Object for adding.
	 * @return
	 *     <p>No results returned.<p>
	 */
	void addTail(_OBJECT object);

	/**
	 * Remove all objects from this container.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();
};

#endif //_LIST_QUEUE_CONTAINER_H_
