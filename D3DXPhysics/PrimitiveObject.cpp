///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "ResourceApplication.h"

#include "JointObject.h"
#include "CompoundObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveObject::CPrimitiveObject(void)
{
	//Set this.
	setThis(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveObject::~CPrimitiveObject(void)
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
// PhysicsEnd
//
///////////////////////////////////////////////////////////////////////////////
	
void CPrimitiveObject::physicsEnd()
{
	//Get keeper.
	CStatusKeeper* keeper = CPhysicsObject::getKeeper();
	//Check result.
	if(keeper != _NULL)
	{
		//Get controller.
		CObjectController* controller = CD3DXRenderableObject::getController();
		//Check result.
		if(controller != _NULL)
		{
			//Set rotation.
			controller->setRotation(keeper->getRotation());
		}
	}
	//Call function.
	CPhysicsObject::physicsEnd();
}

///////////////////////////////////////////////////////////////////////////////
//
// SelectRenderable
//
///////////////////////////////////////////////////////////////////////////////

void CPrimitiveObject::selectRenderable(CResourceManager* resourceManager,_INTEGER type)
{
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_TRIANGLE0);
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CIRCLE0);
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CIRCLE3);
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CIRCLE4);
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CIRCLE5);
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CIRCLE6);
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_POLYGON4);
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_POLYGON6);
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_POLYGON8);
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_POLYGON12);
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_POLYGON20);
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_QUADRANGLE0);
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CONE0);
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CONE3);
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CONE4);
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CONE6);
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CUBOID0);
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_FLOOR0);
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CAPSULE0);
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_FRUSTUM0);
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_FRUSTUM3);
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_FRUSTUM4);
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_FRUSTUM6);
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CYLINDER0);
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CYLINDER3);
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CYLINDER5);
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CYLINDER6);
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_SPHERE0);
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_HEMISPHERE0);
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Set model name.
		CD3DXPrimitiveObject::selectRenderable(resourceManager,PRIMITIVE_CHAMFERCYLINDER0);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
