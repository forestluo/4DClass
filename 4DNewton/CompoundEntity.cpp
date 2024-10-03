///////////////////////////////////////////////////////////////////////////////
//
// CompoundEntity.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundEntity.h"

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundEntity::CCompoundEntity(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundEntity
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundEntity::CCompoundEntity(_FLOAT mass)
	: CPhysicsEntity(mass)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CCompoundEntity
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CCompoundEntity::~CCompoundEntity(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateShape
//
/////////////////////////////////////////////////////////////////////////////////

_OBJECT CCompoundEntity::createShape(CPhysicsManager *manager,CListNodeContainer& shapes)
{
	//Get matrix.
	C4DMatrix4 matrix;
	//Identify.
	matrix.identity();

#ifdef _DEBUG
	assert(manager != _NULL);
	assert(object != _NULL && object->isCompoundObject());
#endif

	//Iterator.
	CListNodeEnumeration iterator;
	//Get enumeration.
	object->getEnumeration(iterator);
	//Do while.
	while(iterator.hasMoreElements())
	{
		//Get object.
		CWorldObject* worldObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
		assert(worldObject != _NULL && !worldObject->isJointObject());
#endif
		//Create shape recursively.
		if(worldObject->isPhysicsObject()) createShapes(manager,worldObject,shapes,matrix);
	}
	//Get count.
	_INTEGER count = shapes.getCount();
	//Check count.
	//If there is no shapes, so there is no collision.
	if(count <= 0) return _NULL;
	//Now create a compound collision for this entity.
	return manager->createCompoundShape(shapes);
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateShapes
//
/////////////////////////////////////////////////////////////////////////////////

void CCompoundEntity::createShapes(CPhysicsManager* manager,CWorldObject* object,
									CListNodeContainer& shapes,const C4DMatrix4& matrix)
{
#ifdef _DEBUG
	assert(manager != _NULL);
	assert(object != _NULL && !object->isJointObject());
#endif
	//Check object.
	//It is not a physics object.
	if(!object->isPhysicsObject()) return;
	//Get physics object.
	CPhysicsObject* physicsObject = (CPhysicsObject *)object->getPhysics();
#ifdef _DEBUG
	assert(physicsObject != _NULL);
#endif
	//Check object.
	if(object->isCompoundObject())
	{
		//World matrix.
		C4DMatrix4 worldMatrix;
		//Get world matrix.
		object->initializeMatrix(worldMatrix);

		//Iterator.
		CListNodeEnumeration iterator;
		//Get enumeration.
		object->getEnumeration(iterator);
		//Do while.
		while(iterator.hasMoreElements())
		{
			//Get object.
			CWorldObject* worldObject = (CWorldObject *)iterator.nextElement();
#ifdef _DEBUG
			assert(worldObject != _NULL && !worldObject->isJointObject());
#endif
			//Create shape recursively.
			if(worldObject->isPhysicsObject()) createShapes(manager,worldObject,shapes,worldMatrix);
		}
	}
	//Check type of object.
	else if(object->isPrimitiveObject())
	{
		//World matrix.
		C4DMatrix4 worldMatrix = matrix;
		//Add rotation.
		{
			//Rotation matrix.
			C4DMatrix4 rotationMatrix;
			//Rotate.
			rotationMatrix.rotate(object->getRotation());
			//Multiply.
			worldMatrix *= rotationMatrix;
		}
		//Add position.
		{
			//Position matrix.
			C4DMatrix4 positionMatrix;
			//Get position.
			C4DVector3 position = object->getPosition();
			//Translate.
			positionMatrix.translate(position.x(),position.y(),position.z());
			//Multiply.
			worldMatrix *= positionMatrix;
		}
		//Get scale.
		//It is the dimension description of object.
		C4DVector3 scale = object->getScale();
#ifdef _DEBUG
		assert(scale.x() > 0.0f && scale.y() > 0.0f && scale.z() > 0.0f);
#endif
		//Get primitive attribute.
		CPrimitiveAttribute attribute = ((CPhysicsPrimitiveObject *)physicsObject)->getPrimitiveAttribute();

		//Shape.
		_OBJECT shape;
		//Get type of primitive.
		_INTEGER type = attribute.getType();
		//Check type of primitive.
		if(type == CPrimitiveAttribute::capsule0Primitive)
		{
			//Create shape.
			shape = manager->createCapsuleShape(attribute.primitiveData.capsule.radius * (scale.x() + scale.z()) / 2.0f,
													attribute.primitiveData.capsule.height * scale.y(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
		{
			//Create shape.
			shape = manager->createChamferCylinderShape(attribute.primitiveData.capsule.radius * (scale.x() + scale.z()) / 2.0f,
															attribute.primitiveData.capsule.height * scale.y(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::cone0Primitive)
		{
			//Create shape.
			shape = manager->createConeShape(attribute.primitiveData.cone.radius * (scale.x() + scale.z()) / 2.0f,
												attribute.primitiveData.cone.height * scale.y(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::cuboid0Primitive ||
				type == CPrimitiveAttribute::floor0Primitive)
		{
			//Create shape.
			shape = manager->createBoxShape(attribute.primitiveData.cuboid.width * scale.x(),
												attribute.primitiveData.cuboid.height * scale.y(),
												attribute.primitiveData.cuboid.depth * scale.z(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::cylinder0Primitive)
		{
			//Create shape.
			shape = manager->createCylinderShape(attribute.primitiveData.cylinder.radius * (scale.x() + scale.z()) / 2.0f,
													attribute.primitiveData.cylinder.height * scale.y(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::sphere0Primitive)
		{
			//Create shape.
			shape = manager->createSphereShape(attribute.primitiveData.sphere.radius * scale.x(),
												attribute.primitiveData.sphere.radius * scale.y(),
												attribute.primitiveData.sphere.radius * scale.z(),worldMatrix);
		}
		else if(type == CPrimitiveAttribute::cone3Primitive ||
				type == CPrimitiveAttribute::cone4Primitive ||
				type == CPrimitiveAttribute::cone6Primitive ||
				//Cylinder.
				type == CPrimitiveAttribute::cylinder3Primitive ||
				type == CPrimitiveAttribute::cylinder5Primitive ||
				type == CPrimitiveAttribute::cylinder6Primitive ||
				//Frustum
				type == CPrimitiveAttribute::frustum0Primitive ||
				type == CPrimitiveAttribute::frustum3Primitive ||
				type == CPrimitiveAttribute::frustum4Primitive ||
				type == CPrimitiveAttribute::frustum6Primitive ||
				//Hemisphere
				type == CPrimitiveAttribute::hemisphere0Primitive ||
				//Polygon
				type == CPrimitiveAttribute::polygon4Primitive ||
				type == CPrimitiveAttribute::polygon6Primitive ||
				type == CPrimitiveAttribute::polygon8Primitive ||
				type == CPrimitiveAttribute::polygon12Primitive ||
				type == CPrimitiveAttribute::polygon20Primitive)
		{
			//Vertex attribute.
			CVertexAttribute attribute;
			//Get vertex attribute.
			((CPhysicsPrimitiveObject *)physicsObject)->getVertexAttribute(attribute);
#ifdef _DEBUG
			assert(attribute.getVertexType() != CVertexAttribute::nullVertex);
#endif
			//Set vertex count.
			_INTEGER vertexCount = attribute.getVertexCount();
#ifdef _DEBUG
			assert(vertexCount >= 3);
#endif
			//Get vertex array.
			_FLOAT3* vertexArray = attribute.getFloat3Vertex();
#ifdef _DEBUG
			assert(vertexArray != _NULL);
#endif
			//Do while.
			for(_INTEGER i = 0;i < vertexCount;i ++)
			{
				//Set vertex.
				vertexArray[i][0] *= scale.x();
				vertexArray[i][1] *= scale.y();
				vertexArray[i][2] *= scale.z();
			}
			//Now create a collision convex for this entity.
			shape = manager->createConvexShape(vertexCount,(_FLOAT *)vertexArray);
		}
#ifdef _DEBUG
		assert(shape != _NULL);
#endif
		//Add it into list.
		shapes.addTail(shape);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
