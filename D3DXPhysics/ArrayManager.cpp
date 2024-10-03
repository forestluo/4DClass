///////////////////////////////////////////////////////////////////////////////
//
// ArrayManager.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ArrayManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Type of floor.
const _INTEGER CArrayManager::xVerticalArray				= 1;
const _INTEGER CArrayManager::yVerticalArray				= 2;
const _INTEGER CArrayManager::zVerticalArray				= 3;

///////////////////////////////////////////////////////////////////////////////
//
// CArrayManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CArrayManager::CArrayManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CArrayManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CArrayManager::~CArrayManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CreateXVerticalFloor
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createXVerticalFloor(CResourceManager* resourceManager,
									_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
	//Position.
	C4DVector3 position;

#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Set height.
	position.x() = origin.x();
	//Do while.
	for(_INTEGER i = -row;i <= row;i ++)
	{
		//Set z.
		position.z() = origin.z() + i * (1.0f + 0.001f);
		//Do while.
		for(_INTEGER j = -column;j <= column;j ++)
		{
			//Set y.
			position.y() = origin.y() + j * (1.0f + 0.001f);

			//Create object.
			CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Set type.
			object->setPrimitiveType(CPrimitiveAttribute::floor0Primitive);
			//Select renderable.
			object->selectRenderable(resourceManager,CPrimitiveAttribute::floor0Primitive);

			//Set position.
			object->setPosition(position);
			//Set rotation.
			object->setEularRotation(0.0f,0.0f,(_FLOAT)D3DX_PI / 2.0f);

			//Add it into world.
			CWorldGroup::addObject(object);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateYVerticalFloor
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createYVerticalFloor(CResourceManager* resourceManager,
									_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
	//Position.
	C4DVector3 position;

#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Set height.
	position.y() = origin.y();
	//Do while.
	for(_INTEGER i = -row;i <= row;i ++)
	{
		//Set z.
		position.z() = origin.z() + i * (1.0f + 0.001f);
		//Do while.
		for(_INTEGER j = -column;j <= column;j ++)
		{
			//Set x.
			position.x() = origin.x() + j * (1.0f + 0.001f);

			//Create object.
			CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Set type.
			object->setPrimitiveType(CPrimitiveAttribute::floor0Primitive);
			//Select renderable.
			object->selectRenderable(resourceManager,CPrimitiveAttribute::floor0Primitive);

			//Set position.
			object->setPosition(position);

			//Add it into world.
			CWorldGroup::addObject(object);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateZVerticalFloor
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createZVerticalFloor(CResourceManager* resourceManager,
									_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
	//Position.
	C4DVector3 position;

#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Set height.
	position.z() = origin.z();
	//Do while.
	for(int i = -row;i <= row;i ++)
	{
		//Set x.
		position.x() = origin.x() + i * (1.0f + 0.001f);
		//Do while.
		for(int j = -column;j <= column;j ++)
		{
			//Set y.
			position.y() = origin.y() + j * (1.0f + 0.001f);

			//Create object.
			CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Set type.
			object->setPrimitiveType(CPrimitiveAttribute::floor0Primitive);
			//Select renderable.
			object->selectRenderable(resourceManager,CPrimitiveAttribute::floor0Primitive);

			//Set position.
			object->setPosition(position);
			//Set rotation.
			object->setEularRotation((_FLOAT)D3DX_PI / 2.0f,0.0f,0.0f);

			//Add it into world.
			CWorldGroup::addObject(object);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateFloor
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createFloor(CResourceManager* resourceManager,
								_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Check type.
	if(arrayType == CArrayManager::xVerticalArray)
	{
		//Create floor.
		createXVerticalFloor(resourceManager,row,column,origin);
	}
	else if(arrayType == CArrayManager::yVerticalArray)
	{
		//Create floor.
		createYVerticalFloor(resourceManager,row,column,origin);
	}
	else if(arrayType == CArrayManager::zVerticalArray)
	{
		//Create floor.
		createZVerticalFloor(resourceManager,row,column,origin);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateYVerticalBall
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createYVerticalBall(CResourceManager* resourceManager,
										_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
	//Position.
	C4DVector3 position;

#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Set height.
	position.y() = origin.y();
	//Do while.
	for(_INTEGER i = -row;i <= row;i ++)
	{
		//Set z.
		position.z() = origin.z() + i * (0.5f + 0.001f);
		//Do while.
		for(_INTEGER j = -column;j <= column;j ++)
		{
			//Set x.
			position.x() = origin.x() + j * (0.5f + 0.001f);

			//Create object.
			CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Set type.
			object->setPrimitiveType(CPrimitiveAttribute::sphere0Primitive);
			//Select renderable.
			object->selectRenderable(resourceManager,CPrimitiveAttribute::sphere0Primitive);

			//Set mass.
			object->setMass(1.0f);
			//Set position.
			object->setPosition(position);
			//Set scaling.
			object->setScale(0.2f,0.2f,0.2f);

			//Add it into world.
			CWorldGroup::addObject(object);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateSphereArray
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createSphereArray(CResourceManager* resourceManager,
										_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Check type.
	if(arrayType == CArrayManager::yVerticalArray)
	{
		//Create ball.
		createYVerticalBall(resourceManager,row,column,origin);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateYVerticalCuboid
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createYVerticalCuboid(CResourceManager* resourceManager,
											_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
	//Position.
	C4DVector3 position;

#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Set height.
	position.y() = origin.y();
	//Do while.
	for(_INTEGER i = -row;i <= row;i ++)
	{
		//Set z.
		position.z() = origin.z() + i * (0.4f + 0.001f);
		//Do while.
		for(_INTEGER j = -column;j <= column;j ++)
		{
			//Set x.
			position.x() = origin.x() + j * (0.4f + 0.001f);

			//Create object.
			CPrimitiveObject* object = new CPrimitiveObject();
#ifdef _DEBUG
			assert(object != _NULL);
#endif
			//Set type.
			object->setPrimitiveType(CPrimitiveAttribute::cuboid0Primitive);
			//Select renderable.
			object->selectRenderable(resourceManager,CPrimitiveAttribute::cuboid0Primitive);

			//Set mass.
			object->setMass(1.0f);
			//Set position.
			object->setPosition(position);
			//Set scaling.
			object->setScale(0.2f,0.2f,0.2f);

			//Add it into world.
			CWorldGroup::addObject(object);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCuboidArray
//
///////////////////////////////////////////////////////////////////////////////

void CArrayManager::createCuboidArray(CResourceManager* resourceManager,
										_INTEGER arrayType,_INTEGER row,_INTEGER column,const C4DVector3& origin)
{
#ifdef _DEBUG
	assert(row > 0 && column > 0);
	assert(resourceManager != _NULL);
#endif

	//Check type.
	if(arrayType == CArrayManager::yVerticalArray)
	{
		//Create cuboid.
		createYVerticalCuboid(resourceManager,row,column,origin);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
