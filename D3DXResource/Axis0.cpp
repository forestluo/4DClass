///////////////////////////////////////////////////////////////////////////////
//
// Axis0.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "Axis0.h"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CAxis0::base(L"CAxis0",L"CD3DXLinestrip");

///////////////////////////////////////////////////////////////////////////////
//
// CAxis0
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CAxis0::CAxis0(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CAxis0
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CAxis0::~CAxis0(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// DrawObjects
//
///////////////////////////////////////////////////////////////////////////////

void CAxis0::drawObjects(IDirect3DDevice9* pd3dDevice)
{
	//Original
    C4DVector3 original(0.0f,0.0f,0.0f);

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif

	//Draw ray.
	drawRay(pd3dDevice,original,C4DVector3(1.0f,0.0f,0.0f),_TRUE);
	drawRay(pd3dDevice,original,C4DVector3(0.0f,1.0f,0.0f),_TRUE);
	drawRay(pd3dDevice,original,C4DVector3(0.0f,0.0f,1.0f),_TRUE);
}
