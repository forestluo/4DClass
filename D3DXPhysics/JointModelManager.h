///////////////////////////////////////////////////////////////////////////////
//
// JointModelManager.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_MODEL_MANAGER_H_
#define _JOINT_MODEL_MANAGER_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldGroup.h"
#include "JointObject.h"
#include "ResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointModelManager
//
///////////////////////////////////////////////////////////////////////////////

class CJointModelManager :
	public virtual CWorldGroup
{
public:
	CJointModelManager(void);
	virtual ~CJointModelManager(void);

public:

	/**
	 * Create joint.
	 *
	 * @param resourceManager Resource manager.
	 * @param jointType Type of joint.
	 * @return
	 *     <p>Joint object.</p>
	 */
	CJointObject* createJoint(CResourceManager* resourceManager,
								_INTEGER jointType);

	/**
	 * Create joint.
	 *
	 * @param resourceManager Resource manager.
	 * @param attribute Attribute of joint.
	 * @return
	 *     <p>Joint object.</p>
	 */
	CJointObject* createJoint(CResourceManager* resourceManager,
								const CJointAttribute& attribute);

public:

	/**
	 * Create joint.
	 *
	 * @param resourceManager Resource
	 * @param jointType Type of joint.
	 * @param childName Name of child.
	 * @param position Position of model.
	 * @param parentName Name of parent.
	 * @return
	 *     <p>Joint object.</p>
	 */
	CJointObject* createJoint(CResourceManager* resourceManager,
								_INTEGER jointType,
								const CNormalString& childName,
								const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f),
								const CNormalString& parentName = L"");

	/**
	 * Create joint.
	 *
	 * @param resourceManager Resource
	 * @param attribute Attribute of joint.
	 * @param childName Name of child.
	 * @param position Position of model.
	 * @param parentName Name of parent.
	 * @return
	 *     <p>Joint object.</p>
	 */
	CJointObject* createJoint(CResourceManager* resourceManager,
								const CJointAttribute& attribute,
								const CNormalString& childName,
								const C4DVector3& position = C4DVector3(0.0f,0.0f,0.0f),
								const CNormalString& parentName = L"");
};

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_MODEL_MANAGER_H_
