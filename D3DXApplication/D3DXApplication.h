///////////////////////////////////////////////////////////////////////////////
//
// D3DXApplication.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _D3DX_APPLICATION_H_
#define _D3DX_APPLICATION_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "CompoundObject.h"
#include "SoundApplication.h"
#include "SceneApplication.h"
#include "PhysicsApplication.h"
#include "ViewPortApplication.h"
#include "ResourceApplication.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXApplication
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXApplication :
	public CSoundApplication, public CResourceApplication,
	public CViewPortApplication, public CSceneApplication, public CPhysicsApplication
{
public:
	CD3DXApplication(void);
	virtual ~CD3DXApplication(void);

public:

	/**
	 * Startup.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void startup();

	/**
	 * Clear foreground.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearForeground();

public:

	/**
	 * Create floor.
	 *
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createFloor(_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
						const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

	/**
	 * Create sphere array.
	 *
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createSphereArray(_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

	/**
	* Create cuboid array.
	*
	 * @param arrayType Type of array.
	 * @param row Row count.
	 * @param column Column count.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createCuboidArray(_INTEGER arrayType,_INTEGER row = 1,_INTEGER column = 1,
							const C4DVector3& origin = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Create model.
	 *
	 * @param type Type of primitive.
	 * @param mass Mass of model.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createModel(_INTEGER type,_FLOAT mass = 0.0f,
						const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
						const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
						const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

	/**
	 * Create model.
	 *
	 * @param attribute Attribute of primitive.
	 * @param mass Mass of model.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void createModel(const CPrimitiveAttribute& attribute,_FLOAT mass = 0.0f,
						const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
						const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
						const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Add compound.
	 *
	 * @param object Compound object.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL addCompound(CCompoundObject* object);

	/**
	 * Create compound.
	 *
	 * @param classCode Class code of compound object.
	 * @param mass Mass of compound.
	 * @param scaling Scaling of model.
	 * @param rotation Rotation of slice.
	 * @param position Position of model.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	void createCompound(_LONG classCode,_FLOAT mass = 0.0f,
						const C4DVector3& scaling = C4DVector3(1.0f,1.0f,1.0f),
						const C4DVector3& rotation = C4DVector3(0.0f,0.0f,0.0f),
						const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f));

public:

	/**
	 * Create joint.
	 *
	 * @param jointType Type of joint.
	 * @param childName Name of child.
	 * @param position Position of model.
	 * @param parentName Name of parent.
	 * @return
	 *     <p>Joint object.</p>
	 */
	void createJoint(_INTEGER jointType,
						const CNormalString& childName,
						const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f),
						const CNormalString& parentName = L"");

	/**
	 * Create joint.
	 *
	 * @param attribute Attribute of joint.
	 * @param childName Name of child.
	 * @param position Position of model.
	 * @param parentName Name of parent.
	 * @return
	 *     <p>Joint object.</p>
	 */
	void createJoint(const CJointAttribute& attribute,
						const CNormalString& childName,
						const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f),
						const CNormalString& parentName = L"");

public:

	/**
	 * Pick object by name.
	 *
	 * @param alias Alias of object.
	 * @param clearPicked Whether clear previous picked object.
	 * @return
	 *     <p>Return a picked object.</p>
	 */
	CWorldObject* pickObject(const CNormalString& alias,_BOOL clearPicked = _TRUE);

	/**
	 * Pick object by mouse.
	 *
	 * @param x X position.
	 * @param y Y position.
	 * @param result Pick result.
	 * @param allHits Whether all hits needed.
	 * @return
	 *     <p>Return true, if there is an picked object.</p>
	 */
	_BOOL pickObject(_INTEGER x,_INTEGER y,CPickResult& result,_BOOL allHits = _FALSE);

protected:

	/** 
	 * Handle pick event.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void handlePickEvent(const D3DXEvent& d3dxEvent);

	/** 
	 * Handle move event.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void handleMoveEvent(const D3DXEvent& d3dxEvent);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent Event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_APPLICATION_H_
