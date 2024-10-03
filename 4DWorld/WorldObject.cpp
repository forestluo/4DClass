///////////////////////////////////////////////////////////////////////////////
//
// WorldObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CWorldObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CWorldObject::CWorldObject(void)
{
	//Set this.
	setThis(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// CWorldObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CWorldObject::~CWorldObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// AddObject
//
///////////////////////////////////////////////////////////////////////////////

void CWorldObject::addObject(CWorldObject* object)
{
#ifdef _DEBUG
	assert(object != _NULL);
#endif
	//Call function.
	CChildAttribute::addObject(object);
	//Set parent.
	object->setParent((CWorldObject *)this);
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeMatrix
//
//////////////////////////////////////////////////////////////////////////////

void CWorldObject::initializeMatrix(C4DMatrix4& matrix) const
{
	//Matrix.
	C4DMatrix4 transformMatrix;

	//Initialize.
	matrix.identity();

	//Get scale.
	C4DVector3 scale = getScale();
	//Scaling.
	transformMatrix.scale(scale.x(),scale.y(),scale.z());
	//Multiply.
	matrix *= transformMatrix;

	//Get matrix.
	transformMatrix.rotate(getRotation());
	//Multiply.
	matrix *= transformMatrix;

	//Get position.
	C4DVector3 position = getPosition();
	//Translate.
	transformMatrix.translate(position.x(),position.y(),position.z());
	//Multiply.
	matrix *= transformMatrix;

	//Get parent object.
	CWorldObject* parent = (CWorldObject *)getParent();
	//Check parent.
	if(parent != _NULL)
	{
		//Get parent matrix.
		parent->initializeMatrix(transformMatrix);
		//Multiply.
		matrix *= transformMatrix;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWorldBox
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CWorldObject::getWorldBox(CSimpleBox& box) const
{
	//Value
	_BOOL flag = _FALSE;
	//Check count.
	if(getCount() > 0)
	{
		//Return result.
		return CChildAttribute::getWorldBox(box);
	}
	else
	{
		//Box.
		CSimpleBox tempBox;
		//World matrix.
		C4DMatrix4 worldMatrix;
		//Get box.
		if(getBox(tempBox))
		{
			//Set flag.
			flag = _TRUE;
			//Initialize matrix.
			initializeMatrix(worldMatrix);
			//Set box.
			box.setBox(&tempBox,&worldMatrix);
		}
	}
	//Return result.
	return flag;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWorldSphere
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CWorldObject::getWorldSphere(CSimpleSphere& sphere) const
{
	//Value
	_BOOL flag = _FALSE;
	//Check count.
	if(getCount() > 0)
	{
		//Return result.
		return CChildAttribute::getWorldSphere(sphere);
	}
	else
	{
		//Sphere.
		CSimpleSphere tempSphere;
		//World matrix.
		C4DMatrix4 worldMatrix;
		//Get box.
		if(getSphere(tempSphere))
		{
			//Set flag.
			flag = _TRUE;
			//Initialize matrix.
			initializeMatrix(worldMatrix);
			//Set sphere.
			sphere.setSphere(&tempSphere,&worldMatrix);
		}
	}
	//Return result.
	return flag;
}
