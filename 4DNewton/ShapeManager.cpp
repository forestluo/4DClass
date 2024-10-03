///////////////////////////////////////////////////////////////////////////////
//
// ShapeManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ShapeManager.h"
#include "ConstValue.h"
#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAX_COMPOUND_SIZE									256
#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))
#define COLLISION_SHAPE(p)									((const NewtonCollision *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CShapeManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CShapeManager::CShapeManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CShapeManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CShapeManager::~CShapeManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// DestroyShape
//
///////////////////////////////////////////////////////////////////////////////
	
void CShapeManager::destroyShape(_OBJECT collisionShape)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(collisionShape != _NULL);
#endif
	//Release shape.
	::NewtonReleaseCollision(WORLD_INSTANCE(world),COLLISION_SHAPE(collisionShape));
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCompoundShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createCompoundShape(CListNodeContainer& shapes)
{
	//Collision shapes.
	NewtonCollision* collisionShapes[MAX_COMPOUND_SIZE];
	//Clear all collision shapes.
	for(_INTEGER i = 0;i < MAX_COMPOUND_SIZE;i ++)
	{
		//Clear collision shapes.
		collisionShapes[i] = (NewtonCollision *)_NULL;
	}

	//Get count.
	_INTEGER count = shapes.getCount();
#ifdef _DEBUG
	assert(count > 0 && count <= MAX_COMPOUND_SIZE);
#endif
	//Enumeration.
	CListNodeEnumeration iterator;
	//Get enumeration.
	shapes.getEnumeration(&iterator);
	//Do while.
	for(_INTEGER i = 0;i < count && iterator.hasMoreElements();i ++)
	{
		//Get shape.
		_OBJECT shape = iterator.nextElement();
#ifdef _DEBUG
		assert(shape != _NULL);
#endif
		//Set collision shapes.
		collisionShapes[i] = (NewtonCollision *)shape;
	}
	//Return result.
	return ::NewtonCreateCompoundCollision(WORLD_INSTANCE(world),count,collisionShapes,0);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateBoxShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createBoxShape(_FLOAT dx,_FLOAT dy,_FLOAT dz)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(dx > 0.0f && dy > 0.0f && dz > 0.0f);
#endif
	//Get result.
	return ::NewtonCreateBox(WORLD_INSTANCE(world),dx,dy,dz,0,NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateConeShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createConeShape(_FLOAT r,_FLOAT h)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Return result.
	return ::NewtonCreateCone(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCylinderShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createCylinderShape(_FLOAT r,_FLOAT h)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Return result.
	return ::NewtonCreateCylinder(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCapsuleShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createCapsuleShape(_FLOAT r,_FLOAT h)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h >= r);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Return result.
	return ::NewtonCreateCapsule(WORLD_INSTANCE(world),r,2 * r + h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateChamferCylinderShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createChamferCylinderShape(_FLOAT r,_FLOAT h)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Return result.
	return ::NewtonCreateChamferCylinder(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateSphereShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createSphereShape(_FLOAT rx,_FLOAT ry,_FLOAT rz)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(rx > 0.0f && ry > 0.0f && rz > 0.0f);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Return result.
	return ::NewtonCreateSphere(WORLD_INSTANCE(world),rx,ry,rz,0,NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateConvexShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createConvexShape(_INTEGER count,const _FLOAT* vertices)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(vertices != _NULL && count >= 4);
#endif
	//Position.
	dVector vector(0.0f,0.0f,0.0f,1.0f);
	//Calculate rotation.
	dMatrix offset(0.0f,0.0f,(float)_PI / 2.0f,vector);
	//Now create a convex hull shape from the vertex geometry.
	return ::NewtonCreateConvexHull(WORLD_INSTANCE(world),count,&vertices[0],sizeof(_FLOAT3),0.0001f,0,NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateBoxShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createBoxShape(_FLOAT dx,_FLOAT dy,_FLOAT dz,const C4DMatrix4& matrix)
{
#ifdef _DEBUG
	assert(world != _NULL);
	assert(dx > 0.0f && dy > 0.0f && dz > 0.0f);
#endif
	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Get result.
	return ::NewtonCreateBox(WORLD_INSTANCE(world),dx,dy,dz,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateConeShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createConeShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Return result.
	return ::NewtonCreateCone(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCapsuleShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createCapsuleShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h >= r);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Return result.
	return ::NewtonCreateCapsule(WORLD_INSTANCE(world),r,2 * r + h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateChamferCylinderShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createChamferCylinderShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Return result.
	return ::NewtonCreateChamferCylinder(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateCylinderShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createCylinderShape(_FLOAT r,_FLOAT h,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(r > 0.0f && h > 0.0f);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Return result.
	return ::NewtonCreateCylinder(WORLD_INSTANCE(world),r,h,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateSphereShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createSphereShape(_FLOAT rx,_FLOAT ry,_FLOAT rz,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(rx > 0.0f && ry > 0.0f && rz > 0.0f);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Return result.
	return ::NewtonCreateSphere(WORLD_INSTANCE(world),rx,ry,rz,0,NULL);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateConvexShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createConvexShape(_INTEGER count,const _FLOAT* vertices,const C4DMatrix4& matrix)
{
	//Local matrix.
	C4DMatrix4 localMatrix;
	//Rotate.
	localMatrix.rotate(C4DQuaternion(C4DVector3(0.0f,0.0f,(_FLOAT)_PI / 2.0f)));
	//Adjust.
	localMatrix *= matrix;

#ifdef _DEBUG
	assert(world != _NULL);
	assert(vertices != _NULL && count >= 4);
#endif

	//Calculate offset.
	dMatrix offset;
	//Copy matrix.
	for(int i = 0;i < 4;i ++)
	{
		//Copy matrix.
		for(int j = 0;j < 4;j ++) offset[i][j] = matrix(i,j);
	}
	//Now create a convex hull shape from the vertex geometry.
	return ::NewtonCreateConvexHull(WORLD_INSTANCE(world),count,&vertices[0],sizeof(_FLOAT3),0.0001f,0,&offset[0][0]);
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateMeshShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createMeshShape(_INTEGER count,_SHORT* indices,_FLOAT* vertices)
{
	//Now create and empty collision tree.
	NewtonCollision* collision = NewtonCreateTreeCollision(WORLD_INSTANCE(world),0);
#ifdef _DEBUG
	assert(collision != _NULL);
#endif
	//Start adding faces to the collision tree.
	NewtonTreeCollisionBeginBuild(collision);
	//Step over the collision geometry and add all faces to the collision tree.
	for(_INTEGER i = 0;i < count;i += 3)
	{
		//Get index.
		_INTEGER i0 = indices[i + 0] & 0xffff;
		_INTEGER i1 = indices[i + 1] & 0xffff;
		_INTEGER i2 = indices[i + 2] & 0xffff;
		//Add each sub mesh as a face id, will will sue this later for a multi material sound effect in and advanced tutorial.
		dVector face[3];
		//Set point.
		face[0] = dVector(vertices[3 * i0 + 0],vertices[3 * i0 + 1],vertices[3 * i0 + 2]);
		face[1] = dVector(vertices[3 * i1 + 0],vertices[3 * i1 + 1],vertices[3 * i1 + 2]);
		face[2] = dVector(vertices[3 * i2 + 0],vertices[3 * i2 + 1],vertices[3 * i2 + 2]);
		//Add index.
		NewtonTreeCollisionAddFace(collision,3,&face[0].m_x,sizeof(dVector),i / 3 + 1);
	}
	//End adding faces to the collision tree, also optimize the mesh for best performance.
	NewtonTreeCollisionEndBuild(collision,1);
	//Return result.
	return collision;
}

///////////////////////////////////////////////////////////////////////////////
//
// CreateConvexShape
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CShapeManager::createHeightFieldShape(_INTEGER rows,_INTEGER columns,_FLOAT quadWidth,_FLOAT quadHeight,_FLOAT* vertices)
{
	//Max attributes.
	char attributes[641 * 481];
	//Max elevations.
	unsigned short elevations[641 * 481];
#ifdef _DEBUG
	assert(vertices != _NULL);
	assert(rows > 0 && columns > 0);
	assert(rows <= 480 && columns <= 640);
	assert(quadWidth > 0.0f && quadHeight > 0.0f);
#endif
	//Clear attributes.
	memset(attributes,1,641 * 481 * sizeof(char));
	//Clear elevations.
	memset(elevations,0,641 * 481 * sizeof(unsigned short));
	//Do while.
	for(_INTEGER i = 0;i < rows + 1;i ++)
	{
		//Do while.
		for(_INTEGER j = 0;j < columns + 1;j ++)
		{
			//Get index.
			_INTEGER index = i * columns + j;

			//Get height value.
			_FLOAT height = vertices[3 * index + 1];
#ifdef _DEBUG
			assert(height >= 0.0f);
#endif
			//Get height value.
			elevations[index] = (unsigned short)(height / quadHeight);
		}
	}
	//Return result.
	return ::NewtonCreateHeightFieldCollision(WORLD_INSTANCE(world),columns + 1,rows + 1,1,(unsigned short *)elevations,(char *)attributes,quadWidth,quadHeight,0);
}
