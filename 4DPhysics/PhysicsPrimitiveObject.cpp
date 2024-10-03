///////////////////////////////////////////////////////////////////////////////
//
// PhysicsPrimitiveObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsPrimitiveObject.h"

#include "GridAttribute.h"
#include "ConeAttribute.h"
#include "SliceAttribute.h"
#include "CuboidAttribute.h"
#include "CircleAttribute.h"
#include "SphereAttribute.h"
#include "PolygonAttribute.h"
#include "CapsuleAttribute.h"
#include "FrustumAttribute.h"
#include "CylinderAttribute.h"
#include "TriangleAttribute.h"
#include "QuadrangleAttribute.h"
#include "HemisphereAttribute.h"
#include "ChamferCylinderAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsPrimitiveObject
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsPrimitiveObject::CPhysicsPrimitiveObject(void)
{
	//Set this.
	setThis(this);
	//Set object type.
	setObjectType(CTypeAttribute::primitiveObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsPrimitiveObject
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsPrimitiveObject::~CPhysicsPrimitiveObject(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CopyRenderable
//
/////////////////////////////////////////////////////////////////////////////////
	
void CPhysicsPrimitiveObject::copyRenderable(const CRenderableAttribute& attribute)
{
#ifdef _DEBUG
	assert(getPrimitiveType() == CPrimitiveAttribute::nullPrimitive);
#endif
	//Get box attribute.
	CBoxAttribute boxAttribute = attribute.getBoxAttribute();
	//Get primitive attribute.
	CPrimitiveAttribute primitiveAttribute = attribute.getPrimitiveAttribute();
#ifdef _DEBUG
	assert(primitiveAttribute.getType() != CPrimitiveAttribute::nullPrimitive);
#endif
	//Copy box.
	CBoxAttribute::copyBox(boxAttribute);
	//Copy attribute.
	CPrimitiveAttribute::copyPrimitive(primitiveAttribute);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CPhysicsPrimitiveObject::getPrimitiveType() const
{
	//Return result.
	return CPrimitiveAttribute::getType();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveType
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsPrimitiveObject::setPrimitiveType(_INTEGER type)
{
#ifdef _DEBUG
	assert(getPrimitiveType() == CPrimitiveAttribute::nullPrimitive);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Set alias.
		setAlias(L"三角形（",L"）");
		//Copy primitive.
		copyRenderable(CTriangleAttribute::triangle0);
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Set alias.
		setAlias(L"网格（",L"）");
		//Copy primitive.
		copyRenderable(CGridAttribute::grid4x3);
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Set alias.
		setAlias(L"网格（",L"）");
		//Copy primitive.
		copyRenderable(CGridAttribute::grid20x15);
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Copy primitive.
		copyRenderable(CGridAttribute::ground80x60);
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Copy primitive.
		copyRenderable(CGridAttribute::ground320x240);
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Copy primitive.
		copyRenderable(CGridAttribute::ground640x480);
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Set alias.
		setAlias(L"圆形（",L"）");
		//Copy primitive.
		copyRenderable(CCircleAttribute::circle0);
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Set alias.
		setAlias(L"正三边形（",L"）");
		//Copy primitive.
		copyRenderable(CCircleAttribute::circle3);
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Set alias.
		setAlias(L"正四边形（",L"）");
		//Copy primitive.
		copyRenderable(CCircleAttribute::circle4);
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Set alias.
		setAlias(L"正五边形（",L"）");
		//Copy primitive.
		copyRenderable(CCircleAttribute::circle5);
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Set alias.
		setAlias(L"正六边形（",L"）");
		//Copy primitive.
		copyRenderable(CCircleAttribute::circle6);
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Set alias.
		setAlias(L"正四面体（",L"）");
		//Copy primitive.
		copyRenderable(CPolygonAttribute::polygon4);
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Set alias.
		setAlias(L"正六面体（",L"）");
		//Copy primitive.
		copyRenderable(CPolygonAttribute::polygon6);
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Set alias.
		setAlias(L"正八面体（",L"）");
		//Copy primitive.
		copyRenderable(CPolygonAttribute::polygon8);
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Set alias.
		setAlias(L"正十二面体（",L"）");
		//Copy primitive.
		copyRenderable(CPolygonAttribute::polygon12);
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Set alias.
		setAlias(L"正二十面体（",L"）");
		//Copy primitive.
		copyRenderable(CPolygonAttribute::polygon20);
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Set alias.
		setAlias(L"四边形（",L"）");
		//Copy primitive.
		copyRenderable(CQuadrangleAttribute::quadrangle0);
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Set alias.
		setAlias(L"圆锥体（",L"）");
		//Copy primitive.
		copyRenderable(CConeAttribute::cone0);
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Set alias.
		setAlias(L"三棱锥（",L"）");
		//Copy primitive.
		copyRenderable(CConeAttribute::cone3);
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Set alias.
		setAlias(L"四棱锥（",L"）");
		//Copy primitive.
		copyRenderable(CConeAttribute::cone4);
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Set alias.
		setAlias(L"六棱锥（",L"）");
		//Copy primitive.
		copyRenderable(CConeAttribute::cone6);
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Set alias.
		setAlias(L"盒体（",L"）");
		//Copy primitive.
		copyRenderable(CCuboidAttribute::cuboid0);
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Set alias.
		setAlias(L"薄板（",L"）");
		//Copy primitive.
		copyRenderable(CSliceAttribute::floor0);
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Set alias.
		setAlias(L"胶囊体（",L"）");
		//Copy primitive.
		copyRenderable(CCapsuleAttribute::capsule0);
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Set alias.
		setAlias(L"圆饼体（",L"）");
		//Copy primitive.
		copyRenderable(CChamferCylinderAttribute::chamferCylinder0);
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Set alias.
		setAlias(L"圆台体（",L"）");
		//Copy primitive.
		copyRenderable(CFrustumAttribute::frustum0);
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Set alias.
		setAlias(L"三棱台（",L"）");
		//Copy primitive.
		copyRenderable(CFrustumAttribute::frustum3);
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Set alias.
		setAlias(L"四棱台（",L"）");
		//Copy primitive.
		copyRenderable(CFrustumAttribute::frustum4);
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Set alias.
		setAlias(L"六棱台（",L"）");
		//Copy primitive.
		copyRenderable(CFrustumAttribute::frustum6);
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Set alias.
		setAlias(L"圆柱体（",L"）");
		//Copy primitive.
		copyRenderable(CCylinderAttribute::cylinder0);
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Set alias.
		setAlias(L"三棱柱（",L"）");
		//Copy primitive.
		copyRenderable(CCylinderAttribute::cylinder3);
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Set alias.
		setAlias(L"五棱柱（",L"）");
		//Copy primitive.
		copyRenderable(CCylinderAttribute::cylinder5);
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Set alias.
		setAlias(L"六棱柱（",L"）");
		//Copy primitive.
		copyRenderable(CCylinderAttribute::cylinder6);
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Set alias.
		setAlias(L"球体（",L"）");
		//Copy primitive.
		copyRenderable(CSphereAttribute::sphere0);
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Set alias.
		setAlias(L"半球体（",L"）");
		//Copy primitive.
		copyRenderable(CHemisphereAttribute::hemisphere0);
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

const CPrimitiveAttribute& CPhysicsPrimitiveObject::getPrimitiveAttribute() const
{
	//Return result.
	return *this;
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetPrimitiveAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsPrimitiveObject::setPrimitiveAttribute(const CPrimitiveAttribute& attribute)
{
#ifdef _DEBUG
	assert(getPrimitiveType() == CPrimitiveAttribute::nullPrimitive);
	assert(attribute.getType() != CPrimitiveAttribute::nullPrimitive);
#endif
	//Get type.
	_INTEGER type = attribute.getType();
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Set alias.
		setAlias(L"三角形（",L"）");
		//Check result.
		if(!attribute.isEqual(CTriangleAttribute::triangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CTriangleAttribute triangle;
			//Set primitive attribute.
			triangle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(triangle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CTriangleAttribute::triangle0);
		}
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Set alias.
		setAlias(L"网格（",L"）");
		//Check result.
		if(!attribute.isEqual(CGridAttribute::grid4x3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(3,4);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(grid);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CGridAttribute::grid4x3);
		}
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Set alias.
		setAlias(L"网格（",L"）");
		//Check result.
		if(!attribute.isEqual(CGridAttribute::grid20x15.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(15,20);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(grid);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CGridAttribute::grid20x15);
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Check result.
		if(!attribute.isEqual(CGridAttribute::ground80x60.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(60,80);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(ground);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CGridAttribute::ground80x60);
		}
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Check result.
		if(!attribute.isEqual(CGridAttribute::ground320x240.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(240,320);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(ground);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CGridAttribute::ground320x240);
		}
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Set alias.
		setAlias(L"地形（",L"）");
		//Check result.
		if(!attribute.isEqual(CGridAttribute::ground640x480.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(480,640);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(ground);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CGridAttribute::ground640x480);
		}
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Set alias.
		setAlias(L"圆形（",L"）");
		//Check result.
		if(!attribute.isEqual(CCircleAttribute::circle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle;
			//Set primitive attribute.
			circle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(circle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCircleAttribute::circle0);
		}
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Set alias.
		setAlias(L"正三边形（",L"）");
		//Check result.
		if(!attribute.isEqual(CCircleAttribute::circle3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(3);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(circle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCircleAttribute::circle3);
		}
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Set alias.
		setAlias(L"正四边形（",L"）");
		//Check result.
		if(!attribute.isEqual(CCircleAttribute::circle4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(4);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(circle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCircleAttribute::circle4);
		}
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Set alias.
		setAlias(L"正五边形（",L"）");
		//Check result.
		if(!attribute.isEqual(CCircleAttribute::circle5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(5);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(circle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCircleAttribute::circle5);
		}
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Set alias.
		setAlias(L"正六边形（",L"）");
		//Check result.
		if(!attribute.isEqual(CCircleAttribute::circle6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(6);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(circle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCircleAttribute::circle6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Set alias.
		setAlias(L"正四面体（",L"）");
		//Check result.
		if(!attribute.isEqual(CPolygonAttribute::polygon4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(4);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(polygon);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CPolygonAttribute::polygon4);
		}
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Set alias.
		setAlias(L"正六面体（",L"）");
		//Check result.
		if(!attribute.isEqual(CPolygonAttribute::polygon6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(6);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(polygon);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CPolygonAttribute::polygon6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Set alias.
		setAlias(L"正八面体（",L"）");
		//Check result.
		if(!attribute.isEqual(CPolygonAttribute::polygon8.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(8);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(polygon);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CPolygonAttribute::polygon8);
		}
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Set alias.
		setAlias(L"正十二面体（",L"）");
		//Check result.
		if(!attribute.isEqual(CPolygonAttribute::polygon12.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(12);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(polygon);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CPolygonAttribute::polygon12);
		}
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Set alias.
		setAlias(L"正二十面体（",L"）");
		//Check result.
		if(!attribute.isEqual(CPolygonAttribute::polygon20.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(20);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(attribute);
			//Copy attribute.
			copyRenderable(polygon);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CPolygonAttribute::polygon20);
		}
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Set alias.
		setAlias(L"四边形（",L"）");
		//Check result.
		if(!attribute.isEqual(CQuadrangleAttribute::quadrangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CQuadrangleAttribute quadrangle;
			//Set primitive attribute.
			quadrangle.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(quadrangle);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CQuadrangleAttribute::quadrangle0);
		}
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Set alias.
		setAlias(L"圆锥体（",L"）");
		//Check result.
		if(!attribute.isEqual(CConeAttribute::cone0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone;
			//Set primitive attribute.
			cone.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cone);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CConeAttribute::cone0);
		}
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Set alias.
		setAlias(L"三棱锥（",L"）");
		//Check result.
		if(!attribute.isEqual(CConeAttribute::cone3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(3);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cone);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CConeAttribute::cone3);
		}
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Set alias.
		setAlias(L"四棱锥（",L"）");
		//Check result.
		if(!attribute.isEqual(CConeAttribute::cone4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(4);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cone);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CConeAttribute::cone4);
		}
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Set alias.
		setAlias(L"六棱锥（",L"）");
		//Check result.
		if(!attribute.isEqual(CConeAttribute::cone6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(6);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cone);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CConeAttribute::cone6);
		}
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Set alias.
		setAlias(L"盒体（",L"）");
		//Check result.
		if(!attribute.isEqual(CCuboidAttribute::cuboid0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCuboidAttribute cuboid;
			//Set primitive attribute.
			cuboid.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cuboid);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCuboidAttribute::cuboid0);
		}
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Set alias.
		setAlias(L"薄板（",L"）");
		//Check result.
		if(!attribute.isEqual(CSliceAttribute::floor0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSliceAttribute floor;
			//Set primitive attribute.
			floor.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(floor);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CSliceAttribute::floor0);
		}
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Set alias.
		setAlias(L"胶囊体（",L"）");
		//Check result.
		if(!attribute.isEqual(CCapsuleAttribute::capsule0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCapsuleAttribute capsule;
			//Set primitive attribute.
			capsule.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(capsule);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCapsuleAttribute::capsule0);
		}
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Set alias.
		setAlias(L"圆饼体（",L"）");
		//Check result.
		if(!attribute.isEqual(CChamferCylinderAttribute::chamferCylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CChamferCylinderAttribute chamferCylinder;
			//Set primitive attribute.
			chamferCylinder.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(chamferCylinder);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CChamferCylinderAttribute::chamferCylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Set alias.
		setAlias(L"圆台体（",L"）");
		//Check result.
		if(!attribute.isEqual(CFrustumAttribute::frustum0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum;
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(frustum);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CFrustumAttribute::frustum0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Set alias.
		setAlias(L"三棱台（",L"）");
		//Check result.
		if(!attribute.isEqual(CFrustumAttribute::frustum3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(3);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(frustum);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CFrustumAttribute::frustum3);
		}
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Set alias.
		setAlias(L"四棱台（",L"）");
		//Check result.
		if(!attribute.isEqual(CFrustumAttribute::frustum4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(4);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(frustum);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CFrustumAttribute::frustum4);
		}
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Set alias.
		setAlias(L"六棱台（",L"）");
		//Check result.
		if(!attribute.isEqual(CFrustumAttribute::frustum6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(6);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(frustum);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CFrustumAttribute::frustum6);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Set alias.
		setAlias(L"圆柱体（",L"）");
		//Check result.
		if(!attribute.isEqual(CCylinderAttribute::cylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder;
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cylinder);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCylinderAttribute::cylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Set alias.
		setAlias(L"三棱柱（",L"）");
		//Check result.
		if(!attribute.isEqual(CCylinderAttribute::cylinder3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(3);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cylinder);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCylinderAttribute::cylinder3);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Set alias.
		setAlias(L"五棱柱（",L"）");
		//Check result.
		if(!attribute.isEqual(CCylinderAttribute::cylinder5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(5);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cylinder);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCylinderAttribute::cylinder5);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Set alias.
		setAlias(L"六棱柱（",L"）");
		//Check result.
		if(!attribute.isEqual(CCylinderAttribute::cylinder6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(6);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(cylinder);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CCylinderAttribute::cylinder6);
		}
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Set alias.
		setAlias(L"球体（",L"）");
		//Check result.
		if(!attribute.isEqual(CSphereAttribute::sphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSphereAttribute sphere;
			//Set primitive attribute.
			sphere.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(sphere);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CSphereAttribute::sphere0);
		}
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Set alias.
		setAlias(L"半球体（",L"）");
		//Check result.
		if(!attribute.isEqual(CHemisphereAttribute::hemisphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CHemisphereAttribute hemisphere;
			//Set primitive attribute.
			hemisphere.setPrimitiveAttribute(attribute);
			//Swap attribute.
			copyRenderable(hemisphere);
		}
		else
		{
			//Copy attribute.
			copyRenderable(CHemisphereAttribute::hemisphere0);
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetIndexAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsPrimitiveObject::getIndexAttribute(CIndexAttribute& attribute) const
{
	//Get type.
	_INTEGER type = getPrimitiveType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
	assert(attribute.getIndexType() == CIndexAttribute::nullIndex);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Check result.
		if(!isEqual(CTriangleAttribute::triangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CTriangleAttribute triangle;
			//Set primitive attribute.
			triangle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(triangle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CTriangleAttribute::triangle0);
		}
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::grid4x3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(3,4);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(grid);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CGridAttribute::grid4x3);
		}
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::grid20x15.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(15,20);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(grid);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CGridAttribute::grid20x15);
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground80x60.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(60,80);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(ground);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CGridAttribute::ground80x60);
		}
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground320x240.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(240,320);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(ground);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CGridAttribute::ground320x240);
		}
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground640x480.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(480,640);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(ground);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CGridAttribute::ground640x480);
		}
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle;
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(circle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCircleAttribute::circle0);
		}
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(3);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(circle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCircleAttribute::circle3);
		}
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(4);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(circle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCircleAttribute::circle4);
		}
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(5);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(circle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCircleAttribute::circle5);
		}
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(6);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(circle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCircleAttribute::circle6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(4);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(polygon);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CPolygonAttribute::polygon4);
		}
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(6);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(polygon);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CPolygonAttribute::polygon6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon8.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(8);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(polygon);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CPolygonAttribute::polygon8);
		}
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon12.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(12);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(polygon);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CPolygonAttribute::polygon12);
		}
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon20.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(20);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(polygon);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CPolygonAttribute::polygon20);
		}
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Check result.
		if(!isEqual(CQuadrangleAttribute::quadrangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CQuadrangleAttribute quadrangle;
			//Set primitive attribute.
			quadrangle.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(quadrangle);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CQuadrangleAttribute::quadrangle0);
		}
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone;
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cone);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CConeAttribute::cone0);
		}
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(3);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cone);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CConeAttribute::cone3);
		}
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(4);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cone);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CConeAttribute::cone4);
		}
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(6);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cone);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CConeAttribute::cone6);
		}
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Check result.
		if(!isEqual(CCuboidAttribute::cuboid0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCuboidAttribute cuboid;
			//Set primitive attribute.
			cuboid.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cuboid);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCuboidAttribute::cuboid0);
		}
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Check result.
		if(!isEqual(CSliceAttribute::floor0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSliceAttribute floor;
			//Set primitive attribute.
			floor.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(floor);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CSliceAttribute::floor0);
		}
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Check result.
		if(!isEqual(CCapsuleAttribute::capsule0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCapsuleAttribute capsule;
			//Set primitive attribute.
			capsule.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(capsule);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCapsuleAttribute::capsule0);
		}
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Check result.
		if(!isEqual(CChamferCylinderAttribute::chamferCylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CChamferCylinderAttribute chamferCylinder0;
			//Set primitive attribute.
			chamferCylinder0.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(chamferCylinder0);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CChamferCylinderAttribute::chamferCylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum;
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(frustum);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CFrustumAttribute::frustum0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(3);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(frustum);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CFrustumAttribute::frustum3);
		}
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(4);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(frustum);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CFrustumAttribute::frustum4);
		}
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(6);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(frustum);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CFrustumAttribute::frustum6);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder;
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cylinder);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCylinderAttribute::cylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(3);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cylinder);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCylinderAttribute::cylinder3);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(5);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cylinder);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCylinderAttribute::cylinder5);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(6);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(cylinder);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CCylinderAttribute::cylinder6);
		}
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Check result.
		if(!isEqual(CSphereAttribute::sphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSphereAttribute sphere;
			//Set primitive attribute.
			sphere.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(sphere);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CSphereAttribute::sphere0);
		}
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Check result.
		if(!isEqual(CHemisphereAttribute::hemisphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CHemisphereAttribute hemisphere;
			//Set primitive attribute.
			hemisphere.setPrimitiveAttribute(*this);
			//Clone index attribute.
			attribute.cloneIndex(hemisphere);
		}
		else
		{
			//Clone index attribute.
			attribute.cloneIndex(CHemisphereAttribute::hemisphere0);
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}

/////////////////////////////////////////////////////////////////////////////////
//
// GetVertexAttribute
//
/////////////////////////////////////////////////////////////////////////////////

void CPhysicsPrimitiveObject::getVertexAttribute(CVertexAttribute& attribute) const
{
	//Get type.
	_INTEGER type = getPrimitiveType();
#ifdef _DEBUG
	assert(type != CPrimitiveAttribute::nullPrimitive);
	assert(attribute.getVertexType() == CVertexAttribute::nullVertex);
#endif
	//Check type.
	if(type == CPrimitiveAttribute::triangle0Primitive)
	{
		//Check result.
		if(!isEqual(CTriangleAttribute::triangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CTriangleAttribute triangle;
			//Set primitive attribute.
			triangle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(triangle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CTriangleAttribute::triangle0);
		}
	}
	else if(type == CPrimitiveAttribute::grid4x3Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::grid4x3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(3,4);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(grid);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CGridAttribute::grid4x3);
		}
	}
	else if(type == CPrimitiveAttribute::grid20x15Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::grid20x15.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute grid(15,20);
			//Set primitive attribute.
			grid.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(grid);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CGridAttribute::grid20x15);
		}
	}
	else if(type == CPrimitiveAttribute::ground80x60Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground80x60.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(60,80);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(ground);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CGridAttribute::ground80x60);
		}
	}
	else if(type == CPrimitiveAttribute::ground320x240Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground320x240.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(240,320);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(ground);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CGridAttribute::ground320x240);
		}
	}
	else if(type == CPrimitiveAttribute::ground640x480Primitive)
	{
		//Check result.
		if(!isEqual(CGridAttribute::ground640x480.getPrimitiveAttribute()))
		{
			//Create attribute.
			CGridAttribute ground(480,640);
			//Set primitive attribute.
			ground.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(ground);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CGridAttribute::ground640x480);
		}
	}
	else if(type == CPrimitiveAttribute::circle0Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle;
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(circle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCircleAttribute::circle0);
		}
	}
	else if(type == CPrimitiveAttribute::circle3Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(3);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(circle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCircleAttribute::circle3);
		}
	}
	else if(type == CPrimitiveAttribute::circle4Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(4);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(circle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCircleAttribute::circle4);
		}
	}
	else if(type == CPrimitiveAttribute::circle5Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(5);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(circle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCircleAttribute::circle5);
		}
	}
	else if(type == CPrimitiveAttribute::circle6Primitive)
	{
		//Check result.
		if(!isEqual(CCircleAttribute::circle6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCircleAttribute circle(6);
			//Set primitive attribute.
			circle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(circle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCircleAttribute::circle6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon4Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(4);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(polygon);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CPolygonAttribute::polygon4);
		}
	}
	else if(type == CPrimitiveAttribute::polygon6Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(6);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(polygon);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CPolygonAttribute::polygon6);
		}
	}
	else if(type == CPrimitiveAttribute::polygon8Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon8.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(8);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(polygon);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CPolygonAttribute::polygon8);
		}
	}
	else if(type == CPrimitiveAttribute::polygon12Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon12.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(12);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(polygon);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CPolygonAttribute::polygon12);
		}
	}
	else if(type == CPrimitiveAttribute::polygon20Primitive)
	{
		//Check result.
		if(!isEqual(CPolygonAttribute::polygon20.getPrimitiveAttribute()))
		{
			//Create attribute.
			CPolygonAttribute polygon(20);
			//Set primitive attribute.
			polygon.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(polygon);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CPolygonAttribute::polygon20);
		}
	}
	else if(type == CPrimitiveAttribute::quadrangle0Primitive)
	{
		//Check result.
		if(!isEqual(CQuadrangleAttribute::quadrangle0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CQuadrangleAttribute quadrangle;
			//Set primitive attribute.
			quadrangle.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(quadrangle);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CQuadrangleAttribute::quadrangle0);
		}
	}
	else if(type == CPrimitiveAttribute::cone0Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone;
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cone);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CConeAttribute::cone0);
		}
	}
	else if(type == CPrimitiveAttribute::cone3Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(3);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cone);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CConeAttribute::cone3);
		}
	}
	else if(type == CPrimitiveAttribute::cone4Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(4);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cone);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CConeAttribute::cone4);
		}
	}
	else if(type == CPrimitiveAttribute::cone6Primitive)
	{
		//Check result.
		if(!isEqual(CConeAttribute::cone6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CConeAttribute cone(6);
			//Set primitive attribute.
			cone.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cone);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CConeAttribute::cone6);
		}
	}
	else if(type == CPrimitiveAttribute::cuboid0Primitive)
	{
		//Check result.
		if(!isEqual(CCuboidAttribute::cuboid0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCuboidAttribute cuboid;
			//Set primitive attribute.
			cuboid.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cuboid);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCuboidAttribute::cuboid0);
		}
	}
	else if(type == CPrimitiveAttribute::floor0Primitive)
	{
		//Check result.
		if(!isEqual(CSliceAttribute::floor0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSliceAttribute floor;
			//Set primitive attribute.
			floor.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(floor);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CSliceAttribute::floor0);
		}
	}
	else if(type == CPrimitiveAttribute::capsule0Primitive)
	{
		//Check result.
		if(!isEqual(CCapsuleAttribute::capsule0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCapsuleAttribute capsule;
			//Set primitive attribute.
			capsule.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(capsule);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCapsuleAttribute::capsule0);
		}
	}
	else if(type == CPrimitiveAttribute::chamferCylider0Primitive)
	{
		//Check result.
		if(!isEqual(CChamferCylinderAttribute::chamferCylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CChamferCylinderAttribute chamferCylinder0;
			//Set primitive attribute.
			chamferCylinder0.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(chamferCylinder0);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CChamferCylinderAttribute::chamferCylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum0Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum;
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(frustum);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CFrustumAttribute::frustum0);
		}
	}
	else if(type == CPrimitiveAttribute::frustum3Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(3);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(frustum);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CFrustumAttribute::frustum3);
		}
	}
	else if(type == CPrimitiveAttribute::frustum4Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum4.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(4);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(frustum);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CFrustumAttribute::frustum4);
		}
	}
	else if(type == CPrimitiveAttribute::frustum6Primitive)
	{
		//Check result.
		if(!isEqual(CFrustumAttribute::frustum6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CFrustumAttribute frustum(6);
			//Set primitive attribute.
			frustum.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(frustum);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CFrustumAttribute::frustum6);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder0Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder;
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cylinder);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCylinderAttribute::cylinder0);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder3Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder3.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(3);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cylinder);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCylinderAttribute::cylinder3);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder5Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder5.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(5);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cylinder);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCylinderAttribute::cylinder5);
		}
	}
	else if(type == CPrimitiveAttribute::cylinder6Primitive)
	{
		//Check result.
		if(!isEqual(CCylinderAttribute::cylinder6.getPrimitiveAttribute()))
		{
			//Create attribute.
			CCylinderAttribute cylinder(6);
			//Set primitive attribute.
			cylinder.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(cylinder);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CCylinderAttribute::cylinder6);
		}
	}
	else if(type == CPrimitiveAttribute::sphere0Primitive)
	{
		//Check result.
		if(!isEqual(CSphereAttribute::sphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CSphereAttribute sphere;
			//Set primitive attribute.
			sphere.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(sphere);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CSphereAttribute::sphere0);
		}
	}
	else if(type == CPrimitiveAttribute::hemisphere0Primitive)
	{
		//Check result.
		if(!isEqual(CHemisphereAttribute::hemisphere0.getPrimitiveAttribute()))
		{
			//Create attribute.
			CHemisphereAttribute hemisphere;
			//Set primitive attribute.
			hemisphere.setPrimitiveAttribute(*this);
			//Clone vertex attribute.
			attribute.cloneVertex(hemisphere);
		}
		else
		{
			//Clone vertex attribute.
			attribute.cloneVertex(CHemisphereAttribute::hemisphere0);
		}
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
}
