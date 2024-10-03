///////////////////////////////////////////////////////////////////////////////
//
// SketcherAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SketcherAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "JointObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// CSketcherAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketcherAttribute::CSketcherAttribute(void)
{
	//Set default value.
	sketcher = (CObjectSketcher *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CSketcherAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketcherAttribute::~CSketcherAttribute(void)
{
	//Check sketcher.
	if(sketcher != _NULL)
	{
		//Delete sketcher.
		delete (CObjectSketcher *)sketcher;
		//Clear sketcher.
		sketcher = (CObjectSketcher *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetSketcher
//
///////////////////////////////////////////////////////////////////////////////

CObjectSketcher* CSketcherAttribute::getSketcher()
{
	//Check sketcher.
	if(sketcher == _NULL)
	{
		//Check type.
		if(isPrimitiveObject())
		{
			//Create sketcher.
			sketcher = new CObjectSketcher();
		}
		else if(isCompoundObject())
		{
			//Create sketcher.
			sketcher = new CObjectSketcher();
		}
		else if(isJointObject())
		{
			//Create sketcher.
			sketcher = new CJointObjectSketcher();
		}
#ifdef _DEBUG
		assert(sketcher != _NULL);
#endif
		//Attach object.
		sketcher->attachObject(this);
	}
	//Return result.
	return sketcher;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetCollision
//
///////////////////////////////////////////////////////////////////////////////

void CSketcherAttribute::setCollision(_BOOL intersect)
{
#ifdef _DEBUG
	assert(sketcher != _NULL);
#endif
	//Check intersect.
	if(intersect)
	{
		//Set draw box.
		sketcher->drawBox = _TRUE;
		//Set intersected.
		sketcher->intersected = _TRUE;
	}
	else
	{
		//Set draw box.
		sketcher->drawBox = _FALSE;
		//Set intersected.
		sketcher->intersected = _FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// SetViewPort
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CSketcherAttribute::setViewPort(CViewPort* viewPort)
{
	//Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(viewPort != _NULL);
#endif

	//Get sketcher.
	CObjectSketcher* sketcher = (CObjectSketcher *)getSketcher();
	//Check sketcher.
	if(sketcher != _NULL) V_RETURN(sketcher->setViewPort(viewPort));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CSketcherAttribute::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr = FALSE;

	//Get sketcher.
	CObjectSketcher* sketcher = (CObjectSketcher *)getSketcher();
	//Check sketcher.
	if(sketcher != _NULL) V_RETURN(sketcher->handleMessage(d3dxEvent));
	//Return result.
	return hr;
}
