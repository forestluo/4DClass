///////////////////////////////////////////////////////////////////////////////
//
// SimpleBox.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleBox.h"
#include "4DPrint.h"
#include "BoxRecycleBin.h"

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
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define RANDOM_RANGE										100.0f
#define RANDOM_EXTENT										50.0f

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

#pragma init_seg(".CRT$XCE")
//Recycle bin.
static CBoxRecycleBin boxBin;

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleBox
//
///////////////////////////////////////////////////////////////////////////////

CSimpleBox::CSimpleBox(void)
{
	//Set default value.
	center[0] = center[1] = center[2] = 0.0f;
	extents[0] = extents[1] = extents[2] = 0.0f;
}

///////////////////////////////////////////////////////////////////////////////
//
// CSimpleBox
//
///////////////////////////////////////////////////////////////////////////////

CSimpleBox::CSimpleBox(_FLOAT x,_FLOAT y,_FLOAT z,_FLOAT dx,_FLOAT dy,_FLOAT dz)
{
#ifdef _DEBUG
	assert(dx >= 0 && dy >= 0 && dz >= 0);
#endif
	//Set value.
	center[0] = x, center[1] = y, center[2] = z;
	extents[0] = dx, extents[1] = dy, extents[2] = dz;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CSimpleBox
//
///////////////////////////////////////////////////////////////////////////////

CSimpleBox::~CSimpleBox(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// X
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::x()
{
	//Return result.
	return center[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// X
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::x() const
{
	//Return result.
	return center[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Y
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::y()
{
	//Return result.
	return center[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Y
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::y() const
{
	//Return result.
	return center[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Z
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::z()
{
	//Return result.
	return center[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Z
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::z() const
{
	//Return result.
	return center[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dx
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::dx()
{
	//Return result.
	return extents[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dx
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::dx() const
{
	//Return result.
	return extents[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dy
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::dy()
{
	//Return result.
	return extents[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dy
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::dy() const
{
	//Return result.
	return extents[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dz
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT& CSimpleBox::dz()
{
	//Return result.
	return extents[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Dz
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::dz() const
{
	//Return result.
	return extents[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Xmin
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::xmin() const
{
	//Return result.
	return center[0] - extents[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Xmax
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::xmax() const
{
	//Return result.
	return center[0] + extents[0];
}

///////////////////////////////////////////////////////////////////////////////
//
// Ymin
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::ymin() const
{
	//Return result.
	return center[1] - extents[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// Ymax
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::ymax() const
{
	//Return result.
	return center[1] + extents[1];
}


///////////////////////////////////////////////////////////////////////////////
//
// Zmin
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::zmin() const
{
	//Return result.
	return center[2] - extents[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Zmax
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CSimpleBox::zmax() const
{
	//Return result.
	return center[2] + extents[2];
}

///////////////////////////////////////////////////////////////////////////////
//
// Normalize
//
///////////////////////////////////////////////////////////////////////////////
	
void CSimpleBox::normalize()
{
	//Set value.
	extents[0] = fabs(extents[0]);
	extents[1] = fabs(extents[1]);
	extents[2] = fabs(extents[2]);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetCenter
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT* CSimpleBox::getCenter()
{
	//Return result.
	return center;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetCenter
//
///////////////////////////////////////////////////////////////////////////////
	
void CSimpleBox::setCenter(_FLOAT* center)
{
#ifdef _DEBUG
	assert(center != _NULL);
#endif
	//Copy memory.
	memcpy(this->center,center,sizeof(_FLOAT3));
}

///////////////////////////////////////////////////////////////////////////////
//
// GetExtents
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT* CSimpleBox::getExtents()
{
	//Return result.
	return extents;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetExtend
//
///////////////////////////////////////////////////////////////////////////////
	
void CSimpleBox::setExtents(_FLOAT* extents)
{
#ifdef _DEBUG
	assert(extents != _NULL);
#endif
	//Copy memory.
	memcpy(this->extents,extents,sizeof(_FLOAT3));
}

///////////////////////////////////////////////////////////////////////////////
//
// Fuse
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleBox::fuse(const CSimpleBox* another)
{
	//Coordinates.
	D3DXVECTOR3 vCoordinates[16];

	vCoordinates[0].x = center[0] + extents[0];
	vCoordinates[0].y = center[1] + extents[1];
	vCoordinates[0].z = center[2] + extents[2];

	vCoordinates[1].x = center[0] + extents[0];
	vCoordinates[1].y = center[1] + extents[1];
	vCoordinates[1].z = center[2] - extents[2];

	vCoordinates[2].x = center[0] + extents[0];
	vCoordinates[2].y = center[1] - extents[1];
	vCoordinates[2].z = center[2] - extents[2];

	vCoordinates[3].x = center[0] - extents[0];
	vCoordinates[3].y = center[1] - extents[1];
	vCoordinates[3].z = center[2] - extents[2];

	vCoordinates[4].x = center[0] - extents[0];
	vCoordinates[4].y = center[1] - extents[1];
	vCoordinates[4].z = center[2] + extents[2];

	vCoordinates[5].x = center[0] - extents[0];
	vCoordinates[5].y = center[1] + extents[1];
	vCoordinates[5].z = center[2] + extents[2];

	vCoordinates[6].x = center[0] + extents[0];
	vCoordinates[6].y = center[1] - extents[1];
	vCoordinates[6].z = center[2] + extents[2];

	vCoordinates[7].x = center[0] - extents[0];
	vCoordinates[7].y = center[1] + extents[1];
	vCoordinates[7].z = center[2] - extents[2];

	{
#ifdef _DEBUG
		assert(another != _NULL);
#endif

		vCoordinates[8].x = another->center[0] + another->extents[0];
		vCoordinates[8].y = another->center[1] + another->extents[1];
		vCoordinates[8].z = another->center[2] + another->extents[2];

		vCoordinates[9].x = another->center[0] + another->extents[0];
		vCoordinates[9].y = another->center[1] + another->extents[1];
		vCoordinates[9].z = another->center[2] - another->extents[2];

		vCoordinates[10].x = another->center[0] + another->extents[0];
		vCoordinates[10].y = another->center[1] - another->extents[1];
		vCoordinates[10].z = another->center[2] - another->extents[2];

		vCoordinates[11].x = another->center[0] - another->extents[0];
		vCoordinates[11].y = another->center[1] - another->extents[1];
		vCoordinates[11].z = another->center[2] - another->extents[2];

		vCoordinates[12].x = another->center[0] - another->extents[0];
		vCoordinates[12].y = another->center[1] - another->extents[1];
		vCoordinates[12].z = another->center[2] + another->extents[2];

		vCoordinates[13].x = another->center[0] - another->extents[0];
		vCoordinates[13].y = another->center[1] + another->extents[1];
		vCoordinates[13].z = another->center[2] + another->extents[2];

		vCoordinates[14].x = another->center[0] + another->extents[0];
		vCoordinates[14].y = another->center[1] - another->extents[1];
		vCoordinates[14].z = another->center[2] + another->extents[2];

		vCoordinates[15].x = another->center[0] - another->extents[0];
		vCoordinates[15].y = another->center[1] + another->extents[1];
		vCoordinates[15].z = another->center[2] - another->extents[2];
	}

	//XNA box.
	AxisAlignedBox box;
	//Calculate AA box.
	ComputeBoundingAxisAlignedBoxFromPoints(&box,16,(XMFLOAT3 *)vCoordinates,sizeof(D3DXVECTOR3));
	//Set center.
	center[0] = box.Center.x, center[1] = box.Center.y, center[2] = box.Center.z;
	//Set extents.
	extents[0] = box.Extents.x, extents[1] = box.Extents.y, extents[2] = box.Extents.z;
}

///////////////////////////////////////////////////////////////////////////////
//
// Rand
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleBox::randBox(const CSimpleBox* box)
{
	//Check box.
	if(box == _NULL)
	{
		//Initialize center.
		x() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (2 * RANDOM_RANGE);
		y() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (2 * RANDOM_RANGE);
		z() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (2 * RANDOM_RANGE);
		//Initialize extents.
		dx() = (float)rand() / (RAND_MAX + 1) * RANDOM_EXTENT;
		dy() = (float)rand() / (RAND_MAX + 1) * RANDOM_EXTENT;
		dz() = (float)rand() / (RAND_MAX + 1) * RANDOM_EXTENT;
	}
	else
	{
		//Initialize extents.
		dx() = (float)rand() / (RAND_MAX + 1) * box->dx() / 2;
		dy() = (float)rand() / (RAND_MAX + 1) * box->dy() / 2;
		dz() = (float)rand() / (RAND_MAX + 1) * box->dz() / 2;

		//Initialize center.
		x() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (box->dx() - dx()) + box->x();
		y() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (box->dy() - dy()) + box->y();
		z() = (float)(rand() - RAND_MAX / 2) / (RAND_MAX + 1) * (box->dz() - dz()) + box->z();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// SetBox
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleBox::setBox(const CSimpleBox* origin,const C4DMatrix4* world)
{
	//Cooridinate.
	D3DXVECTOR3 vCoordinate;
	//Coordinates.
	D3DXVECTOR3 vCoordinates[8];

#ifdef _DEBUG
	assert(origin != _NULL && world != _NULL);
#endif

	vCoordinates[0].x = origin->center[0] + origin->extents[0];
	vCoordinates[0].y = origin->center[1] + origin->extents[1];
	vCoordinates[0].z = origin->center[2] + origin->extents[2];

	vCoordinates[1].x = origin->center[0] + origin->extents[0];
	vCoordinates[1].y = origin->center[1] + origin->extents[1];
	vCoordinates[1].z = origin->center[2] - origin->extents[2];

	vCoordinates[2].x = origin->center[0] + origin->extents[0];
	vCoordinates[2].y = origin->center[1] - origin->extents[1];
	vCoordinates[2].z = origin->center[2] - origin->extents[2];

	vCoordinates[3].x = origin->center[0] - origin->extents[0];
	vCoordinates[3].y = origin->center[1] - origin->extents[1];
	vCoordinates[3].z = origin->center[2] - origin->extents[2];

	vCoordinates[4].x = origin->center[0] - origin->extents[0];
	vCoordinates[4].y = origin->center[1] - origin->extents[1];
	vCoordinates[4].z = origin->center[2] + origin->extents[2];

	vCoordinates[5].x = origin->center[0] - origin->extents[0];
	vCoordinates[5].y = origin->center[1] + origin->extents[1];
	vCoordinates[5].z = origin->center[2] + origin->extents[2];

	vCoordinates[6].x = origin->center[0] + origin->extents[0];
	vCoordinates[6].y = origin->center[1] - origin->extents[1];
	vCoordinates[6].z = origin->center[2] + origin->extents[2];

	vCoordinates[7].x = origin->center[0] - origin->extents[0];
	vCoordinates[7].y = origin->center[1] + origin->extents[1];
	vCoordinates[7].z = origin->center[2] - origin->extents[2];

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

	//XNA box.
	AxisAlignedBox box;
	//Calculate AA box.
	ComputeBoundingAxisAlignedBoxFromPoints(&box,8,(XMFLOAT3 *)vCoordinates,sizeof(D3DXVECTOR3));
	//Set center.
	center[0] = box.Center.x, center[1] = box.Center.y, center[2] = box.Center.z;
	//Set extents.
	extents[0] = box.Extents.x, extents[1] = box.Extents.y, extents[2] = box.Extents.z;
}

///////////////////////////////////////////////////////////////////////////////
//
// Recycle
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleBox::recycle()
{
	//Recycle box.
	boxBin.recycle(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// Create
//
///////////////////////////////////////////////////////////////////////////////

CSimpleBox* CSimpleBox::create()
{
	//Return result.
	return (CSimpleBox *)boxBin.create();
}

///////////////////////////////////////////////////////////////////////////////
//
// Dump
//
///////////////////////////////////////////////////////////////////////////////

void CSimpleBox::dump()
{
	C4DPrint::printLine(stdout,L"CSimpleBox : show parameters !");
	C4DPrint::printLine(stdout,L"\tx = %f",x());
	C4DPrint::printLine(stdout,L"\ty = %f",y());
	C4DPrint::printLine(stdout,L"\tz = %f",z());
	C4DPrint::printLine(stdout,L"\tdx = %f",dx());
	C4DPrint::printLine(stdout,L"\tdy = %f",dy());
	C4DPrint::printLine(stdout,L"\tdz = %f",dz());
}