// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
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
// FillJointProperties
//
///////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::FillJointProperties(CPhysicsJointObject* pJointObject)
{
#ifdef _DEBUG
	assert(pJointObject != NULL);
#endif
	//Get joint type
	_INTEGER type = pJointObject->getJointType();

	//Create property.
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"常规");

	{
		//Joint type.
		CNormalString jointType = L"未知";
		//Check base.
		if(type == CJointAttribute::classicBallJoint) jointType = L"经典球头链";
		else if(type == CJointAttribute::classicHingeJoint) jointType = L"经典转轴链";
		else if(type == CJointAttribute::classicSliderJoint) jointType = L"经典滑动链";
		else if(type == CJointAttribute::classicCorkscrewJoint) jointType = L"经典滑转链";
		else if(type == CJointAttribute::classicUniversalJoint) jointType = L"经典双轴链";
		else if(type == CJointAttribute::classicUpVectorJoint) jointType = L"经典自旋轴";
		else if(type == CJointAttribute::customBallJoint) jointType = L"C型球头链";
		else if(type == CJointAttribute::customHingeJoint) jointType = L"C型转轴链";
		else if(type == CJointAttribute::customSliderJoint) jointType = L"C型滑动链";
		else if(type == CJointAttribute::custom6DOFJoint) jointType = L"C型滑动链";

		//Create property.
		HANDLE_JOINT_TYPE = new CMFCPropertyGridProperty(L"链类型",
			jointType.getCString(), L"链接体类型。");
		//Enable editable.
		HANDLE_JOINT_TYPE->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_TYPE);

		//Get child.
		CWorldObject* child = pJointObject->getJointChild();

		//Create property.
		HANDLE_JOINT_CHILD_NAME = new CMFCPropertyGridProperty(L"子体名称",
			child != NULL ? child->getAlias().getCString() : _T(""), L"被链接的子物体全局名称。");
		//Disable editable.
		HANDLE_JOINT_CHILD_NAME->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_CHILD_NAME);

		//Get parent.
		CWorldObject* parent = pJointObject->getJointParent();

		//Create property.
		HANDLE_JOINT_PARENT_NAME = new CMFCPropertyGridProperty(L"父体名称",
			parent != NULL ? parent->getAlias().getCString() : _T(""), L"被链接的父物体全局名称。");
		//Disable editable.
		HANDLE_JOINT_PARENT_NAME->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_PARENT_NAME);

		//Check base.
		if(CJointAttribute::isClassicJoint(type))
		{
			//Get stiffness.
			float fStiffness = pJointObject->getJointAttribute().stiffness;

			//Create property.
			HANDLE_JOINT_STIFFNESS = new CMFCPropertyGridProperty(L"强硬度",
				(_variant_t) fStiffness, L"链接体的链接强硬度。该数值在0.0至1.0之间。");
			//Enable editable.
			HANDLE_JOINT_STIFFNESS->Enable(FALSE);
			//Add subitem.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_STIFFNESS);
		}

		//Get self collision.
		bool bSelfCollision = pJointObject->isSelfCollision() ? true : false;

		//Create property.
		HANDLE_JOINT_SELF_COLLISION = new CMFCPropertyGridProperty(L"自碰撞",
			(_variant_t) bSelfCollision, L"是否允许子体和父体之间发生碰撞检测。");
		//Enable editable.
		HANDLE_JOINT_SELF_COLLISION->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_SELF_COLLISION);
	}

	//Add property group.
	m_wndPropList.AddProperty(HANDLE_GROUP_MAJOR);

	//Get attribute.
	CJointAttribute attribute = pJointObject->getJointAttribute();
	//Check base.
	if(type == CJointAttribute::classicBallJoint)
	{
		//Create property.
		HANDLE_JOINT_BALL_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_BALL_LIMIT->SetDescription(L"球头链的主要参数。");

		{
			//Get max twist angle.
			float fMaxTwistAngle = attribute.jointData.jointClassicBall.maxTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE = new CMFCPropertyGridProperty(L"最大扭转角",
				(_variant_t) fMaxTwistAngle, L"球头链的最大扭转角度。一般该数值为0度至175度。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE);

			//Get max cone angle.
			float fMaxConeAngle = attribute.jointData.jointClassicBall.maxConeAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE = new CMFCPropertyGridProperty(L"最大圆锥角",
				(_variant_t) fMaxConeAngle, L"球头链可活动的最大圆锥角。一般该数值为0度至175度。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE);

			//Create property.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS = new CMFCPropertyGridProperty(L"锥体主方向");
			//Set description.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->SetDescription(L"球头链的锥体主方向。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS);

			{
				//Get vector.
				C4DVector3 axis(attribute.jointData.jointClassicBall.direction);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) axis.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) axis.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) axis.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_BALL_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::classicHingeJoint)
	{
		//Create property.
		HANDLE_JOINT_HINGE_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_HINGE_LIMIT->SetDescription(L"转轴链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS = new CMFCPropertyGridProperty(L"主方向轴");
			//Set description.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->SetDescription(L"转轴链的主旋转轴方向。");
			//Add item.
			HANDLE_JOINT_HINGE_LIMIT->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicHinge.direction);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_HINGE_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::classicSliderJoint)
	{
		//Create property.
		HANDLE_JOINT_SLIDER_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_SLIDER_LIMIT->SetDescription(L"滑动链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"主滑动方向");
			//Set description.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->SetDescription(L"滑动链的主滑动方向。");
			//Add item.
			HANDLE_JOINT_SLIDER_LIMIT->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicSlider.direction);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_SLIDER_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::classicCorkscrewJoint)
	{
		//Create property.
		HANDLE_JOINT_CORKSCREW_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_CORKSCREW_LIMIT->SetDescription(L"滑转链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"主滑动方向");
			//Set description.
			HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->SetDescription(L"滑转链的主滑动方向。");
			//Add item.
			HANDLE_JOINT_CORKSCREW_LIMIT->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicCorkscrew.direction);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_CORKSCREW_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::classicUniversalJoint)
	{
		//Create property.
		HANDLE_JOINT_UNIVERSAL_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_UNIVERSAL_LIMIT->SetDescription(L"双轴链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0 = new CMFCPropertyGridProperty(L"主转轴方向");
			//Set description.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->SetDescription(L"双轴链的主转轴方向。");
			//Add item.
			HANDLE_JOINT_UNIVERSAL_LIMIT->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUniversal.majorDirection);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z);
			}
		}

		{
			//Create property.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1 = new CMFCPropertyGridProperty(L"副转轴方向");
			//Set description.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->SetDescription(L"双轴链的副转轴方向。");
			//Add item.
			HANDLE_JOINT_UNIVERSAL_LIMIT->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUniversal.minorDirection);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_UNIVERSAL_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::classicUpVectorJoint)
	{
		//Create property.
		HANDLE_JOINT_UPVECTOR_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_UPVECTOR_LIMIT->SetDescription(L"自旋链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"自旋轴方向");
			//Set description.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->SetDescription(L"自旋链的自旋轴方向。");
			//Add item.
			HANDLE_JOINT_UPVECTOR_LIMIT->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUpVector.direction);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_UPVECTOR_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::custom6DOFJoint)
	{
		//Create property.
		HANDLE_JOINT_LINEAR_LIMIT = new CMFCPropertyGridProperty(L"平动参数");
		//Set description.
		HANDLE_JOINT_LINEAR_LIMIT->SetDescription(L"自由链的主要平动参数。");

		{
			//Create property.
			HANDLE_JOINT_LINEAR_LIMIT_MIN = new CMFCPropertyGridProperty(L"最小限制点");
			//Set description.
			HANDLE_JOINT_LINEAR_LIMIT_MIN->SetDescription(L"自由链平移的最小限制点。");
			//Add item.
			HANDLE_JOINT_LINEAR_LIMIT->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN);

			{
				//Get vector.
				C4DVector3 vMinLinearLimits(attribute.jointData.jointCustom6DOF.minLinearLimits);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) vMinLinearLimits.x(), L"在世界坐标系下，最小限制点的x坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_X);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) vMinLinearLimits.y(), L"在世界坐标系下，最小限制点的y坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_Y);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_Z = new CMFCPropertyGridProperty(L"z坐标",
					(_variant_t) vMinLinearLimits.z(), L"在世界坐标系下，最小限制点的z坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_Z);
			}

			//Create property.
			HANDLE_JOINT_LINEAR_LIMIT_MAX = new CMFCPropertyGridProperty(L"最大限制点");
			//Set description.
			HANDLE_JOINT_LINEAR_LIMIT_MAX->SetDescription(L"自由链平移的最大限制点。");
			//Add item.
			HANDLE_JOINT_LINEAR_LIMIT->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX);

			{
				//Get vector.
				C4DVector3 vMaxLinearLimits(attribute.jointData.jointCustom6DOF.maxLinearLimits);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_X = new CMFCPropertyGridProperty(L"x坐标",
					(_variant_t) vMaxLinearLimits.x(), L"在世界坐标系下，最小限制点的x坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_X);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_Y = new CMFCPropertyGridProperty(L"y坐标",
					(_variant_t) vMaxLinearLimits.y(), L"在世界坐标系下，最小限制点的y坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_Y);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_Z = new CMFCPropertyGridProperty(L"z坐标",
					(_variant_t) vMaxLinearLimits.z(), L"在世界坐标系下，最小限制点的z坐标数值。");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_LINEAR_LIMIT);

		//Create property.
		HANDLE_JOINT_ANGULA_LIMIT = new CMFCPropertyGridProperty(L"转动参数");
		//Set description.
		HANDLE_JOINT_ANGULA_LIMIT->SetDescription(L"自由链转动的主要转动参数。");

		{
			//Create property.
			HANDLE_JOINT_ANGULA_LIMIT_MIN = new CMFCPropertyGridProperty(L"最小转动角（角度）");
			//Set description.
			HANDLE_JOINT_ANGULA_LIMIT_MIN->SetDescription(L"自由链转动的最小转动角。注：单位为角度。数值范围为-175度至175度。");
			//Add item.
			HANDLE_JOINT_ANGULA_LIMIT->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN);

			{
				//Get vector.
				C4DVector3 vMinAngulaLimits(attribute.jointData.jointCustom6DOF.minAngulaLimits);
				//Convert to eular angle.
				vMinAngulaLimits = vMinAngulaLimits * 180.0f / D3DX_PI;

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_X = new CMFCPropertyGridProperty(L"绕x轴",
					(_variant_t) vMinAngulaLimits.x(), L"在世界坐标系下，绕x轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_X);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_Y = new CMFCPropertyGridProperty(L"绕x轴",
					(_variant_t) vMinAngulaLimits.y(), L"在世界坐标系下，绕y轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_Y);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_Z = new CMFCPropertyGridProperty(L"绕z轴",
					(_variant_t) vMinAngulaLimits.z(), L"在世界坐标系下，绕z轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_Z);
			}

			//Create property.
			HANDLE_JOINT_ANGULA_LIMIT_MAX = new CMFCPropertyGridProperty(L"最大转动角（角度）");
			//Set description.
			HANDLE_JOINT_ANGULA_LIMIT_MAX->SetDescription(L"自由链转动的最大转动角。注：单位为角度。数值范围为-175度至175度。");
			//Add item.
			HANDLE_JOINT_ANGULA_LIMIT->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX);

			{
				//Get vector.
				C4DVector3 vMaxAngulaLimits(attribute.jointData.jointCustom6DOF.maxAngulaLimits);
				//Convert to eular angle.
				vMaxAngulaLimits = vMaxAngulaLimits * 180.0 / D3DX_PI;

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_X = new CMFCPropertyGridProperty(L"绕x轴",
					(_variant_t) vMaxAngulaLimits.x(), L"在世界坐标系下，绕x轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_X);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_Y = new CMFCPropertyGridProperty(L"绕y轴",
					(_variant_t) vMaxAngulaLimits.y(), L"在世界坐标系下，绕y轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_Y);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_Z = new CMFCPropertyGridProperty(L"绕z轴",
					(_variant_t) vMaxAngulaLimits.z(), L"在世界坐标系下，绕z轴转动的角度。");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_ANGULA_LIMIT);

		//Create property.
		HANDLE_JOINT_DIRECTION = new CMFCPropertyGridProperty(L"方向参数");
		//Set description.
		HANDLE_JOINT_DIRECTION->SetDescription(L"自由链转动的主要方向参数。");

		{
			//Create property.
			HANDLE_JOINT_MAJOR_DIRECTION = new CMFCPropertyGridProperty(L"主方向");
			//Set description.
			HANDLE_JOINT_MAJOR_DIRECTION->SetDescription(L"自由链的主方向。");
			//Add property group.
			HANDLE_JOINT_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustom6DOF.majorDirection);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Z);
			}

			//Create property.
			HANDLE_JOINT_MINOR_DIRECTION = new CMFCPropertyGridProperty(L"副方向");
			//Set description.
			HANDLE_JOINT_MINOR_DIRECTION->SetDescription(L"自由链的副方向。");
			//Add property group.
			HANDLE_JOINT_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustom6DOF.minorDirection);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MINOR_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MINOR_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MINOR_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_DIRECTION);
	}
	//Check base.
	else if(type == CJointAttribute::customBallJoint)
	{
		//Create property.
		HANDLE_JOINT_BALL_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_BALL_LIMIT->SetDescription(L"球链接的主要参数。");

		{
			//Get min twist angle.
			float fMinTwistAngle = attribute.jointData.jointCustomBall.minTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE = new CMFCPropertyGridProperty(L"最小扭转角（角度）",
				(_variant_t) fMinTwistAngle, L"球链接的最小扭转角。注：单位为角度。数值范为-180度至+180度。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE);

			//Get max twist angle.
			float fMaxTwistAngle = attribute.jointData.jointCustomBall.maxTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE = new CMFCPropertyGridProperty(L"最大扭转角（角度）",
				(_variant_t) fMaxTwistAngle, L"球链接的最大扭转角。注：单位为角度。数值范为-180度至+180度。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE);

			//Get max cone angle.
			float fMaxConeAngle = attribute.jointData.jointCustomBall.maxConeAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE = new CMFCPropertyGridProperty(L"最大锥体角（角度）",
				(_variant_t) fMaxConeAngle, L"球链接的最大锥体角。注：单位为角度。数值范围为0度～175度。");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE);

			//Create property.
			HANDLE_JOINT_MAJOR_DIRECTION = new CMFCPropertyGridProperty(L"主方向");
			//Set description.
			HANDLE_JOINT_MAJOR_DIRECTION->SetDescription(L"球链接的主方向。");
			//Add subitem.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomBall.direction);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_BALL_LIMIT);
	}
	//Check base.
	else if(type == CJointAttribute::customHingeJoint)
	{
		//Create property.
		HANDLE_JOINT_HINGE_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_HINGE_LIMIT->SetDescription(L"转轴链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS = new CMFCPropertyGridProperty(L"主方向轴");
			//Set description.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->SetDescription(L"转轴链的主旋转轴方向。");
			//Add item.
			HANDLE_JOINT_HINGE_LIMIT->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomHinge.direction);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_HINGE_LIMIT);
	}
	else if(type == CJointAttribute::customSliderJoint)
	{
		//Create property.
		HANDLE_JOINT_SLIDER_LIMIT = new CMFCPropertyGridProperty(L"参数");
		//Set description.
		HANDLE_JOINT_SLIDER_LIMIT->SetDescription(L"滑动链的主要参数。");

		{
			//Create property.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"主滑动方向");
			//Set description.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->SetDescription(L"滑动链的主滑动方向。");
			//Add item.
			HANDLE_JOINT_SLIDER_LIMIT->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomSlider.direction);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x轴向",
					(_variant_t) direction.x(), L"在世界坐标系中，沿x轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y轴向",
					(_variant_t) direction.y(), L"在世界坐标系中，沿y轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z轴向",
					(_variant_t) direction.z(), L"在世界坐标系中，沿z轴方向数值。");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_SLIDER_LIMIT);
	}
}

