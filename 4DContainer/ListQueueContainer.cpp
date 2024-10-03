///////////////////////////////////////////////////////////////////////////////
//
// ListQueueContainer.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ListQueueContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// CListQueueContainer
//
///////////////////////////////////////////////////////////////////////////////

CListQueueContainer::CListQueueContainer(void)
{
	//Set size.
	setSize(1);
	//Create list.
	root = new CListNode();
#ifdef _DEBUG
	assert(root != _NULL);
#endif

	//Set read position.
	readPosition = root;
	//Set write position.
	writePosition = root;
}

///////////////////////////////////////////////////////////////////////////////
//
// CListQueueContainer
//
///////////////////////////////////////////////////////////////////////////////

CListQueueContainer::CListQueueContainer(_INTEGER capacity)
	: C4DContainer(capacity)
{
	//Set size.
	setSize(1);
	//Create list.
	root = new CListNode();
#ifdef _DEBUG
	assert(root != _NULL);
#endif

	//Set read position.
	readPosition = root;
	//Set write position.
	writePosition = root;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CListQueueContainer
//
///////////////////////////////////////////////////////////////////////////////

CListQueueContainer::~CListQueueContainer(void)
{
#ifdef _DEBUG
	assert(root != _NULL);
#endif

	//Clear all.
	clearAll();

	//Clear object.
	root->clearValue();
	//Clear next.
	root->setNext((CListNode *)_NULL);
	//Clear previous.
	root->setPrevious((CListNode *)_NULL);

	//Delete root.
	delete root;
	//Clear root.
	root = (CListNode *)_NULL;

	//Clear read position.
	readPosition = (CListNode *)_NULL;
	//Clear write position.
	writePosition = (CListNode *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// DeleteNode
//
///////////////////////////////////////////////////////////////////////////////

void CListQueueContainer::deleteNode(CListNode* node)
{
#ifdef _DEBUG
	assert(node != _NULL);
#endif
	//Remove node.
	removeNode(node);

	//Clear value.
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

void CListQueueContainer::removeNode(CListNode* node)
{
#ifdef _DEBUG
	assert(node != _NULL);
#endif
	//Decrease size.
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
// AddHeadNode
//
///////////////////////////////////////////////////////////////////////////////

void CListQueueContainer::addHeadNode(CListNode* node)
{
#ifdef _DEBUG
	assert(node != _NULL);
#endif
	//Increase size.
	increaseSize();

	//Create list element.
	CListNode* element = new CListNode();

	//Set next.
	element->setNext(node->getNext());
	//Set previous.
	element->setPrevious(node);

	//Set next previous.
	element->setNextPrevious(element);
	//Set previous next.
	element->setPreviousNext(element);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHead
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListQueueContainer::getHead()
{
#ifdef _DEBUG
	assert(readPosition != _NULL);
	assert(writePosition != _NULL);
#endif
	//Check position.
	return readPosition != writePosition ? readPosition->getValue() : _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveHead
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CListQueueContainer::removeHead()
{
#ifdef _DEBUG
	assert(readPosition != _NULL);
	assert(writePosition != _NULL);
#endif
	//Check position.
	if(readPosition != writePosition)
	{
		//Decrease count.
		decreaseCount();
		//Get value.
		_OBJECT value = readPosition->getValue();
		//Clear value.
		readPosition->clearValue();
		//Move next.
		readPosition = readPosition->getNext();
		//Return result.
		return value;
	}
	//Return null.
	return _NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// AddTail
//
///////////////////////////////////////////////////////////////////////////////

void CListQueueContainer::addTail(_OBJECT object)
{
#ifdef _DEBUG
	assert(readPosition != _NULL);
	assert(writePosition != _NULL);
#endif
	//Increase count.
	increaseCount();
	//Set object.
	writePosition->setValue(object);
	//Check result.
	if(writePosition->getNext() == readPosition)
	{
		//Add head node.
		addHeadNode(writePosition);
	}
	//Get next.
	writePosition = writePosition->getNext();
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CListQueueContainer::clearAll()
{
	//Call super.
	C4DContainer::clearAll();

	//Remove all elements.
	while((root->getNext()) != root)
	{
		//Get value.
		_OBJECT value = root->getNext()->getValue();
		//Delete node.
		deleteNode(root->getNext());
	}

	//Set size.
	setSize(1);
	//Set read position.
	readPosition = root;
	//Set write position.
	writePosition = root;
}
