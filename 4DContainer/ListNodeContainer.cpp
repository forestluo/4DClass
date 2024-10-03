///////////////////////////////////////////////////////////////////////////////
//
// ListNodeContainer.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ListNodeContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// CListNodeContainer
//
///////////////////////////////////////////////////////////////////////////////

CListNodeContainer::CListNodeContainer(void)
{
	//Set size.
	setSize(1);
	//Create root.
	root = new CListNode();
#ifdef _DEBUG
	assert(root != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CListNodeContainer
//
///////////////////////////////////////////////////////////////////////////////
	
CListNodeContainer::CListNodeContainer(_INTEGER capacity)
	: C4DContainer(capacity)
{
	//Set size.
	setSize(1);
	//Create root.
	root = new CListNode();
#ifdef _DEBUG
	assert(root != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CListNodeContainer
//
///////////////////////////////////////////////////////////////////////////////

CListNodeContainer::~CListNodeContainer(void)
{
#ifdef _DEBUG
	assert(root != _NULL);
#endif

	//Clear all.
	clearAll();

	//Clear next.
	root->setNext((CListNode *)_NULL);
	//Clear previous.
	root->setPrevious((CListNode *)_NULL);
	//Clear value.
	root->setValue((CListNode *)_NULL);

	//Delete root.
	delete (CListNode *)root;
	//Clear root.
	root = (CListNode *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// DeleteNode
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::deleteNode(CListNode* node)
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(node != _NULL);
#endif
	//Remove node.
	removeNode(node);

	//Set value.
	node->clearValue();

	//Delete node.
	delete node;
	//Clear node.
	node = (CListNode *)_NULL;

	//Decrease count.
	decreaseCount();
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveNode
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::removeNode(CListNode* node)
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(node != _NULL);
#endif
	//Sub size.
	decreaseSize();

	//Set next previous.
	node->setNextPrevious(node->getPrevious());
	//Set previous next.
	node->setPreviousNext(node->getNext());

	//Set next.
	node->setNext((CListNode *)_NULL);
	//Set previous.
	node->setPrevious((CListNode *)_NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddTailNode
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::addTailNode(CListNode* node)
{
#ifdef _DEBUG
	assert(node != _NULL);
#endif
	//Add size.
	increaseSize();

	//Set next.
	node->setNext(root);
	//Set previous.
	node->setPrevious(root->getPrevious());

	//Set next previous.
	node->setNextPrevious(node);
	//Set previous next.
	node->setPreviousNext(node);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddHeadNode
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::addHeadNode(CListNode* node)
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(node != _NULL);
#endif
	//Add size.
	increaseSize();

	//Set next.
	node->setNext(root->getNext());
	//Set previous.
	node->setPrevious(root);

	//Set next previous.
	node->setNextPrevious(node);
	//Set previous next.
	node->setPreviousNext(node);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHead
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::getHead()
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(root->getNext() != _NULL);
#endif
	//Get head of list.
	return root->getNext()->getValue();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHead
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::getTail()
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(root->getPrevious() != _NULL);
#endif
	//Get tail of list.
	return root->getPrevious()->getValue();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetIndexed
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::getIndexed(_INTEGER index)
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(index >= 0 && index < getCount());
#endif
	//Get node.
	CListNode* node = root->getNext();
	//Do while.
	while(node != root)
	{
		//Check index.
		if(index == 0) return node->getValue();
		//Sub index.
		index --;
		//Get next.
		node = node->getNext();
	}
	//Return null.
	return _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveHead
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::removeHead()
{
#ifdef _DEBUG
	assert(root != _NULL);
#endif
	
	//Get head.
	CListNode* head = root->getNext();

#ifdef _DEBUG
	assert(head != _NULL);
#endif

	//Check result.
	if(head == root) return _NULL;

	//Get object.
	_OBJECT object = head->getValue();
	//Delete node.
	deleteNode(head);
	//Return object.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveTail
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::removeTail()
{
#ifdef _DEBUG
	assert(root != _NULL);
#endif

	//Get tail.
	CListNode* tail = root->getPrevious();

#ifdef _DEBUG
	assert(tail != _NULL);
#endif

	//Check result.
	if(tail == root) return _NULL;

	//Get object.
	_OBJECT object = tail->getValue();
	//Delete node.
	deleteNode(tail);
	//Return object.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// Remove
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::removeValue(_OBJECT object)
{
	//Node.
	CListNode *node = root->getNext();
	//Do while.
	while(node != root)
	{
		//Get value.
		_OBJECT value = node->getValue();
		//Check result.
		if(value == object) {deleteNode(node); return;}
		//Get next.
		node = node->getNext();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveIndexed
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListNodeContainer::removeIndexed(_INTEGER index)
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(index >= 0 && index < getCount());
#endif
	//Get node.
	CListNode* node = root->getNext();
	//Do while.
	while(node != root)
	{
		//Check index.
		if(index == 0)
		{
			//Get value.
			_OBJECT value = node->getValue();
			//Delete node and return value.
			deleteNode(node); return value;
		}
		//Sub index.
		index --;
		//Get next.
		node = node->getNext();
	}
	//Return null.
	return _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// AddHead
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::addHead(_OBJECT object)
{
	//Increase count.
	increaseCount();
	//Add head.
	addHeadNode(new CListNode(object));
}

///////////////////////////////////////////////////////////////////////////////
//
// AddTail
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::addTail(_OBJECT object)
{
	//Increase count.
	increaseCount();
	//Add tail.
	addTailNode(new CListNode(object));
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::clearAll()
{
#ifdef _DEBUG
	assert(root != _NULL);
#endif
	//Do while.
	while(root->getNext() != root)
	{
		//Remove head.
		removeHead();
#ifdef _DEBUG
		assert(getCount() >= 0);
#endif
	}
#ifdef _DEBUG
	assert(getCount() == 0);
	assert(root->getPrevious() == root);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// Elements
//
///////////////////////////////////////////////////////////////////////////////

void CListNodeContainer::getEnumeration(CListNodeEnumeration* enumeration) const
{
#ifdef _DEBUG
	assert(root != _NULL);
	assert(enumeration != _NULL);
#endif
	//Set root node.
	enumeration->setListRoot(root);
}
