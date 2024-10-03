///////////////////////////////////////////////////////////////////////////////
//
// HashListCase.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include <vld.h>
#include <time.h>
#include <stdlib.h>

#include "4DTime.h"
#include "4DPrint.h"

#include "KeyListNode.h"
#include "HashListContainer.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define VALUE_COUNT											100

///////////////////////////////////////////////////////////////////////////////
//
// Main
//
///////////////////////////////////////////////////////////////////////////////

void main(int argc,char* argv[])
{
	//Seed the random-number generator with the current time so that
    //the numbers will be different every time we run.
    srand((unsigned)time(NULL));

#ifdef _DEBUG
	assert(argv != _NULL);
#endif

	//Values.
	_INTEGER values[VALUE_COUNT];
	//Create container.
	CHashListContainer container;

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
		//Get index.
		_INTEGER index = (_INTEGER)(rand() % VALUE_COUNT);
		//Check result.
		if(values[index] == -1)
		{
			//Set value.
			values[index] = rand();
			//Add it into list.
			assert(container.setValue((_LONG)index,(_OBJECT)values[index]) == _NULL);

			//Add insert count.
			insertCount ++;
			/*
			//Print.
			C4DPrint::printLine(stdout,
				L"CHashListContainer::main : key(%d) = value(%d) inserted !",index,values[index]);
			*/
		}
		else
		{
			//Delete it from list.
			assert(container.removeValue((_LONG)index) == (_OBJECT)values[index]);
			/*
			//Print.
			C4DPrint::printLine(stdout,
				L"CHashListContainer::main : key(%d) = value(%d) deleted !",index,values[index]);
			*/

			//Set value.
			values[index] = -1;
			//Add delete count.
			deleteCount ++;
		}
	}
	//Calculate consumed time.
	C4DPrint::printLine(stdout,L"CHashListContainer.main : consumed = %d ms",C4DTime::getMilliseconds() - clock);
	C4DPrint::printLine(stdout,L"CHashListContainer.main : insert = %d",insertCount);
	C4DPrint::printLine(stdout,L"CHashListContainer.main : delete = %d",deleteCount);
	C4DPrint::printLine(stdout,L"CHashListContainer.main : capacity = %d, size = %d, count = %d",
								container.getCapacity(),container.getSize(),container.getCount());

	/*
	//Print.
	C4DPrint::printLine(stdout,L"CHashListContainer.main : print values !"); 
	//Enumeration.
	CListNodeEnumeration iterator;
	//Get enumeration.
	container.getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get value.
		_OBJECT value = iterator.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Print.
		C4DPrint::printLine(stdout,L"\tvalue = %d",value); 
	}
	*/

	/*
	//Print.
	C4DPrint::printLine(stdout,L"CHashListContainer.main : print key-values !"); 
	//Get enumeration.
	container.getEnumeration(&iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get node.
		CKeyListNode* node = (CKeyListNode *)iterator.nextNode();
#ifdef _DEBUG
		assert(node != _NULL);
#endif
		//Print.
		C4DPrint::printLine(stdout,L"\tkey = %d",node->getKey()); 
		C4DPrint::printLine(stdout,L"\tvalue = %d",((_INTEGER)node->getValue())); 
	}
	*/
}