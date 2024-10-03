///////////////////////////////////////////////////////////////////////////////
//
// Sketch0.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "Sketch0.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define SKETCHER_INSTANCE(p)								((CObjectSketcher *)(p))
#define RED_COLOR											D3DCOLOR_RGBA(255,0,0,255)
#define GREEN_COLOR											D3DCOLOR_RGBA(0,255,0,255)
#define BLUE_COLOR											D3DCOLOR_RGBA(0,0,255,255)
#define WHITE_COLOR											D3DCOLOR_RGBA(255,255,255,255)

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CSketch0::base(L"CSketch0",L"CD3DXLinestrip");

///////////////////////////////////////////////////////////////////////////////
//
// CSketch0
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketch0::CSketch0(void)
{
	//Set default value.
	sketcher = (CObjectSketcher *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CSketch0
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketch0::~CSketch0(void)
{
	//Clear value.
	sketcher = (CObjectSketcher *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// DetachSkether
//
///////////////////////////////////////////////////////////////////////////////

void CSketch0::detachSketcher(void)
{
	//Clear skether.
	sketcher = (CObjectSketcher *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// AttachSketcher
//
///////////////////////////////////////////////////////////////////////////////

void CSketch0::attachSketcher(_OBJECT sketcher)
{
#ifdef _DEBUG
	assert(sketcher != _NULL);
#endif
	//Set sketcher.
	this->sketcher = sketcher;
}

///////////////////////////////////////////////////////////////////////////////
//
// DrawObjects
//
///////////////////////////////////////////////////////////////////////////////

void CSketch0::drawObjects(IDirect3DDevice9* pd3dDevice)
{
#ifdef _DEBUG
	assert(pd3dDevice != _NULL && sketcher != _NULL);
#endif

	//Get effect.
	CD3DXEffect* pEffect = getEffect();
#ifdef _DEBUG
	assert(pEffect != _NULL);
#endif

	//Set use world.
	pEffect->setUseWorld(_TRUE);
	//Commit changes.
	pEffect->commitChanges();

	//Check draw axis.
	if(SKETCHER_INSTANCE(sketcher)->drawAxis)
	{
		//Original
		C4DVector3 original(0.0f,0.0f,0.0f);

		//Set color.
		pEffect->setColor(RED_COLOR);
		//Commit changes.
		pEffect->commitChanges();
		//Draw ray.
		drawRay(pd3dDevice,original,C4DVector3(1.0f,0.0f,0.0f),_TRUE);

		//Set color.
		pEffect->setColor(GREEN_COLOR);
		//Commit changes.
		pEffect->commitChanges();
		//Draw ray.
		drawRay(pd3dDevice,original,C4DVector3(0.0f,1.0f,0.0f),_TRUE);

		//Set color.
		pEffect->setColor(BLUE_COLOR);
		//Commit changes.
		pEffect->commitChanges();
		//Draw ray.
		drawRay(pd3dDevice,original,C4DVector3(0.0f,0.0f,1.0f),_TRUE);
	}

	//Set use world.
	pEffect->setUseWorld(_FALSE);
	//Commit changes.
	pEffect->commitChanges();

	//Set color.
	pEffect->setColor(SKETCHER_INSTANCE(sketcher)->intersected ? RED_COLOR : WHITE_COLOR);
	//Commit changes.
	pEffect->commitChanges();

	//Check draw aabox.
	if(SKETCHER_INSTANCE(sketcher)->drawBox)
	{
		//Box.
		CSimpleBox box;
		//Get box.
		if(SKETCHER_INSTANCE(sketcher)->getWorldBox(box)) drawBox(pd3dDevice,box);
	}
	//Check draw sphere.
	if(SKETCHER_INSTANCE(sketcher)->drawSphere)
	{
		//Sphere.
		CSimpleSphere sphere;
		//Draw sphere.
		if(SKETCHER_INSTANCE(sketcher)->getWorldSphere(sphere)) drawSphere(pd3dDevice,sphere);
	}
}
