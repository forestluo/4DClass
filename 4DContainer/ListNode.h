////////////////////////////////////////////////////////////////////////////////
//
// ListNode.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DNode.h"

///////////////////////////////////////////////////////////////////////////////
//
// ListNode
//
///////////////////////////////////////////////////////////////////////////////

class CListNode : public C4DNode
{
private:
	//Next
	CListNode* next;
	//Previous
	CListNode* previous;

public:
	CListNode(void);
	CListNode(_OBJECT value);
	virtual ~CListNode(void);

	/**
	 * Get node of next object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Node of next object.</p>
	 */
	CListNode* getNext();

	/**
	 * Get node of previous object.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Node of previous object.</p>
	 */
	CListNode* getPrevious();

	/**
	 * Set node of next object.
	 *
	 * @param next Node of next object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setNext(CListNode* next);

	/**
	 * Set node of previous object.
	 *
	 * @param previous Node of previous object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPrevious(CListNode* previous);

	/**
	 * Set node of next previous object.
	 *
	 * @param previous Node of next previous object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setNextPrevious(CListNode* previous);

	/**
	 * Set node of previous next object.
	 *
	 * @param next Node of previous next object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPreviousNext(CListNode* next);
};

////////////////////////////////////////////////////////////////////////////////
#endif //_LIST_NODE_H_