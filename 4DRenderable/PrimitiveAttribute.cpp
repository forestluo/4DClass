///////////////////////////////////////////////////////////////////////////////
//
// PrimitiveAttribute.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

const _INTEGER CPrimitiveAttribute::nullPrimitive			= 0;
//Polygon
const _INTEGER CPrimitiveAttribute::polygon4Primitive		= 1;
const _INTEGER CPrimitiveAttribute::polygon6Primitive		= 2;
const _INTEGER CPrimitiveAttribute::polygon8Primitive		= 3;
const _INTEGER CPrimitiveAttribute::polygon12Primitive		= 4;
const _INTEGER CPrimitiveAttribute::polygon20Primitive		= 5;
//Circle
const _INTEGER CPrimitiveAttribute::circle0Primitive        = 6;
const _INTEGER CPrimitiveAttribute::circle3Primitive        = 7;
const _INTEGER CPrimitiveAttribute::circle4Primitive        = 8;
const _INTEGER CPrimitiveAttribute::circle5Primitive        = 9;
const _INTEGER CPrimitiveAttribute::circle6Primitive        = 10;
//Triangle
const _INTEGER CPrimitiveAttribute::triangle0Primitive		= 11;
//Quadrangle
const _INTEGER CPrimitiveAttribute::quadrangle0Primitive	= 12;
//Grid
const _INTEGER CPrimitiveAttribute::grid4x3Primitive		= 13;
const _INTEGER CPrimitiveAttribute::grid20x15Primitive		= 14;
const _INTEGER CPrimitiveAttribute::ground80x60Primitive	= 15;
const _INTEGER CPrimitiveAttribute::ground320x240Primitive	= 16;
const _INTEGER CPrimitiveAttribute::ground640x480Primitive	= 17;
//Cone
const _INTEGER CPrimitiveAttribute::cone0Primitive			= 18;
const _INTEGER CPrimitiveAttribute::cone3Primitive			= 19;
const _INTEGER CPrimitiveAttribute::cone4Primitive			= 20;
const _INTEGER CPrimitiveAttribute::cone6Primitive			= 21;
//Cylinder
const _INTEGER CPrimitiveAttribute::cylinder0Primitive		= 22;
const _INTEGER CPrimitiveAttribute::cylinder3Primitive		= 23;
const _INTEGER CPrimitiveAttribute::cylinder5Primitive		= 24;
const _INTEGER CPrimitiveAttribute::cylinder6Primitive		= 25;
//Cuboid
const _INTEGER CPrimitiveAttribute::floor0Primitive			= 26;
const _INTEGER CPrimitiveAttribute::cuboid0Primitive		= 27;
//Frustum
const _INTEGER CPrimitiveAttribute::frustum0Primitive		= 28;
const _INTEGER CPrimitiveAttribute::frustum3Primitive		= 29;
const _INTEGER CPrimitiveAttribute::frustum4Primitive		= 30;
const _INTEGER CPrimitiveAttribute::frustum6Primitive		= 31;
//Sphere
const _INTEGER CPrimitiveAttribute::sphere0Primitive		= 32;
const _INTEGER CPrimitiveAttribute::hemisphere0Primitive	= 33;
const _INTEGER CPrimitiveAttribute::capsule0Primitive		= 34;
const _INTEGER CPrimitiveAttribute::chamferCylider0Primitive= 35;

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute::CPrimitiveAttribute(void)
{
	//Set default type.
	type = nullPrimitive;
	//Set default value.
	rings = 0;
	//Set default value.
	segments = 0;
	//Clear data.
	memset(&primitiveData,0,sizeof(tagPrimitiveData));
}

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute::CPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
	//Copy primitive.
	copyPrimitive(attribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPrimitiveAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute::~CPrimitiveAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Operator
//
/////////////////////////////////////////////////////////////////////////////////

CPrimitiveAttribute& CPrimitiveAttribute::operator = (const CPrimitiveAttribute& attribute)
{
	//Copy primitive.
	copyPrimitive(attribute);
	//Return this.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPrimitiveAttribute::getType() const
{
	//Return result.
	return type;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetType
//
///////////////////////////////////////////////////////////////////////////////

void CPrimitiveAttribute::setType(_INTEGER type)
{
#ifdef _DEBUG
	assert(type >= 0 && type <= 35);
#endif
	//Set value.
	this->type = type;
}

///////////////////////////////////////////////////////////////////////////////
//
// CopyPrimitive
//
///////////////////////////////////////////////////////////////////////////////

void CPrimitiveAttribute::copyPrimitive(const CPrimitiveAttribute& attribute)
{
	//Set type.
	type = attribute.type;
	//Set rings.
	rings = attribute.rings;
	//Set segments.
	segments = attribute.segments;
	//Copy data.
	memcpy(&primitiveData,&attribute.primitiveData,sizeof(tagPrimitiveData));
}

///////////////////////////////////////////////////////////////////////////////
//
// IsEqual
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CPrimitiveAttribute::isEqual(const CPrimitiveAttribute& attribute) const
{
	//Set type.
	if(type != attribute.type) return _FALSE;
	//Check rings.
	if(rings != attribute.rings) return _FALSE;
	//Check segments.
	if(segments != attribute.segments) return _FALSE;
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.triangle,&attribute.primitiveData.triangle,
			sizeof(tagPrimitiveData::tagD3DXTriangle)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive ||
			type == CPrimitiveAttribute::grid20x15Primitive ||
			type == CPrimitiveAttribute::ground80x60Primitive ||
			type == CPrimitiveAttribute::ground320x240Primitive ||
			type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.grid,&attribute.primitiveData.grid,
			sizeof(tagPrimitiveData::tagD3DXGrid)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::circle0Primitive ||
			type == CPrimitiveAttribute::circle3Primitive ||
			type == CPrimitiveAttribute::circle4Primitive ||
			type == CPrimitiveAttribute::circle5Primitive ||
			type == CPrimitiveAttribute::circle6Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.circle,&attribute.primitiveData.circle,
			sizeof(tagPrimitiveData::tagD3DXCircle)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive ||
		type == CPrimitiveAttribute::polygon6Primitive ||
		type == CPrimitiveAttribute::polygon8Primitive ||
		type == CPrimitiveAttribute::polygon12Primitive ||
		type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.polygon,&attribute.primitiveData.polygon,
			sizeof(tagPrimitiveData::tagD3DXPolygon)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.quadrangle,&attribute.primitiveData.quadrangle,
			sizeof(tagPrimitiveData::tagD3DXQuadrangle)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::cone0Primitive ||
			type == CPrimitiveAttribute::cone3Primitive ||
			type == CPrimitiveAttribute::cone4Primitive ||
			type == CPrimitiveAttribute::cone6Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.cone,&attribute.primitiveData.cone,
			sizeof(tagPrimitiveData::tagD3DXCone)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive ||
			type == CPrimitiveAttribute::floor0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.cuboid,&attribute.primitiveData.cuboid,
			sizeof(tagPrimitiveData::tagD3DXCuboid)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.capsule,&attribute.primitiveData.capsule,
			sizeof(tagPrimitiveData::tagD3DXCapsule)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.chamferCylinder,&attribute.primitiveData.chamferCylinder,
			sizeof(tagPrimitiveData::tagD3DXChamferCylinder)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive ||
			type == CPrimitiveAttribute::frustum3Primitive ||
			type == CPrimitiveAttribute::frustum4Primitive ||
			type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.frustum,&attribute.primitiveData.frustum,
			sizeof(tagPrimitiveData::tagD3DXFrustum)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive ||
			type == CPrimitiveAttribute::cylinder3Primitive ||
			type == CPrimitiveAttribute::cylinder5Primitive ||
			type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.cylinder,&attribute.primitiveData.cylinder,
			sizeof(tagPrimitiveData::tagD3DXCylinder)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.sphere,&attribute.primitiveData.sphere,
			sizeof(tagPrimitiveData::tagD3DXSphere)) == 0 ? _TRUE : _FALSE;
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Return result.
		return memcmp(&primitiveData.hemisphere,&attribute.primitiveData.hemisphere,
			sizeof(tagPrimitiveData::tagD3DXHemisphere)) == 0 ? _TRUE : _FALSE;
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return true.
	return _FALSE;
}
