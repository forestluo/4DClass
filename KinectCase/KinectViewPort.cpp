///////////////////////////////////////////////////////////////////////////////
//
// KinectViewPort.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "KinectViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// Defination
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_DIRECTION									C4DVector3(0.0f,1.0f,0.0f)
#define CAMERA_INSTANCE(p)									((CModelViewerCamera *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CKinectViewPort::base(L"CKinectViewPort",L"CModelViewPort");

///////////////////////////////////////////////////////////////////////////////
//
// CKinectViewPort
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectViewPort::CKinectViewPort(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// ~CKinectViewPort
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CKinectViewPort::~CKinectViewPort(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeCamera
//
///////////////////////////////////////////////////////////////////////////////

void CKinectViewPort::initializeCamera(_OBJECT camera)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Look at.
	D3DXVECTOR3 vecAt(0.0f,1.5f,0.0f);
	//Eye at.
	D3DXVECTOR3 vecEye(-3.0f,4.5f,0.0f);
	//Set view parameters.
	//Let camera look at Z axis.
	CAMERA_INSTANCE(camera)->SetViewParams(&vecEye,&vecAt);

	//Rotation.
	C4DQuaternion rotation(DEFAULT_DIRECTION,C4DVector3(1.0f,0.0f,0.0f));
	//Set up vector.
	CAMERA_INSTANCE(camera)->SetViewQuat(D3DXQUATERNION(rotation));
}
