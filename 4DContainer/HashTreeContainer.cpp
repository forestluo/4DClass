///////////////////////////////////////////////////////////////////////////////
//
// HashTreeContainer.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "HashTreeContainer.h"
#include "4DTime.h"
#include "4DPrint.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <time.h>
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define VALUE_COUNT											1000000

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Primes
const _INTEGER hashPrimes[18] = 
{
	//Used.
	31, 30, 29, 23, 19, 17, 11, 13, 7,
	//Not used.
	37, 41, 43, 47, 53, 59, 61
};

///////////////////////////////////////////////////////////////////////////////
//
// CHashTreeContainer
//
///////////////////////////////////////////////////////////////////////////////

CHashTreeContainer::CHashTreeContainer(void)
{
	//Create root.
	root = new CHashTreeNode();
#ifdef _DEBUG
	assert(root != _NULL);
#endif
	//Increase size.
	increaseSize();

	//Set default value.
	maxLevel = 0;
	currentLevel = 0;
	keyExists = _FALSE;
	previousValue = _NULL;
	firstNode = (CHashTreeNode *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CHashTreeContainer
//
///////////////////////////////////////////////////////////////////////////////

CHashTreeContainer::~CHashTreeContainer(void)
{
	//Check result.
	if(root != _NULL)
	{
		//Delete root.
		delete (CHashTreeNode *)root;
		//Clear root.
		root = (CHashTreeNode *)_NULL;
	}
	//Clear value.
	previousValue = _NULL;
	//Clear first node.
	firstNode = (CHashTreeNode *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// Clear
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeContainer::clear()
{
	//Clear value.
	currentLevel = 0;
	keyExists = _FALSE;
	previousValue = _NULL;
	firstNode = (CHashTreeNode *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// PushLevel
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeContainer::pushLevel()
{
	//Add level.
	currentLevel ++;
	//Check result.
	if(currentLevel > maxLevel) maxLevel = currentLevel;
}

///////////////////////////////////////////////////////////////////////////////
//
// PopLevel
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeContainer::popLevel()
{
	//Sub level.
	currentLevel --;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrime
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CHashTreeContainer::getPrime()
{
#ifdef _DEBUG
	assert(currentLevel >= 0 && currentLevel < 10);
#endif
	//Return result.
	return hashPrimes[currentLevel];
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMaxLevel
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CHashTreeContainer::getMaxLevel()
{
	//Return result.
	return maxLevel;
}

///////////////////////////////////////////////////////////////////////////////
//
// Exists
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CHashTreeContainer::exists(_LONG key)
{
#ifdef _DEBUG
	assert(key != -1L);
#endif
	//Clear.
	clear();
	//Return result.
	return root->exists(key,this);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetValue
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHashTreeContainer::getValue(_LONG key)
{
#ifdef _DEBUG
	assert(root != _NULL && key != -1L);
#endif
	//Clear.
	clear();
	//Return result.
	return root->getValue(key,this);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetValue
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CHashTreeContainer::setValue(_LONG key,_OBJECT value)
{
#ifdef _DEBUG
	assert(root != _NULL && key != -1L);
#endif
	//Clear.
	clear();
	//Do it recursively.
	return root->setValue(key,value,this);
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveValue
//
///////////////////////////////////////////////////////////////////////////////
	
_OBJECT CHashTreeContainer::removeValue(_LONG key)
{
#ifdef _DEBUG
	assert(root != _NULL && key != -1L);
#endif
	//Clear.
	clear();
	//Do it recursively.
	return root->removeValue(key,this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Clear all.
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeContainer::clearAll()
{
	C4DContainer::clearAll();

	//Clear.
	clear();
	//Increase size.
	increaseSize();

#ifdef _DEBUG
	assert(root != _NULL);
#endif
	//Clear all.
	root->clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

void CHashTreeContainer::main(int argc,char* argv[])
{
	//Seed the random-number generator with the current time so that
    //the numbers will be different every time we run.
    srand((unsigned)time(NULL));

#ifdef _DEBUG
	assert(argv != _NULL);
#endif

	//Values.
	_INTEGER* values = (_INTEGER *)malloc(VALUE_COUNT * sizeof(_INTEGER));
	//Create container.
	CHashTreeContainer container;

	//Rand count.
	_INTEGER randCount = 0;
	//Insert count.
	_INTEGER insertCount = 0;
	//Delete count.
	_INTEGER deleteCount = 0;

	//Initialize values.
	for(_INTEGER i = 0;i < VALUE_COUNT;i ++) values[i] = -1;

	//Get current clock.
	_LONG clock = C4DTime::getMilliseconds();
	//Do testing.
	for(_INTEGER i = 0;i < 10 * VALUE_COUNT;i ++)
	{
		//Add rand count.
		randCount ++;
		//Get index.
		_INTEGER index = (_INTEGER)(rand() % VALUE_COUNT);
		//Check result.
		if(values[index] == -1)
		{
			//Add rand count.
			randCount ++;
			//Set value.
			values[index] = rand();

			//Add it into list.
			assert(container.setValue((_LONG)index,(_OBJECT)values[index]) == _NULL);
			/*
			//Print.
			C4DPrint::printLine(stdout,
				L"CHashTreeContainer::main : key(%d) value(%d) inserted !",index,values[index]);*/

			//Add insert count.
			insertCount ++;
		}
		else
		{
			//Delete it from list.
			assert(container.removeValue((_LONG)index) == (_OBJECT)values[index]);
			/*
			//Print.
			C4DPrint::printLine(stdout,
				L"CHashTreeContainer::main : key(%d) value(%d) deleted !",index,values[index]);*/

			//Add delete count.
			deleteCount ++;
			//Set value.
			values[index] = -1;
		}
	}
	//Free values.
	free(values);
	//Calculate consumed time.
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : max level = %d",container.getMaxLevel());
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : consumed = %d ms",C4DTime::getMilliseconds() - clock);

	//Print result.
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : rand = %d",randCount);
	//Get current clock.
	clock = C4DTime::getMilliseconds();
	//Do rand.
	for(_INTEGER i = 0;i < randCount;i ++) rand();
	//Print result.
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : rand consumed = %d ms",C4DTime::getMilliseconds() - clock);

	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : insert = %d",insertCount);
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : delete = %d",deleteCount);
	C4DPrint::printLine(stdout,L"CHashTreeContainer.main : capacity = %d, size = %d, count = %d",
								container.getCapacity(),container.getSize(),container.getCount());
}