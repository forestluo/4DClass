///////////////////////////////////////////////////////////////////////////////
//
// ModelManager.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ModelManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ResourceName.h"
#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CModelManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CModelManager::CModelManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CModelManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CModelManager::~CModelManager(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveObject* CModelManager::createModel(CResourceManager* resourceManager,
												const CNormalString& name)
{
#ifdef _DEBUG
	assert(name.length() > 0);
	assert(resourceManager != _NULL);
#endif

	//Create a object.
	CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Set primitive type according to the name.
	if(name == PRIMITIVE_TRIANGLE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::triangle0Primitive);
	}
	else if(name == PRIMITIVE_CIRCLE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::circle0Primitive);
	}
	else if(name == PRIMITIVE_CIRCLE3)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::circle3Primitive);
	}
	else if(name == PRIMITIVE_CIRCLE4)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::circle4Primitive);
	}
	else if(name == PRIMITIVE_CIRCLE5)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::circle5Primitive);
	}
	else if(name == PRIMITIVE_CIRCLE6)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::circle6Primitive);
	}
	else if(name == PRIMITIVE_POLYGON4)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::polygon4Primitive);
	}
	else if(name == PRIMITIVE_POLYGON6)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::polygon6Primitive);
	}
	else if(name == PRIMITIVE_POLYGON8)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::polygon8Primitive);
	}
	else if(name == PRIMITIVE_POLYGON12)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::polygon12Primitive);
	}
	else if(name == PRIMITIVE_POLYGON20)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::polygon20Primitive);
	}
	else if(name == PRIMITIVE_QUADRANGLE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::quadrangle0Primitive);
	}
	else if(name == PRIMITIVE_CUBOID0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cuboid0Primitive);
	}
	else if(name == PRIMITIVE_FLOOR0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::floor0Primitive);
	}
	else if(name == PRIMITIVE_CONE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cone0Primitive);
	}
	else if(name == PRIMITIVE_CONE3)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cone3Primitive);
	}
	else if(name == PRIMITIVE_CONE4)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cone4Primitive);
	}
	else if(name == PRIMITIVE_CONE6)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cone6Primitive);
	}
	else if(name == PRIMITIVE_CYLINDER0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cylinder0Primitive);
	}
	else if(name == PRIMITIVE_CYLINDER3)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cylinder3Primitive);
	}
	else if(name == PRIMITIVE_CYLINDER5)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cylinder5Primitive);
	}
	else if(name == PRIMITIVE_CYLINDER6)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::cylinder6Primitive);
	}
	else if(name == PRIMITIVE_FRUSTUM0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::frustum0Primitive);
	}
	else if(name == PRIMITIVE_FRUSTUM3)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::frustum3Primitive);
	}
	else if(name == PRIMITIVE_FRUSTUM4)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::frustum4Primitive);
	}
	else if(name == PRIMITIVE_FRUSTUM6)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::frustum6Primitive);
	}
	else if(name == PRIMITIVE_SPHERE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::sphere0Primitive);
	}
	else if(name == PRIMITIVE_HEMISPHERE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::hemisphere0Primitive);
	}
	else if(name == PRIMITIVE_CAPSULE0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::capsule0Primitive);
	}
	else if(name == PRIMITIVE_CHAMFERCYLINDER0)
	{
		//Set attribute.
		object->setPrimitiveType(CPrimitiveAttribute::chamferCylider0Primitive);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Select renderable.
	object->CD3DXPrimitiveObject::selectRenderable(resourceManager,name);
	//Add it into scene.
	CWorldGroup::addObject(object);
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveObject* CModelManager::createModel(CResourceManager* resourceManager,
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
	CWorldGroup::addObject(object);
	//Return result.
	return object;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateModel
//
///////////////////////////////////////////////////////////////////////////////

CPrimitiveObject* CModelManager::createModel(CRenderableManager* renderableManager,
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
	CWorldGroup::addObject(object);
	//Return result.
	return object;
}
