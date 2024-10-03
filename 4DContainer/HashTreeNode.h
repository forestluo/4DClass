///////////////////////////////////////////////////////////////////////////////
//
// HashTreeNode.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _HASH_TREE_NODE_H_
#define _HASH_TREE_NODE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DNode.h"
#include "HashTreeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// HashTreeNode
//
///////////////////////////////////////////////////////////////////////////////

class CHashTreeNode : public C4DNode
{
	friend class CHashTreeContainer;

private:
	/**
	 * Child flag.
	 */
	_INTEGER childFlag;
	/**
	 * Parent.
	 */
	CHashTreeNode* parent;

private:
	/**
	 * Key
	 */
	_LONG key;
	/**
	 * Subnodes.
	 */
	CHashTreeNode* subnodes[31];

public:
	CHashTreeNode(void);
	virtual ~CHashTreeNode(void);

private:

	/**
	 * Has child.
	 *
	 * <p>Whether has child.</p>
	 *
	 * @param prime Prime limitation.
	 * @return
	 *     <p>Return true, if it has child.</p>
	 */
	_BOOL hasChild();

	/**
	 * Clear child.
	 *
	 * @param node Node.
	 * @param prime Prime limitation.
	 * @return
	 *     <p>Index of this node.</p>
	 */
	_BOOL clearChild(CHashTreeNode* node,_INTEGER prime);

private:

	/**
	 * DoAction
	 * 
	 * @param action Action type.
	 * @param key Key value.
	 * @param value Object value.
	 * @param container Hash tree container.
	 * @return
	 *     <p>Node that has no child.</p>
	 */
	CHashTreeNode* doAction(_INTEGER action,_LONG key,_OBJECT value,CHashTreeContainer* container);

private:

	/**
	 * Exists
	 * 
	 * @param key Key value.
	 * @param container Hash tree container.
	 * @return
	 *     <p>Return true, if key exists.</p>
	 */
	_BOOL exists(_LONG key,CHashTreeContainer* container);

	/**
	 * Get value.
	 *
	 * @param key Key value.
	 * @param container Hash tree container.
	 * @return
	 *     <p>Current value of the key.</p>
	 */
	_OBJECT getValue(_LONG key,CHashTreeContainer* container);

	/**
	 * Set value.
	 *
	 * @param key Key value.
	 * @param container Hash tree container.
	 * @return
	 *     <p>Previous value of the key.</p>
	 */
	_OBJECT removeValue(_LONG key,CHashTreeContainer* container);

	/**
	 * Set value.
	 *
	 * @param key Key value.
	 * @param value Value for setting.
	 * @param container Hash tree container.
	 * @return
	 *     <p>Previous value of the key.</p>
	 */
	_OBJECT setValue(_LONG key,_OBJECT value,CHashTreeContainer* container);

public:

	/**
	 * Get key.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>Key of node.</p>
	 */
	_LONG getKey();

	/**
	 * Remove objects from this list.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAll();
};

///////////////////////////////////////////////////////////////////////////////
#endif //_HASH_TREE_NODE_H_
