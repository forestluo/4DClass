///////////////////////////////////////////////////////////////////////////////
//
// HashTreeContainer.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _HASH_TREE_CONTAINER_H_
#define _HASH_TREE_CONTAINER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DContainer.h"
#include "HashTreeNode.h"

///////////////////////////////////////////////////////////////////////////////
//
// HashTreeContainer
//
///////////////////////////////////////////////////////////////////////////////

class CHashTreeContainer : public C4DContainer
{
	friend class CHashTreeNode;

private:
	/**
	 * Root node.
	 */
	CHashTreeNode* root;

private:
	/**
	 * First subnode.
	 */
	CHashTreeNode* firstNode;

private:
	/**
	 * Max level.
	 */
	_INTEGER maxLevel;
	/**
	 * Level.
	 */
	_INTEGER currentLevel;

	/**
	 * Flag.
	 */
	_BOOL keyExists;
	/**
	 * Object
	 */
	_OBJECT previousValue;
	
public:
	CHashTreeContainer(void);
	virtual ~CHashTreeContainer(void);

private:

	/**
	 * Clear.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clear();

	/**
	 * Push level.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void pushLevel();

	/**
	 * Pop level.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void popLevel();

	/**
	 * Get prime.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Prime value according to current level.</p>
	 */
	_INTEGER getPrime();

public:

	/**
	 * Exists
	 * 
	 * @param key Key value.
	 * @return
	 *     <p>Return true, if key exists.</p>
	 */
	_BOOL exists(_LONG key);

	/**
	 * Get value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_OBJECT getValue(_LONG key);

	/**
	 * Set value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>Previous value.</p>
	 */
	_OBJECT setValue(_LONG key,_OBJECT value);

	/**
	 * Remove value.
	 *
	 * @param key Key value.
	 * @return
	 *     <p>Previous value.</p>
	 */
	_OBJECT removeValue(_LONG key);

	/**
	 * Clear all.
	 * 
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void clearAll();

public:

	/**
	 * Get max level.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Max level value.</p>
	 */
	_INTEGER getMaxLevel();

public:

	/**
	 * Main
	 *
	 * @param argc Count of arguments.
	 * @param argv Parameter of arguments.
	 * @return
	 *     <p>No results returned.</p>
	 */
	static void main(int argc,char* argv[]);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_HASH_TREE_CONTAINER_H_
