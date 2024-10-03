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

#include "ObjectSketcher.h"
#include "JointObjectSketcher.h"

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
// OnJointPropertyChanged
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::OnJointPropertyChanged(CPhysicsJointObject* pJointObject,CMFCPropertyGridProperty *pProp)
{
#ifdef _DEBUG
	assert(pJointObject != NULL && pProp != NULL);
#endif
	//Get attribute.
	int type = pJointObject->getJointType();
	//Check type of object.
	if(type == CJointAttribute::classicBallJoint)
	{
		//Check handle.
		if(pProp == HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE)
		{
			//Set twist angle.
			pJointObject->getJointAttribute().jointData.jointClassicBall.maxTwistAngle = pProp->GetValue().fltVal * D3DX_PI / 180.0f;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE)
		{
			//Set cone angle.
			pJointObject->getJointAttribute().jointData.jointClassicBall.maxConeAngle = pProp->GetValue().fltVal * D3DX_PI / 180.0f;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicBall.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicBall.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicBall.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::classicHingeJoint)
	{
		if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicHinge.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicHinge.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicHinge.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::classicSliderJoint)
	{
		if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicSlider.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicSlider.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicSlider.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::classicCorkscrewJoint)
	{
		if(pProp == HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicCorkscrew.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicCorkscrew.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicCorkscrew.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::classicUniversalJoint)
	{
		if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.majorDirection[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.majorDirection[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.majorDirection[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.minorDirection[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.minorDirection[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUniversal.minorDirection[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::classicUpVectorJoint)
	{
		if(pProp == HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUpVector.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUpVector.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointClassicUpVector.direction[2] = pProp->GetValue().fltVal;
		}
	}
	else if(type == CJointAttribute::custom6DOFJoint)
	{
		if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MIN_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minLinearLimits[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MIN_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minLinearLimits[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MIN_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minLinearLimits[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MAX_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxLinearLimits[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MAX_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxLinearLimits[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_LINEAR_LIMIT_MAX_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxLinearLimits[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MIN_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minAngulaLimits[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MIN_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minAngulaLimits[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MIN_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minAngulaLimits[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MAX_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxAngulaLimits[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MAX_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxAngulaLimits[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_ANGULA_LIMIT_MAX_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.maxAngulaLimits[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.majorDirection[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.majorDirection[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.majorDirection[2] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MINOR_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minorDirection[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MINOR_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minorDirection[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MINOR_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustom6DOF.minorDirection[2] = pProp->GetValue().fltVal;
		}
	}
	else if(type == CJointAttribute::customBallJoint)
	{
		if(pProp == HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.minTwistAngle = pProp->GetValue().fltVal * D3DX_PI / 180.0f;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.maxTwistAngle = pProp->GetValue().fltVal * D3DX_PI / 180.0f;
		}
		else if(pProp == HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.maxConeAngle = pProp->GetValue().fltVal * D3DX_PI / 180.0f;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_MAJOR_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomBall.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::customHingeJoint)
	{
		if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomHinge.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomHinge.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomHinge.direction[2] = pProp->GetValue().fltVal;
		}
	}
	//Check type of object.
	else if(type == CJointAttribute::customSliderJoint)
	{
		if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomSlider.direction[0] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomSlider.direction[1] = pProp->GetValue().fltVal;
		}
		else if(pProp == HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z)
		{
			//Set value.
			pJointObject->getJointAttribute().jointData.jointCustomSlider.direction[2] = pProp->GetValue().fltVal;
		}
	}
}