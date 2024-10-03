///////////////////////////////////////////////////////////////////////////////
//
// BoxObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "BoxObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DPrint.h"

#include "MultiBoxObject.h"
#include "SingleBoxObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CBoxObject
//
///////////////////////////////////////////////////////////////////////////////

CBoxObject::CBoxObject(void)
{
	//Set default value.
	box = (CSimpleBox *)_NULL;
	sphere = (CSimpleSphere *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CBoxObject
//
///////////////////////////////////////////////////////////////////////////////

CBoxObject::~CBoxObject(void)
{
	//Clear all.
	clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearAll
//
///////////////////////////////////////////////////////////////////////////////

void CBoxObject::clearAll()
{
	//Check box.
	if(box != _NULL)
	{
		//Recycle box.
		box->recycle();
		//Clear box.
		box = (CSimpleBox *)_NULL;
	}
	//Check sphere.
	if(sphere != _NULL)
	{
		//Recycle sphere.
		sphere->recycle();
		//Clear sphere.
		sphere = (CSimpleSphere *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBox
//
///////////////////////////////////////////////////////////////////////////////

CSimpleBox* CBoxObject::getBox()
{
	//Return result.
	return box;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearBox
//
///////////////////////////////////////////////////////////////////////////////

void CBoxObject::clearBox()
{
#ifdef _DEBUG
	assert(box != _NULL);
#endif
	//Recycle axis aligned box.
	box->recycle();
	//Clear axis aligned box.
	box = (CSimpleBox *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetBox
//
///////////////////////////////////////////////////////////////////////////////
	
void CBoxObject::setBox(CSimpleBox* box)
{
#ifdef _DEBUG
	assert(box != _NULL);
	assert(this->box == _NULL);
#endif
	//Set box.
	this->box = box;
}

///////////////////////////////////////////////////////////////////////////////
//
// ClearSphere
//
///////////////////////////////////////////////////////////////////////////////

void CBoxObject::clearSphere()
{
#ifdef _DEBUG
	assert(sphere != _NULL);
#endif
	//Recycle sphere.
	sphere->recycle();
	//Clear sphere.
	sphere = (CSimpleSphere *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSphere
//
///////////////////////////////////////////////////////////////////////////////

CSimpleSphere* CBoxObject::getSphere(void)
{
	//Return result.
	return sphere;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSphere
//
///////////////////////////////////////////////////////////////////////////////
	
void CBoxObject::setSphere(CSimpleSphere* sphere)
{
#ifdef _DEBUG
	assert(sphere != _NULL);
	assert(this->sphere == _NULL);
#endif
	//Set sphere.
	this->sphere = sphere;
}

///////////////////////////////////////////////////////////////////////////////
//
// Dump
//
///////////////////////////////////////////////////////////////////////////////

void CBoxObject::dump()
{
	C4DPrint::printLine(stdout,L"CBoxObject::dump : show parameters !");
	//Check box.
	if(box != _NULL) box->dump();
	//Check sphere.
	if(sphere != _NULL) sphere->dump();
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetSingleBoxObject
//
/////////////////////////////////////////////////////////////////////////////////

CBoxObject* getSingleBoxObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Malloc object.
	CSingleBoxObject* boxObject = CSingleBoxObject::create();
#ifdef _DEBUG
	assert(boxObject != _NULL);
#endif

	//Create box.
	CSimpleBox* box = CSimpleBox::create();
#ifdef _DEBUG
	assert(box != _NULL);
#endif
	//Check box.
	if(object->getWorldBox(*box))
	{
		//Set box.
		boxObject->setBox(box);
	}
	else
	{
		//Recycle.
		boxObject->recycle();
		//Return result.
		return (CBoxObject *)_NULL;
	}

	//Create sphere.
	CSimpleSphere* sphere = CSimpleSphere::create();
#ifdef _DEBUG
	assert(sphere != _NULL);
#endif
	//Get sphere.
	if(object->getWorldSphere(*sphere))
	{
		//Set sphere.
		boxObject->setSphere(sphere);
	}
	else
	{
		//Recycle.
		boxObject->recycle();
		//Return result.
		return (CBoxObject *)_NULL;
	}
	//Return result.
	return boxObject;
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetMultiBoxObject
//
/////////////////////////////////////////////////////////////////////////////////

CBoxObject* getMultiBoxObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif

	//Malloc object.
	CMultiBoxObject* boxObject = CMultiBoxObject::create();
#ifdef _DEBUG
	assert(boxObject != _NULL);
#endif

	//Create box.
	CSimpleBox* box = CSimpleBox::create();
#ifdef _DEBUG
	assert(box != _NULL);
#endif
	//Check box.
	if(object->getWorldBox(*box))
	{
		//Set box.
		boxObject->setBox(box);
	}
	else
	{
		//Recycle.
		box->recycle();
		//Return result.
		return (CBoxObject *)_NULL;
	}

	//Create sphere.
	CSimpleSphere* sphere = CSimpleSphere::create();
#ifdef _DEBUG
	assert(sphere != _NULL);
#endif
	//Get sphere.
	if(object->getWorldSphere(*sphere))
	{
		//Set sphere.
		boxObject->setSphere(sphere);
	}
	else
	{
		//Recycle.
		sphere->recycle();
		//Return result.
		return (CBoxObject *)_NULL;
	}

	//Enumeration.
	CListNodeEnumeration iterator;
	//Get enumeration.
	object->getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get child object.
		CWorldObject* childObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(childObject != _NULL);
#endif
		//Get collision tree.
		CBoxObject* subObject = (CBoxObject *)_NULL;
		//Check instance.
		if(childObject->isCompoundObject())
		{
			//Get object.
			subObject = getMultiBoxObject(childObject);
		}
		else if(childObject->isJointObject())
		{
			//Get object.
			subObject = getMultiBoxObject(childObject);
		}
		else if(childObject->isPrimitiveObject())
		{
			//Get object.
			subObject = getSingleBoxObject(childObject);
		}
		//Check result.
		if(subObject != _NULL) boxObject->addObject(subObject);
	}
	//Return result.
	return boxObject;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetBoxObject
//
///////////////////////////////////////////////////////////////////////////////

CBoxObject* CBoxObject::getBoxObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Check instance.
	if(object->isCompoundObject())
	{
		//Get object.
		return getMultiBoxObject(object);
	}
	else if(object->isJointObject())
	{
		//Get object.
		return getMultiBoxObject(object);
	}
	else if(object->isPrimitiveObject())
	{
		//Get object.
		return getSingleBoxObject(object);
	}
	//Return null.
	return (CBoxObject *)_NULL;
}
