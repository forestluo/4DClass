///////////////////////////////////////////////////////////////////////////////
//
// HashTreeNode.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HashTreeNode.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define ACTION_CHECK											1
#define ACTION_GET												2
#define ACTION_SET												3
#define ACTION_REMOVE											4

///////////////////////////////////////////////////////////////////////////////
//
// CHashTreeNode
//
///////////////////////////////////////////////////////////////////////////////

CHashTreeNode::CHashTreeNode(void)
{
	//Clear key.
	key = -1L;
	//Set child flag.
	childFlag = 0;
	//Clear parent.
	parent = (CHashTreeNode *)_NULL;
	//Clear subnodes
	for(_INTEGER i = 0;i < 31;i ++)
	{
		//Clear subnodes.
		subnodes[i] = (CHashTreeNode *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CHashTreeNode
//
///////////////////////////////////////////////////////////////////////////////

CHashTreeNode::~CHashTreeNode(void)
{
	//Clear all.
	clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// HasChild
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHashTreeNode::hasChild()
{
	//Return result.
	return childFlag != 0 ? _TRUE : _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearChild
//
///////////////////////////////////////////////////////////////////////////////
	
_BOOL CHashTreeNode::clearChild(CHashTreeNode* node,_INTEGER prime)
{
	//Do while.
	for(_INTEGER i = 0;i < prime;i ++)
	{
		//Check child.
		if(subnodes[i] == node)
		{
			//Clear flag.
			childFlag &= ~(1 << i);
			//Clear hash node.
			subnodes[i] = (CHashTreeNode *)_NULL; return _TRUE;
		}
	}
	//Return false.
	return _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetKey
//
///////////////////////////////////////////////////////////////////////////////

_LONG CHashTreeNode::getKey()
{
	//Return result.
	return key;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll.
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeNode::clearAll()
{
	//Clear key.
	key = -1L;
	//Child flag.
	childFlag = 0;
	//Clear parent.
	parent = (CHashTreeNode *)_NULL;
	//Clear subnodes
	for(_INTEGER i = 0;i < 31;i ++)
	{
		//Check child.
		if(subnodes[i] != _NULL)
		{
			//Delete it.
			delete (CHashTreeNode *)subnodes[i];
			//Clear subnodes.
			subnodes[i] = (CHashTreeNode *)_NULL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Exists
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHashTreeNode::exists(_LONG key,CHashTreeContainer* container)
{
#ifdef _DEBUG
	assert(key != -1L && container != _NULL);
#endif
	//Do action.
	doAction(ACTION_CHECK,key,_NULL,container);
	//Return result.
	return container->keyExists;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetValue
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHashTreeNode::getValue(_LONG key,CHashTreeContainer* container)
{
#ifdef _DEBUG
	assert(key != -1L && container != _NULL);
#endif
	//Do action.
	doAction(ACTION_GET,key,_NULL,container);
	//Return result.
	return container->previousValue;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetValue
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHashTreeNode::setValue(_LONG key,_OBJECT value,CHashTreeContainer* container)
{
#ifdef _DEBUG
	assert(key != -1L && container != _NULL);
#endif
	//Do action.
	doAction(ACTION_SET,key,value,container);
	//Return result.
	return container->previousValue;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveValue
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHashTreeNode::removeValue(_LONG key,CHashTreeContainer* container)
{
#ifdef _DEBUG
	assert(key != -1L && container != _NULL);
#endif
	//Do action.
	doAction(ACTION_REMOVE,key,_NULL,container);
	//Return result.
	return container->previousValue;
}

///////////////////////////////////////////////////////////////////////////////
//
// DoAction
//
///////////////////////////////////////////////////////////////////////////////

CHashTreeNode* CHashTreeNode::doAction(_INTEGER action,_LONG key,_OBJECT value,CHashTreeContainer* container)
{
#ifdef _DEBUG
	assert(key != -1L && container != _NULL);
	assert(action >= ACTION_CHECK && action <= ACTION_REMOVE);
#endif
	//Check result.
	if(this->key == -1L)
	{
		//Check first node.
		if(container->firstNode == _NULL) container->firstNode = this;
	}
	else if(this->key == key)
	{
		//Set flag.
		container->keyExists = _TRUE;
		//Get value.
		container->previousValue = C4DNode::getValue();
		//Check action.
		switch(action)
		{
		case ACTION_SET:
			//Set value.
			C4DNode::setValue(value);
		case ACTION_CHECK:
		case ACTION_GET:
			//Check first node.
			if(container->firstNode == _NULL) return (CHashTreeNode *)_NULL;
			//Swap this node to the first node.
			//Set key.
			container->firstNode->key = key;
			//Set value.
			container->firstNode->C4DNode::setValue(value);
			break;
		case ACTION_REMOVE:
			//Decrease count.
			container->decreaseCount();
			break;
		}
		//Clear this node.
		//Clear key.
		this->key = -1L;
		//Clar value.
		C4DNode::clearValue();
		//Return result.
		return !hasChild() ? this : (CHashTreeNode *)_NULL;
	}

	//Get index.
	_INTEGER index = key % container->getPrime();
	//Check result.
	if(index < 0) index += container->getPrime();
#ifdef _DEBUG
	assert(index >= 0 && index < 31);
#endif
	//Check node.
	CHashTreeNode* subnode = subnodes[index];
	//Check result.
	if(subnode == _NULL)
	{
		//Check action.
		if(action == ACTION_SET)
		{
			//Check first node.
			if(container->firstNode != _NULL)
			{
				//Set key.
				container->firstNode->key = key;
				//Set value.
				container->firstNode->C4DNode::setValue(value);
			}
			else
			{
				//Create subnode.
				subnode = new CHashTreeNode();
#ifdef _DEBUG
				assert(subnode != _NULL);
#endif
				//Set key.
				subnode->key = key;
				//Set value.
				subnode->C4DNode::setValue(value);

				//Set parent.
				subnode->parent = this;
				//Set child flag.
				childFlag |= 1 << index;
				//Set subnode.
				subnodes[index] = subnode;
				//Increase size.
				container->increaseSize();
			}
			//Increase count.
			container->increaseCount();
		}
		//Return result.
		return (CHashTreeNode *)_NULL;
	}
	//Push level.
	container->pushLevel();
	//Set value.
	subnode = subnode->doAction(action,key,value,container);
	//Pop level.
	container->popLevel();
	//Check result.
	if(subnode == _NULL) return (CHashTreeNode *)_NULL;
	//Delete subnode.
	delete (CHashTreeNode *)subnode;
	//Decrease size.
	container->decreaseSize();
#ifndef _DEBUG
	//Clear child.
	clearChild(subnode,container->getPrime());
#else
	//Clear child.
	assert(clearChild(subnode,container->getPrime()));
#endif
	//Check value.
	if(this->key != -1L) return (CHashTreeNode *)_NULL;
	//Check child.
	return !hasChild() ? this : (CHashTreeNode *)_NULL;
}
