///////////////////////////////////////////////////////////////////////////////
//
// EntityManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "EntityManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NewtonPhysics.h"
#include "HashListContainer.h"

#include "BoxEntity.h"
#include "ConeEntity.h"
#include "MeshEntity.h"
#include "ConvexEntity.h"
#include "SphereEntity.h"
#include "CapsuleEntity.h"
#include "CylinderEntity.h"
#include "CompoundEntity.h"
#include "HeightFieldEntity.h"
#include "ChamferCylinderEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))
#define COLLISION_BODY(p)									((const NewtonBody *)(p))
#define COLLISION_SHAPE(p)									((const NewtonCollision *)(p))

#define ENTITIES_INSTANCE(p)								((CHashListContainer *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CEntityManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CEntityManager::CEntityManager(void)
{
	//Create entities.
	entities = new CHashListContainer();
#ifdef _DEBUG
	assert(entities != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CEntityManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CEntityManager::~CEntityManager(void)
{
	//Release all.
	releaseAll();
	//Check entities.
	if(entities != _NULL)
	{
		//Delete entities.
		delete (CHashListContainer *)entities;
		//Clear entities.
		entities = (CHashListContainer *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ReleaseAll
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::releaseAll()
{
	//Get enumeration.
	CListNodeEnumeration iterator;

#ifdef _DEBUG
	assert(entities != _NULL);
	assert(physicsManager != _NULL);
#endif

	//Get enumeration.
	ENTITIES_INSTANCE(entities)->getEnumeration(&iterator);
	//Do while
	while(iterator.hasMoreElements())
	{
		//Get element.
		_OBJECT value = iterator.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Detach object.
		((CPhysicsEntity *)value)->detachObject((CPhysicsManager *)physicsManager);
		//Delete entity.
		delete (CPhysicsEntity *)value;
	}
	//Clear all.
	ENTITIES_INSTANCE(entities)->clearAll();
}

///////////////////////////////////////////////////////////////////////////////
//
// RemoveEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::removeEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(entities != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Remove it from hash list.
	_OBJECT value = ENTITIES_INSTANCE(entities)->removeValue((_LONG)object);
	//Check result.
	if(value != _NULL)
	{
		//Detach object.
		((CPhysicsEntity *)value)->detachObject((CPhysicsManager *)physicsManager);
		//Delete entity.
		delete (CPhysicsEntity *)value;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// ParagramEnd
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::paragramEnd(_LONG timestamp)
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(entities != _NULL);
#endif
	//Get enumeration.
	ENTITIES_INSTANCE(entities)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsEntity *)value)->paragramEnd(timestamp);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsEnd
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::physicsEnd()
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(entities != _NULL);
#endif
	//Get enumeration.
	ENTITIES_INSTANCE(entities)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsEntity *)value)->physicsEnd();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// PhysicsBegin
//
///////////////////////////////////////////////////////////////////////////////
	
void CEntityManager::physicsBegin(_LONG timestamp)
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(entities != _NULL);
#endif
	//Get enumeration.
	ENTITIES_INSTANCE(entities)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsEntity *)value)->physicsBegin(timestamp);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// SetParagram
//
///////////////////////////////////////////////////////////////////////////////
	
void CEntityManager::setParagram(_FLOAT interpolationParam)
{
	//Enumeration.
	CListNodeEnumeration enumeration;
#ifdef _DEBUG
	assert(entities != _NULL);
#endif
	//Get enumeration.
	ENTITIES_INSTANCE(entities)->getEnumeration(&enumeration);
	//Do while
	while(enumeration.hasMoreElements())
	{
		//Get element.
		_OBJECT value = enumeration.nextElement();
#ifdef _DEBUG
		assert(value != _NULL);
#endif
		//Set paragram.
		((CPhysicsEntity *)value)->setParagram(interpolationParam);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCollisionBody
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CEntityManager::getCollisionBody(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(entities != _NULL);
#endif
	//Remove value from hash tree.
	CPhysicsEntity* entity = (CPhysicsEntity *)ENTITIES_INSTANCE(entities)->getValue((_LONG)object);
#ifdef _DEBUG
	assert(entity != _NULL);
#endif
	//Get collision body.
	return entity->getBody();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetForce
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::setForce(CPhysicsObject* object,const C4DVector3& force)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(entities != _NULL);
#endif
	//Remove value from hash tree.
	CPhysicsEntity* entity = (CPhysicsEntity *)ENTITIES_INSTANCE(entities)->getValue((_LONG)object);
#ifdef _DEBUG
	assert(entity != _NULL);
#endif
	//Set force.
	entity->setForce(force);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetVelocity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::setVelocity(CPhysicsObject* object,const C4DVector3& velocity)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(entities != _NULL);
#endif
	//Remove value from hash tree.
	CPhysicsEntity* entity = (CPhysicsEntity *)ENTITIES_INSTANCE(entities)->getValue((_LONG)object);
#ifdef _DEBUG
	assert(entity != _NULL);
#endif
	//Set velocity.
	entity->setVelocity(velocity);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPosition
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::setPosition(CPhysicsObject* object,const C4DVector3& position)
{
#ifdef _DEBUG
	assert(object != _NULL);
	assert(entities != _NULL);
#endif
	//Remove value from hash tree.
	CPhysicsEntity* entity = (CPhysicsEntity *)ENTITIES_INSTANCE(entities)->getValue((_LONG)object);
#ifdef _DEBUG
	assert(entity != _NULL);
#endif
	//Set position.
	entity->setPosition(position);
}

///////////////////////////////////////////////////////////////////////////////
//
// AddBoxEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addBoxEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CBoxEntity* entity = new CBoxEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddConeEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addConeEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CConeEntity* entity = new CConeEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddCapsuleEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addCapsuleEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CCapsuleEntity* entity = new CCapsuleEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddChamferCylinderEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addChamferCylinderEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CChamferCylinderEntity* entity = new CChamferCylinderEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddCylinderEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addCylinderEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CCylinderEntity* entity = new CCylinderEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddSphereEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addSphereEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CSphereEntity* entity = new CSphereEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != _NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddConvexEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addConvexEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CConvexEntity* entity = new CConvexEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddMeshEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addMeshEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CMeshEntity* entity = new CMeshEntity();
#ifdef _DEBUG
	assert(entity != NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// AddHeightFieldEntity
//
///////////////////////////////////////////////////////////////////////////////

void CEntityManager::addHeightFieldEntity(CPhysicsObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CHeightFieldEntity* entity = new CHeightFieldEntity();
#ifdef _DEBUG
	assert(entity != NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// AddEntity
//
////////////////////////////////////////////////////////////////////////////////

void CEntityManager::addEntity(CPhysicsCompoundObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Create entity.
	//With zero mass.
	CCompoundEntity* entity = new CCompoundEntity(object->getMass());
#ifdef _DEBUG
	assert(entity != NULL);
	assert(physicsManager != _NULL);
#endif
	//Attach it with object.
	if(entity->attachObject((CPhysicsManager *)physicsManager,object))
	{
#ifdef _DEBUG
		assert(entities != _NULL);
#endif
		//Add it into list.
		ENTITIES_INSTANCE(entities)->setValue((_LONG)object,(_OBJECT)entity);
	}
}

////////////////////////////////////////////////////////////////////////////////
//
// AddEntity
//
////////////////////////////////////////////////////////////////////////////////

void CEntityManager::addEntity(CPhysicsPrimitiveObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Get type.
	_INTEGER type = object->getPrimitiveType();
	//Check result.
	if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Add entity.
		addCapsuleEntity(object);
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Add entity.
		addChamferCylinderEntity(object);
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Add entity.
		addConeEntity(object);
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Add entity.
		addBoxEntity(object);
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Add entity.
		addBoxEntity(object);
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Add entity.
		addCylinderEntity(object);
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Add entity.
		addSphereEntity(object);
	}
	else if(type == CPrimitiveAttribute::cone3Primitive ||
			type == CPrimitiveAttribute::cone4Primitive ||
			type == CPrimitiveAttribute::cone6Primitive)
	{
		//Add entity.
		addConvexEntity(object);
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive ||
			type == CPrimitiveAttribute::cylinder5Primitive ||
			type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Add entity.
		addConvexEntity(object);
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive ||
			type == CPrimitiveAttribute::frustum3Primitive ||
			type == CPrimitiveAttribute::frustum4Primitive ||
			type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Add entity.
		addConvexEntity(object);
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Add entity.
		addConvexEntity(object);
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive ||
			type == CPrimitiveAttribute::polygon6Primitive ||
			type == CPrimitiveAttribute::polygon8Primitive ||
			type == CPrimitiveAttribute::polygon12Primitive ||
			type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Add entity.
		addConvexEntity(object);
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive ||
			type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Add entity.
		addMeshEntity(object);
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive ||
			type == CPrimitiveAttribute::ground320x240Primitive ||
			type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Add entity.
		addHeightFieldEntity(object);
	}
}