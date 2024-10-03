///////////////////////////////////////////////////////////////////////////////
//
// CollisionMethod.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "CollisionMethod.h"
#include "ConstValue.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DX10Math.h"

////////////////////////////////////////////////////////////////////////////////
//
// XNA
//
////////////////////////////////////////////////////////////////////////////////

#include <xnamath.h>

#include "xnaCollision.h"
using namespace XNA;

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Status 
const _INTEGER CCollisionMethod::unknow							= 0x00000;
const _INTEGER CCollisionMethod::inside							= 0x10000;
const _INTEGER CCollisionMethod::contact						= 0x20000;
const _INTEGER CCollisionMethod::depature						= 0x30000;
const _INTEGER CCollisionMethod::intersect						= 0x40000;

///////////////////////////////////////////////////////////////////////////////
//
// CCollisionMethod
//
///////////////////////////////////////////////////////////////////////////////

CCollisionMethod::CCollisionMethod(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ~CCollisionMethod
//
///////////////////////////////////////////////////////////////////////////////

CCollisionMethod::~CCollisionMethod(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Collision1
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision1(CSimpleBox* b1,CSimpleBox* b2)
{
#ifdef _DEBUG
	assert(b1 != _NULL && b2 != _NULL);
#endif
	//Box
	AxisAlignedBox box1, box2;
	//Set values.
	box1.Center.x = b1->x();
	box1.Center.y = b1->y();
	box1.Center.z = b1->z();
	box1.Extents.x = b1->dx();
	box1.Extents.y = b1->dy();
	box1.Extents.z = b1->dz();
	//Set values.
	box2.Center.x = b2->x();
	box2.Center.y = b2->y();
	box2.Center.z = b2->z();
	box2.Extents.x = b2->dx();
	box2.Extents.y = b2->dy();
	box2.Extents.z = b2->dz();
	//Return result.
	return IntersectAxisAlignedBoxAxisAlignedBox(&box1,&box2) ?
		CCollisionMethod::intersect : CCollisionMethod::depature;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision2
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision2(CSimpleBox* b1,CSimpleBox* b2)
{
#ifdef _DEBUG
	assert(b1 != _NULL && b2 != _NULL);
#endif

	//Check result.
	if(fabs(b1->x() - b2->x()) > b1->dx() + b2->dx()) return CCollisionMethod::depature;
	if(fabs(b1->y() - b2->y()) > b1->dy() + b2->dy()) return CCollisionMethod::depature;
	if(fabs(b1->z() - b2->z()) > b1->dz() + b2->dz()) return CCollisionMethod::depature;
	//Return result.
	return CCollisionMethod::intersect;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision1
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision1(CSimpleSphere* s1,CSimpleSphere* s2)
{
#ifdef _DEBUG
	assert(s1 != _NULL && s2 != _NULL);
#endif

	//Sphere.
	Sphere sphere1, sphere2;
	//Set values.
	sphere1.Radius = s1->r();
	sphere1.Center.x = s1->x();
	sphere1.Center.y = s1->y();
	sphere1.Center.z = s1->z();
	//Set values.
	sphere2.Radius = s2->r();
	sphere2.Center.x = s2->x();
	sphere2.Center.y = s2->y();
	sphere2.Center.z = s2->z();

	//Return result.
	return IntersectSphereSphere(&sphere1,&sphere2) ?
		CCollisionMethod::intersect : CCollisionMethod::depature;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision2
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision2(CSimpleSphere* s1,CSimpleSphere* s2)
{
#ifdef _DEBUG
	assert(s1 != _NULL && s2 != _NULL);
#endif

	//Get values.
	_FLOAT sumRadius = s1->r() + s2->r();
	
	//Get dx.
	_FLOAT dx = fabs(s1->x() - s2->x());
	//Check result.
	if(dx > sumRadius) return CCollisionMethod::depature;

	//Get dy.
	_FLOAT dy = fabs(s1->y() - s2->y());
	//Check result.
	if(dy > sumRadius) return CCollisionMethod::depature;

	//Get dz.
	_FLOAT dz = fabs(s1->z() - s2->z());
	//Check result.
	if(dz > sumRadius) return CCollisionMethod::depature;

	//ABS((A1 + A2 + ... + An) / n ) < SQRT((A1 * A1 + A2 * A2 + ... + An * An) / n)
	_FLOAT pseudoDistance = (dx + dy + dz) * (_FLOAT)_RECIPROC_SQRT3;
	//Check result.
	//Pseudo distance is bigger
	if(pseudoDistance > sumRadius) return CCollisionMethod::depature;

	//Square distance.
	_FLOAT squareDistance = 0.0f;
	//Square radius.
	_FLOAT squareRadius = sumRadius * sumRadius;

	//Get square distance.
	squareDistance += dx * dx;
	//Check result.
	if(squareDistance > squareRadius) return CCollisionMethod::depature;

	//Get square distance.
	squareDistance += dy * dy;
	//Check result.
	if(squareDistance > squareRadius) return CCollisionMethod::depature;

	//Get square distance.
	squareDistance += dz * dz;
	//Check result.
	if(squareDistance > squareRadius) return CCollisionMethod::depature;

	//Set result
	return CCollisionMethod::intersect;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision2
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision2(CMultiBoxObject* o1,CMultiBoxObject* o2)
{
	//Result.
	_INTEGER result;

#ifdef _DEBUG
	assert(o1 != _NULL && o2 != _NULL);
#endif

	//Get result.
	result = collision1(o1,o2);
	//Check result.
	if(result == CCollisionMethod::depature) return result;

	//Do while.
	for(_INTEGER i = 0;i < o1->getCount();i ++)
	{
		//Get object.
		CBoxObject* pObject = o1->getObject(i);
#ifdef _DEBUG
		assert(pObject != _NULL);
#endif
		//Clear result.
		result = CCollisionMethod::depature;
		//Check object.
		if(!pObject->isSingle())
		{
			//Do it recursively.
			result = collision2((CMultiBoxObject *)pObject,o2);
		}
		else
		{
			//Get result.
			result = collision2(o2,(CSingleBoxObject *)pObject);
		}
		//Check result.
		if(result == CCollisionMethod::intersect) return result;
	}
	//Return result.
	return CCollisionMethod::depature;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision2
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CCollisionMethod::collision2(CMultiBoxObject* o1,CSingleBoxObject* o2)
{
	//Result.
	_INTEGER result;

#ifdef _DEBUG
	assert(o1 != _NULL && o2 != _NULL);
#endif

	//Get result.
	result = collision1(o1,o2);
	//Check result.
	if(result == CCollisionMethod::depature) result;

	//Do while.
	for(_INTEGER i = 0;i < o1->getCount();i ++)
	{
		//Get object.
		CBoxObject* pObject = o1->getObject(i);
#ifdef _DEBUG
		assert(pObject != _NULL);
#endif
		//Clear result.
		result = CCollisionMethod::depature;
		//Check object.
		if(!pObject->isSingle())
		{
			//Do it recursively.
			result = collision2((CMultiBoxObject *)pObject,o2);
		}
		else
		{
			//Get result.
			result = collision2((CSingleBoxObject *)pObject,o2);
		}
		//Check result.
		if(result == CCollisionMethod::intersect) return result;
	}
	//Set result.
	return CCollisionMethod::depature;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision2
//
///////////////////////////////////////////////////////////////////////////////
	
_INTEGER CCollisionMethod::collision2(CSingleBoxObject* o1,CSingleBoxObject* o2)
{
	//Return result.
	return collision1(o1,o2);
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision1
//
///////////////////////////////////////////////////////////////////////////////
	
_INTEGER CCollisionMethod::collision1(CBoxObject* o1,CBoxObject* o2)
{
	//Result.
	_INTEGER result;

#ifdef _DEBUG
	assert(o1 != _NULL && o2 != _NULL);
#endif

	//Get box.
	CSimpleBox* b1 = o1->getBox();
#ifdef _DEBUG
	assert(b1 != _NULL);
#endif
	//Get box
	CSimpleBox* b2 = o2->getBox();
#ifdef _DEBUG
	assert(b2 != _NULL);
#endif
	//Check box.
	result = collision2(b1,b2);
	//Check result.
	if(result == CCollisionMethod::depature) return result;

	//Get sphere.
	CSimpleSphere* s1 = o1->getSphere();
#ifdef _DEBUG
	assert(s1 != _NULL);
#endif
	//Get sphere.
	CSimpleSphere* s2 = o2->getSphere();
#ifdef _DEBUG
	assert(s2 != _NULL);
#endif
	//Check sphere.
	result = collision2(s1,s2);
	//Check result.
	if(result == CCollisionMethod::depature) return result;

	//Return intersect.
	return CCollisionMethod::intersect;
}

///////////////////////////////////////////////////////////////////////////////
//
// Collision1
//
///////////////////////////////////////////////////////////////////////////////
	
_INTEGER CCollisionMethod::collision3(CBoxObject* o1,CBoxObject* o2)
{
#ifdef _DEBUG
	assert(o1 != _NULL && o2 != _NULL);
#endif

	//Check result.
	if(o1->isSingle())
	{
		if(o2->isSingle())
		{
			//Return result.
			return collision2((CSingleBoxObject *)o1,(CSingleBoxObject *)o2);
		}
		else
		{
			//Return result.
			return collision2((CMultiBoxObject *)o2,(CSingleBoxObject *)o1);
		}
	}
	else
	{
		if(o2->isSingle())
		{
			//Return result.
			return collision2((CMultiBoxObject *)o1,(CSingleBoxObject *)o2);
		}
		else
		{
			//Return result.
			return collision2((CMultiBoxObject *)o1,(CMultiBoxObject *)o2);
		}
	}
}
