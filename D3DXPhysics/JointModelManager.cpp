///////////////////////////////////////////////////////////////////////////////
//
// JointModelManager.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "JointModelManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "JointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// CJointModelManager
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CJointModelManager::CJointModelManager(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CJointModelManager
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CJointModelManager::~CJointModelManager(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject* CJointModelManager::createJoint(CResourceManager* resourceManager,
												_INTEGER jointType)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif
	//Joint object.
	CJointObject* joint = new CJointObject(jointType);
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Set name.
	joint->setAlias(L"�����ᣨ",L"��");
	//Create objects of joint.
	joint->createObjects(resourceManager);
	//Add joint.
	CWorldGroup::addObject(joint);
	//Return result.
	return joint;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject* CJointModelManager::createJoint(CResourceManager* resourceManager,
												const CJointAttribute& attribute)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif
	//Joint object.
	CJointObject* joint = new CJointObject(attribute);
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Check type.
	if(attribute.getType() == CJointAttribute::classicBallJoint)
	{
		//Set name.
		joint->setAlias(L"������ͷ����",L"��");
	}
	else if(attribute.getType() == CJointAttribute::classicCorkscrewJoint)
	{
		//Set name.
		joint->setAlias(L"���们ת����",L"��");
	}
	else if(attribute.getType() == CJointAttribute::classicHingeJoint)
	{
		//Set name.
		joint->setAlias(L"����ת������",L"��");
	}
	else if(attribute.getType() == CJointAttribute::classicSliderJoint)
	{
		//Set name.
		joint->setAlias(L"���们������",L"��");
	}
	else if(attribute.getType() == CJointAttribute::classicUniversalJoint)
	{
		//Set name.
		joint->setAlias(L"����˫������",L"��");
	}
	else if(attribute.getType() == CJointAttribute::classicUpVectorJoint)
	{
		//Set name.
		joint->setAlias(L"���������ᣨ",L"��");
	}
	else if(attribute.getType() == CJointAttribute::custom6DOFJoint)
	{
		//Set name.
		joint->setAlias(L"C����������",L"��");
	}
	else if(attribute.getType() == CJointAttribute::customBallJoint)
	{
		//Set name.
		joint->setAlias(L"C����ͷ����",L"��");
	}
	else if(attribute.getType() == CJointAttribute::customHingeJoint)
	{
		//Set name.
		joint->setAlias(L"C��ת������",L"��");
	}
	else if(attribute.getType() == CJointAttribute::customSliderJoint)
	{
		//Set name.
		joint->setAlias(L"C�ͻ�������",L"��");
	}
	else
	{
		//Set name.
		joint->setAlias(L"δ֪�����ͣ�",L"��");
	}
	//Create objects of joint.
	joint->createObjects(resourceManager);
	//Add joint.
	CWorldGroup::addObject(joint);
	//Return result.
	return joint;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject* CJointModelManager::createJoint(CResourceManager* resourceManager,
												_INTEGER jointType,
												const CNormalString& childName,
												const C4DVector3& position,
												const CNormalString& parentName)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Get child.
	CWorldObject* child;
	//Check name.
	if(childName.length() <= 0)
	{
		//Set child.
		child = (CWorldObject *)_NULL;
	}
	else
	{
		//Get child.
		child = getObject(childName);
	}

	//Get parent.
	CWorldObject* parent;
	//Check name.
	if(parentName.length() <= 0)
	{
		//Set parent.
		parent = (CWorldObject *)_NULL;
	}
	else
	{
		//Get parent.
		parent = getObject(parentName);
	}

	//Create joint.
	CJointObject* joint = createJoint(resourceManager,jointType);
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Set child.
	if(child != _NULL) joint->setJointChild(child);
	//Set parent.
	if(parent != _NULL) joint->setJointParent(parent);
	//Set position.
	joint->setPosition(position);
	//Return result.
	return joint;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateJoint
//
/////////////////////////////////////////////////////////////////////////////////

CJointObject* CJointModelManager::createJoint(CResourceManager* resourceManager,
												const CJointAttribute& attribute,
												const CNormalString& childName,
												const C4DVector3& position,
												const CNormalString& parentName)
{
#ifdef _DEBUG
	assert(resourceManager != _NULL);
#endif

	//Get child.
	CWorldObject* child;
	//Check name.
	if(childName.length() <= 0)
	{
		//Set child.
		child = (CWorldObject *)_NULL;
	}
	else
	{
		//Get child.
		child = getObject(childName);
	}

	//Get parent.
	CWorldObject* parent;
	//Check name.
	if(parentName.length() <= 0)
	{
		//Set parent.
		parent = (CWorldObject *)_NULL;
	}
	else
	{
		//Get parent.
		parent = getObject(parentName);
	}

	//Create joint.
	CJointObject* joint = createJoint(resourceManager,attribute);
#ifdef _DEBUG
	assert(joint != _NULL);
#endif
	//Set child.
	if(child != _NULL) joint->setJointChild(child);
	//Set parent.
	if(parent != _NULL) joint->setJointParent(parent);
	//Set position.
	joint->setPosition(position);
	//Return result.
	return joint;
}