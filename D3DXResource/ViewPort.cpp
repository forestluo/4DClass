///////////////////////////////////////////////////////////////////////////////
//
// ViewPort.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "ViewPort.h"

///////////////////////////////////////////////////////////////////////////////
//
// Defination
//
///////////////////////////////////////////////////////////////////////////////

#define CAMERA_INSTANCE(p)									((CBaseCamera *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Globals
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CViewPort::base(L"CViewPort",L"C4DObject");

///////////////////////////////////////////////////////////////////////////////
//
// CViewPort
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CViewPort::CViewPort(_OBJECT camera)
{
#ifdef _DEBUG
	assert(camera != NULL);
#endif
	//Set value.
	this->camera = camera;

	//Set default value.
	frameStamp = 0;
	width = height = 0;
	xMouse = yMouse = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// ~CViewPort
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CViewPort::~CViewPort(void)
{
	//Delete camera.
	if(camera != _NULL)
	{
		//Delete instance.
		delete CAMERA_INSTANCE(camera);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// InitializeCamera
//
///////////////////////////////////////////////////////////////////////////////

void CViewPort::initializeCamera(_OBJECT camera)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Look at.
    D3DXVECTOR3 vecAt(0.0f,0.0f,0.0f);
	//Eye at.
    D3DXVECTOR3 vecEye(0.0f,0.0f,-5.0f);
	//Set view parameters.
	//Let camera look at Z axis.
    CAMERA_INSTANCE(camera)->SetViewParams(&vecEye,&vecAt);
}

///////////////////////////////////////////////////////////////////////////////
//
// NextFrameStamp
//
///////////////////////////////////////////////////////////////////////////////

void CViewPort::nextFrameStamp()
{
	//Add timestamp.
	frameStamp ++;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFrameStamp
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CViewPort::getFrameStamp()
{
	//Set value.
	return frameStamp;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMouseX
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CViewPort::getMouseX()
{
    //Return mouse position.
	return xMouse;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMouseY
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CViewPort::getMouseY()
{
    //Return mouse position.
	return yMouse;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWidth
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CViewPort::getWidth()
{
	//Set value.
	return width;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetHeight
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CViewPort::getHeight()
{
	//Set value.
	return height;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFarClip
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CViewPort::getFarClip()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return CAMERA_INSTANCE(camera)->GetFarClip();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetNearClip
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CViewPort::getNearClip()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return CAMERA_INSTANCE(camera)->GetNearClip();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFAspect
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CViewPort::getFAspect()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return CAMERA_INSTANCE(camera)->GetFAspect();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFieldOfView
//
///////////////////////////////////////////////////////////////////////////////

_FLOAT CViewPort::getFieldOfView()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return CAMERA_INSTANCE(camera)->GetFieldOfView();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEyeAt
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CViewPort::getEyeAt()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return C4DVector3(*CAMERA_INSTANCE(camera)->GetEyePt());
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEyeLookAt
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CViewPort::getEyeLookAt()
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set value.
	return C4DVector3(*CAMERA_INSTANCE(camera)->GetLookAtPt());
}

///////////////////////////////////////////////////////////////////////////////
//
// SetViewParameters
//
///////////////////////////////////////////////////////////////////////////////

void CViewPort::setViewParameters(const C4DVector3& vEyeAt,const C4DVector3& vEyeLookAt)
{
	//Set value.
	D3DXVECTOR3 eyeAt(vEyeAt);
	//Set value.
	D3DXVECTOR3 eyeLookAt(vEyeLookAt);

#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Set parameters.
	CAMERA_INSTANCE(camera)->SetViewParams(&eyeAt,&eyeLookAt);
}

///////////////////////////////////////////////////////////////////////////////
//
// SetProjectionParameters
//
///////////////////////////////////////////////////////////////////////////////

void CViewPort::setProjectionParameters(_FLOAT fov,_FLOAT aspect,_FLOAT nearPlane,_FLOAT farPlane)
{
#ifdef _DEBUG
	assert(camera != NULL);
#endif
	//Set parameters.
	CAMERA_INSTANCE(camera)->SetProjParams(fov,aspect,nearPlane,farPlane);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetViewMatrix
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 CViewPort::getViewMatrix()
{
#ifdef _DEBUG
	assert(camera != NULL);
#endif
	//Get the view matrix from the camera class
	return C4DMatrix4(*CAMERA_INSTANCE(camera)->GetViewMatrix());
}

///////////////////////////////////////////////////////////////////////////////
//
// GetProjectionMatrix
//
///////////////////////////////////////////////////////////////////////////////

C4DMatrix4 CViewPort::getProjectionMatrix()
{
#ifdef _DEBUG
	assert(camera != NULL);
#endif
	//Get the projection matrix from the camera class
	return C4DMatrix4(*CAMERA_INSTANCE(camera)->GetProjMatrix());
}

///////////////////////////////////////////////////////////////////////////////
//
// GetViewDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CViewPort::getViewDirection(_INTEGER x,_INTEGER y)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Direction.
	D3DXVECTOR3 vDirection;
	//Get projection matrix.
	D3DXMATRIX mProjection = *CAMERA_INSTANCE(camera)->GetProjMatrix();
	//Compute the vector of the Pick ray in screen space.
	vDirection.x = ( ( ( 2.0f * x ) / getWidth() ) - 1 ) / mProjection._11;
	vDirection.y = -( ( ( 2.0f * y ) / getHeight() ) - 1 ) / mProjection._22;
	vDirection.z = 1.0f;
	//Return result.
	return C4DVector3(vDirection);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetWorldDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CViewPort::getWorldDirection(_INTEGER x,_INTEGER y)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif
	//Inverse matrix.
	D3DXMATRIX mInverse;
	//Get view matrix.
	D3DXMATRIX mView = *CAMERA_INSTANCE(camera)->GetViewMatrix();
	//Inverse it.
	D3DXMatrixInverse(&mInverse,NULL,&mView);

	//Current position.
	D3DXVECTOR3 vPosition(getViewDirection(x,y));

	//Current position.
	D3DXVECTOR3 wPosition;
	//Transform it.
	D3DXVec3TransformCoord(&wPosition,&vPosition,&mInverse);
	//Return result.
	return C4DVector3(wPosition);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMoveDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CViewPort::getMoveDirection(_INTEGER x,_INTEGER y)
{
#ifdef _DEBUG
	assert(camera != _NULL);
#endif

	//Inverse matrix.
	D3DXMATRIX mInverse;
	//Get view matrix.
	D3DXMATRIX mView = *CAMERA_INSTANCE(camera)->GetViewMatrix();
	//Inverse it.
	D3DXMatrixInverse(&mInverse,NULL,&mView);

	//Current position.
	D3DXVECTOR3 vPosition(getViewDirection(x,y));

	//Current position.
	D3DXVECTOR3 wPosition;
	//Transform it.
	D3DXVec3TransformCoord(&wPosition,&vPosition,&mInverse);

	//Last position.
	D3DXVECTOR3 vLastPosition(getViewDirection(xMouse,yMouse));

	//Last position.
	D3DXVECTOR3 wLastPosition;
	//Transform it.
	D3DXVec3TransformCoord(&wLastPosition,&vLastPosition,&mInverse);

	//Get eye direction.
	D3DXVECTOR3 vEyeDirection(getEyeLookAt() - getEyeAt());
	//Get distance.
	FLOAT fDistance = D3DXVec3Length(&vEyeDirection);

	//Get current direction.
	return C4DVector3(fDistance * (wPosition - wLastPosition));
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CViewPort::handleMessage(const D3DXEvent& d3dxEvent)
{
#ifdef _DEBUG
	assert(camera != NULL);
#endif

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Handle key presses.
	case d3dxMsgProc:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxMsgProc.pbNoFurtherProcessing != NULL);
#endif
		///////////////////////////////////////
		//
		//Check mouse message.
		if(d3dxEvent.d3dxMsgProc.IsMouseEvent())
		{
			//Get mouse position.
			xMouse = (short)LOWORD(d3dxEvent.d3dxMsgProc.lParam);
			yMouse = (short)HIWORD(d3dxEvent.d3dxMsgProc.lParam);
		}
		//
		///////////////////////////////////////
		//Let camera handle message.
		CAMERA_INSTANCE(camera)->HandleMessages(d3dxEvent.d3dxMsgProc.hWnd,d3dxEvent.d3dxMsgProc.uMsg,
								d3dxEvent.d3dxMsgProc.wParam,d3dxEvent.d3dxMsgProc.lParam);
		break;
	//Handle updates to the scene.
	case d3dxOnFrameMove:
		//Frame move.
		CAMERA_INSTANCE(camera)->FrameMove(d3dxEvent.d3dxFrameMove.fElapsedTime);
		break;
	//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Initialize camera.
		initializeCamera(camera);
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Get width.
		width = GetBackBufferSurfaceWidth(d3dxEvent.d3dxResetDevice9);
		//Get height.
		height = GetBackBufferSurfaceHeight(d3dxEvent.d3dxResetDevice9);
		//Setup the camera's projection parameters.
		//Calculate aspect ratio.
		float fAspectRatio = width / (FLOAT)height;
		//Set projection parameters.
		CAMERA_INSTANCE(camera)->SetProjParams(D3DX_PI / 4,fAspectRatio,0.1f,1000.0f);
		break;
	}
	//Return result.
	return CD3DXObject::handleMessage(d3dxEvent);
}
