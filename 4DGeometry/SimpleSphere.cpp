///////////////////////////////////////////////////////////////////////////////
//
// SimpleSphere.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleSphere.h"
#include "4DPrint.h"
#include "SphereRecycleBin.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>

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

#pragma init_seg(".CRT$XCE")
//Recycle bin.
static CSphereRecycleBin sphereBin;

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleSphere
//
///////////////////////////////////////////////////////////////////////////////

CSimpleSphere::CSimpleSphere(void)
{
	//Set default value.
	radius = 0.0f;
	center[0] = center[1] = center[2] = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleSphere
//
///////////////////////////////////////////////////////////////////////////////

CSimpleSphere::CSimpleSphere(_FLOAT x,_FLOAT y,_FLOAT z,_FLOAT radius)
{
	//Set value.
	this->radius = radius;
	//Set value.
	center[0] = x, center[1] = y, center[2] = z;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CSimpleSphere
//
///////////////////////////////////////////////////////////////////////////////

CSimpleSphere::~CSimpleSphere(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// X
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleSphere::x()
{
	//Return result.
	return center[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// X
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleSphere::x() const
{
	//Return result.
	return center[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Y
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleSphere::y()
{
	//Return result.
	return center[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Y
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleSphere::y() const
{
	//Return result.
	return center[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Z
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleSphere::z()
{
	//Return result.
	return center[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Z
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleSphere::z() const
{
	//Return result.
	return center[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// R
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleSphere::r()
{
	//Return result.
	return radius;
}

///////////////////////////////////////////////////////////////////////////////
//
// R
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleSphere::r() const
{
	//Return result.
	return radius;
}

///////////////////////////////////////////////////////////////////////////////
//
// Normalize
//
///////////////////////////////////////////////////////////////////////////////
	
void CSimpleSphere::normalize()
{
	//Set value.
	radius = fabs(radius);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetRadius
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleSphere::getRadius()
{
	//Return result.
	return radius;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetRadius
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::setRadius(_FLOAT radius)
{
#ifdef _DEBUG
	assert(radius >= 0.0f);
#endif
	//Set radius.
	this->radius = radius;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCenter
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT* CSimpleSphere::getCenter()
{
	//Return result.
	return center;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetCenter
//
///////////////////////////////////////////////////////////////////////////////
	
void CSimpleSphere::setCenter(_FLOAT* center)
{
#ifdef _DEBUG
	assert(center != _NULL);
#endif
	//Copy memory.
	memcpy(this->center,center,sizeof(_FLOAT3));
}

///////////////////////////////////////////////////////////////////////////////
//
// Fuse
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::fuse(const CSimpleSphere* another)
{
	//Get center.
	D3DXVECTOR3 o1, o2;

#ifdef _DEBUG
	assert(another != _NULL);
#endif

	//Set center.
	o1.x = center[0], o1.y = center[1], o1.z = center[2];
	//Set center.
	o2.x = another->center[0], o2.y = another->center[1], o2.z = another->center[2];
	//Sub.
	D3DXVECTOR3 v = o2 - o1;
	//Get distance.
	float fDistance = D3DXVec3Length(&v);
	//Check result.
	if(fDistance <= fabs(radius - another->radius))
	{
		//Check result.
		if(radius < another->radius)
		{
			//Set new radius.
			radius = another->radius;
			//Set new center.
			memcpy(center,another->center,sizeof(_FLOAT3));
		}
	}
	else
	{
		//Get new center.
		v = (o1 + o2) / 2.0f + v * (another->radius - radius) / (2.0f * fDistance);

		//Set center.
		center[0] = v.x; center[0] = v.y; center[0] = v.z;
		//Set radius.
		radius = (fDistance + radius + another->radius) / 2.0f;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSphere
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::setSphere(const CSimpleSphere* origin,const C4DMatrix4* world)
{
	//Cooridinate.
	D3DXVECTOR3 vCoordinate;
	D3DXVECTOR3 vCoordinates[6];

#ifdef _DEBUG
	assert(origin != _NULL);
#endif

	//Get coordinates.
	vCoordinates[0].x = origin->center[0] + origin->radius;
	vCoordinates[0].y = origin->center[1];
	vCoordinates[0].z = origin->center[2];

	//Get coordinates.
	vCoordinates[1].x = origin->center[0];
	vCoordinates[1].y = origin->center[1] + origin->radius;
	vCoordinates[1].z = origin->center[2];

	//Get coordinates.
	vCoordinates[2].x = origin->center[0];
	vCoordinates[2].y = origin->center[1];
	vCoordinates[2].z = origin->center[2] + origin->radius;

	//Get coordinates.
	vCoordinates[3].x = origin->center[0] - origin->radius;
	vCoordinates[3].y = origin->center[1];
	vCoordinates[3].z = origin->center[2];

	//Get coordinates.
	vCoordinates[4].x = origin->center[0];
	vCoordinates[4].y = origin->center[1] - origin->radius;
	vCoordinates[4].z = origin->center[2];

	//Get coordinates.
	vCoordinates[5].x = origin->center[0];
	vCoordinates[5].y = origin->center[1];
	vCoordinates[5].z = origin->center[2] - origin->radius;

	//Check world.
	if(world != _NULL)
	{
		//Create matrix.
		D3DXMATRIX mWorld(*world);
		//Do while.
		for(_INTEGER i = 0;i < 6;i ++)
		{
			//Transform coordinates.
			D3DXVec3TransformCoord(&vCoordinate,&vCoordinates[i],&mWorld);
			//Set value.
			vCoordinates[i] = vCoordinate;
		}
	}
	//XNA sphere.
	Sphere sphere;
	//Calculate bounding sphere.
	ComputeBoundingSphereFromPoints(&sphere,6,(XMFLOAT3 *)vCoordinates,sizeof(D3DXVECTOR3));
	//Set radius.
	radius = sphere.Radius;
	//Set center.
	center[0] = sphere.Center.x, center[1] = sphere.Center.y, center[2] = sphere.Center.z;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSphere
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::setSphere(const CSimpleBox* origin,const C4DMatrix4* world)
{
	//Cooridinate.
	D3DXVECTOR3 vCoordinate;
	D3DXVECTOR3 vCoordinates[8];

#ifdef _DEBUG
	assert(origin != _NULL);
#endif

	vCoordinates[0].x = origin->x() + origin->dx();
	vCoordinates[0].y = origin->y() + origin->dy();
	vCoordinates[0].z = origin->z() + origin->dz();

	vCoordinates[1].x = origin->x() + origin->dx();
	vCoordinates[1].y = origin->y() + origin->dy();
	vCoordinates[1].z = origin->z() - origin->dz();

	vCoordinates[2].x = origin->x() + origin->dx();
	vCoordinates[2].y = origin->y() - origin->dy();
	vCoordinates[2].z = origin->z() - origin->dz();

	vCoordinates[3].x = origin->x() - origin->dx();
	vCoordinates[3].y = origin->y() - origin->dy();
	vCoordinates[3].z = origin->z() - origin->dz();

	vCoordinates[4].x = origin->x() - origin->dx();
	vCoordinates[4].y = origin->y() - origin->dy();
	vCoordinates[4].z = origin->z() + origin->dz();

	vCoordinates[5].x = origin->x() - origin->dx();
	vCoordinates[5].y = origin->y() + origin->dy();
	vCoordinates[5].z = origin->z() + origin->dz();

	vCoordinates[6].x = origin->x() + origin->dx();
	vCoordinates[6].y = origin->y() - origin->dy();
	vCoordinates[6].z = origin->z() + origin->dz();

	vCoordinates[7].x = origin->x() - origin->dx();
	vCoordinates[7].y = origin->y() + origin->dy();
	vCoordinates[7].z = origin->z() - origin->dz();

	//Check world.
	if(world != _NULL)
	{
		//Create matrix.
		D3DXMATRIX mWorld(*world);
		//Do while.
		for(_INTEGER i = 0;i < 8;i ++)
		{
			//Transform coordinates.
			D3DXVec3TransformCoord(&vCoordinate,&vCoordinates[i],&mWorld);
			//Set value.
			vCoordinates[i] = vCoordinate;
		}
	}
	//XNA sphere.
	Sphere sphere;
	//Calculate bounding sphere.
	ComputeBoundingSphereFromPoints(&sphere,8,(XMFLOAT3 *)vCoordinates,sizeof(D3DXVECTOR3));
	//Set radius.
	radius = sphere.Radius;
	//Set center.
	center[0] = sphere.Center.x, center[1] = sphere.Center.y, center[2] = sphere.Center.z;
}

///////////////////////////////////////////////////////////////////////////////
//
// Recycle
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::recycle()
{
	//Recycle sphere.
	sphereBin.recycle(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Create
//
///////////////////////////////////////////////////////////////////////////////

CSimpleSphere* CSimpleSphere::create()
{
	//Return result.
	return (CSimpleSphere *)sphereBin.create();
}

///////////////////////////////////////////////////////////////////////////////
//
// Dump
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleSphere::dump()
{
	C4DPrint::printLine(stdout,L"CSimpleSphere : show parameters !");
	C4DPrint::printLine(stdout,L"\tx = %f",x());
	C4DPrint::printLine(stdout,L"\ty = %f",y());
	C4DPrint::printLine(stdout,L"\tz = %f",z());
	C4DPrint::printLine(stdout,L"\tr = %f",r());
}