///////////////////////////////////////////////////////////////////////////////
//
// CompoundObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "JointObject.h"
#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CCompoundObject::base(L"CCompoundObject",L"CD3DXCompoundObject");

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundObject::CCompoundObject(void)
{
	//Set this.
	setThis(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundObject::~CCompoundObject(void)
{
	//Enumeration.
	CListNodeEnumeration iterator;
	//Get numeration.
	getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get world object.
		CWorldObject* object = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(object != _NULL);
#endif
		//Check result.
		if(object->isPhysicsObject()
			&& object->isRenderableObject())
		{
			//Remove it from list.
			CWorldObject::removeObject(object);

			//Get this.
			_OBJECT thisObject = object->getThis();
#ifdef _DEBUG
			assert(thisObject != _NULL);
#endif
			//Check type.
			if(object->isJointObject())
			{
				//Delete object.
				delete (CJointObject *)thisObject;
			}
			else if(object->isCompoundObject())
			{
				//Delete object.
				delete (CCompoundObject *)thisObject;
			}
			else if(object->isPrimitiveObject())
			{
				//Delete object.
				delete (CPrimitiveObject *)thisObject;
			}
#ifdef _DEBUG
			else assert(_FALSE);
#endif
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddModel
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveObject* CCompoundObject::addModel(CResourceManager* resourceManager,
											_INTEGER type,_FLOAT mass,
											const C4DVector3& scaling,
											const C4DVector3& rotation,
											const C4DVector3& position)
{
#ifdef _DEBUG
	assert(mass >= 0.0f);
	assert(resourceManager != _NULL);
	assert(scaling.x() > 0.0f && scaling.y() > 0.0f && scaling.z() > 0.0f);
#endif

	//Create object.
	CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set type.
	object->setPrimitiveType(type);
	//Select renderable.
	object->selectRenderable(resourceManager,type);
	//Set mass.
	object->setMass(mass);
	//Set scaling.
	object->setScale(scaling);
	//Set position.
	object->setPosition(position);
	//Set rotation.
	object->setEularRotation(rotation.x(),rotation.y(),rotation.z());
	//Add it into world.
	CWorldObject::addObject(object);
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveObject* CCompoundObject::createModel(CRenderableManager* renderableManager,
												const CPrimitiveAttribute& attribute,_FLOAT mass,
												const C4DVector3& scaling,
												const C4DVector3& rotation,
												const C4DVector3& position)
{
#ifdef _DEBUG
	assert(mass >= 0.0f);
	assert(renderableManager != _NULL);
	assert(scaling.x() > 0.0f && scaling.y() > 0.0f && scaling.z() > 0.0f);
#endif

	//Create object.
	CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set type.
	object->setPrimitiveAttribute(attribute);
	//Create renderable.
	CD3DXPrimitive* primitive = renderableManager->createPrimitive(attribute);
#ifdef _DEBUG
	assert(primitive != NULL);
#endif
	//Create renderable.
	object->setRenderable(primitive);
	//Set mass.
	object->setMass(mass);
	//Set scaling.
	object->setScale(scaling);
	//Set position.
	object->setPosition(position);
	//Set rotation.
	object->setEularRotation(rotation.x(),rotation.y(),rotation.z());
	//Add it into world.
	CWorldObject::addObject(object);
	//Return result.
	return object;
}
