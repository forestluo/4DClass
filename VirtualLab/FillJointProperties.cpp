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
	HANDLE_GROUP_MAJOR = new CMFCPropertyGridProperty(L"����");

	{
		//Joint type.
		CNormalString jointType = L"δ֪";
		//Check base.
		if(type == CJointAttribute::classicBallJoint) jointType = L"������ͷ��";
		else if(type == CJointAttribute::classicHingeJoint) jointType = L"����ת����";
		else if(type == CJointAttribute::classicSliderJoint) jointType = L"���们����";
		else if(type == CJointAttribute::classicCorkscrewJoint) jointType = L"���们ת��";
		else if(type == CJointAttribute::classicUniversalJoint) jointType = L"����˫����";
		else if(type == CJointAttribute::classicUpVectorJoint) jointType = L"����������";
		else if(type == CJointAttribute::customBallJoint) jointType = L"C����ͷ��";
		else if(type == CJointAttribute::customHingeJoint) jointType = L"C��ת����";
		else if(type == CJointAttribute::customSliderJoint) jointType = L"C�ͻ�����";
		else if(type == CJointAttribute::custom6DOFJoint) jointType = L"C�ͻ�����";

		//Create property.
		HANDLE_JOINT_TYPE = new CMFCPropertyGridProperty(L"������",
			jointType.getCString(), L"���������͡�");
		//Enable editable.
		HANDLE_JOINT_TYPE->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_TYPE);

		//Get child.
		CWorldObject* child = pJointObject->getJointChild();

		//Create property.
		HANDLE_JOINT_CHILD_NAME = new CMFCPropertyGridProperty(L"��������",
			child != NULL ? child->getAlias().getCString() : _T(""), L"�����ӵ�������ȫ�����ơ�");
		//Disable editable.
		HANDLE_JOINT_CHILD_NAME->Enable(FALSE);
		//Add subitem.
		HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_CHILD_NAME);

		//Get parent.
		CWorldObject* parent = pJointObject->getJointParent();

		//Create property.
		HANDLE_JOINT_PARENT_NAME = new CMFCPropertyGridProperty(L"��������",
			parent != NULL ? parent->getAlias().getCString() : _T(""), L"�����ӵĸ�����ȫ�����ơ�");
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
			HANDLE_JOINT_STIFFNESS = new CMFCPropertyGridProperty(L"ǿӲ��",
				(_variant_t) fStiffness, L"�����������ǿӲ�ȡ�����ֵ��0.0��1.0֮�䡣");
			//Enable editable.
			HANDLE_JOINT_STIFFNESS->Enable(FALSE);
			//Add subitem.
			HANDLE_GROUP_MAJOR->AddSubItem(HANDLE_JOINT_STIFFNESS);
		}

		//Get self collision.
		bool bSelfCollision = pJointObject->isSelfCollision() ? true : false;

		//Create property.
		HANDLE_JOINT_SELF_COLLISION = new CMFCPropertyGridProperty(L"����ײ",
			(_variant_t) bSelfCollision, L"�Ƿ���������͸���֮�䷢����ײ��⡣");
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
		HANDLE_JOINT_BALL_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_BALL_LIMIT->SetDescription(L"��ͷ������Ҫ������");

		{
			//Get max twist angle.
			float fMaxTwistAngle = attribute.jointData.jointClassicBall.maxTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE = new CMFCPropertyGridProperty(L"���Ťת��",
				(_variant_t) fMaxTwistAngle, L"��ͷ�������Ťת�Ƕȡ�һ�����ֵΪ0����175�ȡ�");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE);

			//Get max cone angle.
			float fMaxConeAngle = attribute.jointData.jointClassicBall.maxConeAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE = new CMFCPropertyGridProperty(L"���Բ׶��",
				(_variant_t) fMaxConeAngle, L"��ͷ���ɻ�����Բ׶�ǡ�һ�����ֵΪ0����175�ȡ�");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE);

			//Create property.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS = new CMFCPropertyGridProperty(L"׶��������");
			//Set description.
			HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->SetDescription(L"��ͷ����׶��������");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS);

			{
				//Get vector.
				C4DVector3 axis(attribute.jointData.jointClassicBall.direction);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) axis.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_X);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) axis.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS->AddSubItem(HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Y);

				//Create property.
				HANDLE_JOINT_BALL_LIMIT_CONE_AXIS_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) axis.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_HINGE_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_HINGE_LIMIT->SetDescription(L"ת��������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS = new CMFCPropertyGridProperty(L"��������");
			//Set description.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->SetDescription(L"ת����������ת�᷽��");
			//Add item.
			HANDLE_JOINT_HINGE_LIMIT->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicHinge.direction);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_SLIDER_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_SLIDER_LIMIT->SetDescription(L"����������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"����������");
			//Set description.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->SetDescription(L"������������������");
			//Add item.
			HANDLE_JOINT_SLIDER_LIMIT->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicSlider.direction);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_CORKSCREW_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_CORKSCREW_LIMIT->SetDescription(L"��ת������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"����������");
			//Set description.
			HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->SetDescription(L"��ת��������������");
			//Add item.
			HANDLE_JOINT_CORKSCREW_LIMIT->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicCorkscrew.direction);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_CORKSCREW_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_UNIVERSAL_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_UNIVERSAL_LIMIT->SetDescription(L"˫��������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0 = new CMFCPropertyGridProperty(L"��ת�᷽��");
			//Set description.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->SetDescription(L"˫��������ת�᷽��");
			//Add item.
			HANDLE_JOINT_UNIVERSAL_LIMIT->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUniversal.majorDirection);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_X);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Y);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION0_Z);
			}
		}

		{
			//Create property.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1 = new CMFCPropertyGridProperty(L"��ת�᷽��");
			//Set description.
			HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->SetDescription(L"˫�����ĸ�ת�᷽��");
			//Add item.
			HANDLE_JOINT_UNIVERSAL_LIMIT->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUniversal.minorDirection);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_X);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Set enabled.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y->Enable(_FALSE);
				//Add subitem.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1->AddSubItem(HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Y);

				//Create property.
				HANDLE_JOINT_UNIVERSAL_LIMIT_DIRECTION1_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_UPVECTOR_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_UPVECTOR_LIMIT->SetDescription(L"����������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"�����᷽��");
			//Set description.
			HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->SetDescription(L"�������������᷽��");
			//Add item.
			HANDLE_JOINT_UPVECTOR_LIMIT->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointClassicUpVector.direction);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_UPVECTOR_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_LINEAR_LIMIT = new CMFCPropertyGridProperty(L"ƽ������");
		//Set description.
		HANDLE_JOINT_LINEAR_LIMIT->SetDescription(L"����������Ҫƽ��������");

		{
			//Create property.
			HANDLE_JOINT_LINEAR_LIMIT_MIN = new CMFCPropertyGridProperty(L"��С���Ƶ�");
			//Set description.
			HANDLE_JOINT_LINEAR_LIMIT_MIN->SetDescription(L"������ƽ�Ƶ���С���Ƶ㡣");
			//Add item.
			HANDLE_JOINT_LINEAR_LIMIT->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN);

			{
				//Get vector.
				C4DVector3 vMinLinearLimits(attribute.jointData.jointCustom6DOF.minLinearLimits);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) vMinLinearLimits.x(), L"����������ϵ�£���С���Ƶ��x������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_X);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) vMinLinearLimits.y(), L"����������ϵ�£���С���Ƶ��y������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_Y);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MIN_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) vMinLinearLimits.z(), L"����������ϵ�£���С���Ƶ��z������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MIN->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MIN_Z);
			}

			//Create property.
			HANDLE_JOINT_LINEAR_LIMIT_MAX = new CMFCPropertyGridProperty(L"������Ƶ�");
			//Set description.
			HANDLE_JOINT_LINEAR_LIMIT_MAX->SetDescription(L"������ƽ�Ƶ�������Ƶ㡣");
			//Add item.
			HANDLE_JOINT_LINEAR_LIMIT->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX);

			{
				//Get vector.
				C4DVector3 vMaxLinearLimits(attribute.jointData.jointCustom6DOF.maxLinearLimits);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) vMaxLinearLimits.x(), L"����������ϵ�£���С���Ƶ��x������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_X);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) vMaxLinearLimits.y(), L"����������ϵ�£���С���Ƶ��y������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_Y);

				//Create property.
				HANDLE_JOINT_LINEAR_LIMIT_MAX_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) vMaxLinearLimits.z(), L"����������ϵ�£���С���Ƶ��z������ֵ��");
				//Add subitem.
				HANDLE_JOINT_LINEAR_LIMIT_MAX->AddSubItem(HANDLE_JOINT_LINEAR_LIMIT_MAX_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_LINEAR_LIMIT);

		//Create property.
		HANDLE_JOINT_ANGULA_LIMIT = new CMFCPropertyGridProperty(L"ת������");
		//Set description.
		HANDLE_JOINT_ANGULA_LIMIT->SetDescription(L"������ת������Ҫת��������");

		{
			//Create property.
			HANDLE_JOINT_ANGULA_LIMIT_MIN = new CMFCPropertyGridProperty(L"��Сת���ǣ��Ƕȣ�");
			//Set description.
			HANDLE_JOINT_ANGULA_LIMIT_MIN->SetDescription(L"������ת������Сת���ǡ�ע����λΪ�Ƕȡ���ֵ��ΧΪ-175����175�ȡ�");
			//Add item.
			HANDLE_JOINT_ANGULA_LIMIT->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN);

			{
				//Get vector.
				C4DVector3 vMinAngulaLimits(attribute.jointData.jointCustom6DOF.minAngulaLimits);
				//Convert to eular angle.
				vMinAngulaLimits = vMinAngulaLimits * 180.0f / D3DX_PI;

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_X = new CMFCPropertyGridProperty(L"��x��",
					(_variant_t) vMinAngulaLimits.x(), L"����������ϵ�£���x��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_X);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_Y = new CMFCPropertyGridProperty(L"��x��",
					(_variant_t) vMinAngulaLimits.y(), L"����������ϵ�£���y��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_Y);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MIN_Z = new CMFCPropertyGridProperty(L"��z��",
					(_variant_t) vMinAngulaLimits.z(), L"����������ϵ�£���z��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MIN->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MIN_Z);
			}

			//Create property.
			HANDLE_JOINT_ANGULA_LIMIT_MAX = new CMFCPropertyGridProperty(L"���ת���ǣ��Ƕȣ�");
			//Set description.
			HANDLE_JOINT_ANGULA_LIMIT_MAX->SetDescription(L"������ת�������ת���ǡ�ע����λΪ�Ƕȡ���ֵ��ΧΪ-175����175�ȡ�");
			//Add item.
			HANDLE_JOINT_ANGULA_LIMIT->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX);

			{
				//Get vector.
				C4DVector3 vMaxAngulaLimits(attribute.jointData.jointCustom6DOF.maxAngulaLimits);
				//Convert to eular angle.
				vMaxAngulaLimits = vMaxAngulaLimits * 180.0 / D3DX_PI;

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_X = new CMFCPropertyGridProperty(L"��x��",
					(_variant_t) vMaxAngulaLimits.x(), L"����������ϵ�£���x��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_X);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_Y = new CMFCPropertyGridProperty(L"��y��",
					(_variant_t) vMaxAngulaLimits.y(), L"����������ϵ�£���y��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_Y);

				//Create property.
				HANDLE_JOINT_ANGULA_LIMIT_MAX_Z = new CMFCPropertyGridProperty(L"��z��",
					(_variant_t) vMaxAngulaLimits.z(), L"����������ϵ�£���z��ת���ĽǶȡ�");
				//Add subitem.
				HANDLE_JOINT_ANGULA_LIMIT_MAX->AddSubItem(HANDLE_JOINT_ANGULA_LIMIT_MAX_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_ANGULA_LIMIT);

		//Create property.
		HANDLE_JOINT_DIRECTION = new CMFCPropertyGridProperty(L"�������");
		//Set description.
		HANDLE_JOINT_DIRECTION->SetDescription(L"������ת������Ҫ���������");

		{
			//Create property.
			HANDLE_JOINT_MAJOR_DIRECTION = new CMFCPropertyGridProperty(L"������");
			//Set description.
			HANDLE_JOINT_MAJOR_DIRECTION->SetDescription(L"��������������");
			//Add property group.
			HANDLE_JOINT_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustom6DOF.majorDirection);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Z);
			}

			//Create property.
			HANDLE_JOINT_MINOR_DIRECTION = new CMFCPropertyGridProperty(L"������");
			//Set description.
			HANDLE_JOINT_MINOR_DIRECTION->SetDescription(L"�������ĸ�����");
			//Add property group.
			HANDLE_JOINT_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustom6DOF.minorDirection);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MINOR_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MINOR_DIRECTION->AddSubItem(HANDLE_JOINT_MINOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MINOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_BALL_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_BALL_LIMIT->SetDescription(L"�����ӵ���Ҫ������");

		{
			//Get min twist angle.
			float fMinTwistAngle = attribute.jointData.jointCustomBall.minTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE = new CMFCPropertyGridProperty(L"��СŤת�ǣ��Ƕȣ�",
				(_variant_t) fMinTwistAngle, L"�����ӵ���СŤת�ǡ�ע����λΪ�Ƕȡ���ֵ��Ϊ-180����+180�ȡ�");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MIN_TWIST_ANGLE);

			//Get max twist angle.
			float fMaxTwistAngle = attribute.jointData.jointCustomBall.maxTwistAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE = new CMFCPropertyGridProperty(L"���Ťת�ǣ��Ƕȣ�",
				(_variant_t) fMaxTwistAngle, L"�����ӵ����Ťת�ǡ�ע����λΪ�Ƕȡ���ֵ��Ϊ-180����+180�ȡ�");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_TWIST_ANGLE);

			//Get max cone angle.
			float fMaxConeAngle = attribute.jointData.jointCustomBall.maxConeAngle * 180.0f / D3DX_PI;
			//Create property.
			HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE = new CMFCPropertyGridProperty(L"���׶��ǣ��Ƕȣ�",
				(_variant_t) fMaxConeAngle, L"�����ӵ����׶��ǡ�ע����λΪ�Ƕȡ���ֵ��ΧΪ0�ȡ�175�ȡ�");
			//Add item.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_BALL_LIMIT_MAX_CONE_ANGLE);

			//Create property.
			HANDLE_JOINT_MAJOR_DIRECTION = new CMFCPropertyGridProperty(L"������");
			//Set description.
			HANDLE_JOINT_MAJOR_DIRECTION->SetDescription(L"�����ӵ�������");
			//Add subitem.
			HANDLE_JOINT_BALL_LIMIT->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomBall.direction);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_MAJOR_DIRECTION->AddSubItem(HANDLE_JOINT_MAJOR_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_MAJOR_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_HINGE_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_HINGE_LIMIT->SetDescription(L"ת��������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS = new CMFCPropertyGridProperty(L"��������");
			//Set description.
			HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->SetDescription(L"ת����������ת�᷽��");
			//Add item.
			HANDLE_JOINT_HINGE_LIMIT->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomHinge.direction);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_X);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS->AddSubItem(HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Y);

				//Create property.
				HANDLE_JOINT_HINGE_LIMIT_MAJOR_AXIS_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
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
		HANDLE_JOINT_SLIDER_LIMIT = new CMFCPropertyGridProperty(L"����");
		//Set description.
		HANDLE_JOINT_SLIDER_LIMIT->SetDescription(L"����������Ҫ������");

		{
			//Create property.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION = new CMFCPropertyGridProperty(L"����������");
			//Set description.
			HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->SetDescription(L"������������������");
			//Add item.
			HANDLE_JOINT_SLIDER_LIMIT->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION);

			{
				//Get vector.
				C4DVector3 direction(attribute.jointData.jointCustomSlider.direction);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X = new CMFCPropertyGridProperty(L"x����",
					(_variant_t) direction.x(), L"����������ϵ�У���x�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_X);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y = new CMFCPropertyGridProperty(L"y����",
					(_variant_t) direction.y(), L"����������ϵ�У���y�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Y);

				//Create property.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z = new CMFCPropertyGridProperty(L"z����",
					(_variant_t) direction.z(), L"����������ϵ�У���z�᷽����ֵ��");
				//Add subitem.
				HANDLE_JOINT_SLIDER_LIMIT_DIRECTION->AddSubItem(HANDLE_JOINT_SLIDER_LIMIT_DIRECTION_Z);
			}
		}

		//Add property group.
		m_wndPropList.AddProperty(HANDLE_JOINT_SLIDER_LIMIT);
	}
}

