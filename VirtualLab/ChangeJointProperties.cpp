// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "4DProperties.h"
#include "VirtualLabDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MAINFRAME											((CMainFrame *)GetTopLevelFrame())

///////////////////////////////////////////////////////////////////////////////
//
// ChangeJointProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::ChangeJointProperties(CPhysicsJointObject* pJointObject)
{
#ifdef _DEBUG
	assert(pJointObject != NULL);
#endif
	//Get type.
	_INTEGER type = pJointObject->getJointType();
	//Get attribute.
	CJointAttribute attribute = pJointObject->getJointAttribute();
	//Check base.
	if(type == CJointAttribute::classicBallJoint)
	{
		//Get vector.
		C4DVector3 direction(attribute.jointData.jointClassicBall.direction);
		//Check handle.
		if(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X != NULL)
		{
			//Set value.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X->SetValue((_variant_t) direction.x());
		}
		//Check handle.
		if(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y != NULL)
		{
			//Set value.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y->SetValue((_variant_t) direction.y());
		}
		//Check handle.
		if(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z != NULL)
		{
			//Set value.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z->SetValue((_variant_t) direction.z());
		}
	}
	//Check base.
	else if(type == CJointAttribute::classicHingeJoint)
	{
		//Get vector.
		C4DVector3 direction(attribute.jointData.jointClassicHinge.direction);
		//Check handle.
		if(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X != NULL)
		{
			//Set value.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X->SetValue((_variant_t) direction.x());
		}
		//Check handle.
		if(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y != NULL)
		{
			//Set value.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y->SetValue((_variant_t) direction.y());
		}
		//Check handle.
		if(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z != NULL)
		{
			//Set value.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z->SetValue((_variant_t) direction.z());
		}
	}
	//Check base.
	else if(type == CJointAttribute::classicSliderJoint)
	{

	}
	//Check base.
	else if(type == CJointAttribute::classicCorkscrewJoint)
	{

	}
	//Check base.
	else if(type == CJointAttribute::classicUniversalJoint)
	{

	}
	//Check base.
	else if(type == CJointAttribute::classicUpVectorJoint)
	{
		//Get vector.
		C4DVector3 direction(attribute.jointData.jointClassicUpVector.direction);
		//Check handle.
		if(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X != NULL)
		{
			//Set value.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X->SetValue((_variant_t) direction.x());
		}
		//Check handle.
		if(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y != NULL)
		{
			//Set value.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y->SetValue((_variant_t) direction.y());
		}
		//Check handle.
		if(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z != NULL)
		{
			//Set value.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z->SetValue((_variant_t) direction.z());
		}
	}
	//Check base.
	else if(type == CJointAttribute::custom6DOFJoint)
	{

	}
}
