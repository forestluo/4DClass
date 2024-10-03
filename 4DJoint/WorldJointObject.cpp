///////////////////////////////////////////////////////////////////////////////
//
// WorldJointObject.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "WorldJointObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include <memory.h>

#include "4DMath.h"

///////////////////////////////////////////////////////////////////////////////
//
// CWorldJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CWorldJointObject::CWorldJointObject(_INTEGER jointType)
	: CJointAttribute(getDefaultAttribute(jointType))
{
	//Set this.
	setThis(this);
	//Set object type.
	setObjectType(CTypeAttribute::jointObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CWorldJointObject
//
// Default construction.
//
///////////////////////////////////////////////////////////////////////////////

CWorldJointObject::CWorldJointObject(const CJointAttribute& attribute)
	: CJointAttribute(attribute)
{
	//Set this.
	setThis(this);
	//Set object type.
	setObjectType(CTypeAttribute::jointObject);
}

///////////////////////////////////////////////////////////////////////////////
//
// CWorldJointObject
//
// Default deconstruction.
//
///////////////////////////////////////////////////////////////////////////////

CWorldJointObject::~CWorldJointObject(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// GetJointType
//
///////////////////////////////////////////////////////////////////////////////

_INTEGER CWorldJointObject::getJointType() const
{
	//Return result.
	return CJointAttribute::getType();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetJointAttribute
//
///////////////////////////////////////////////////////////////////////////////

CJointAttribute& CWorldJointObject::getJointAttribute()
{
	//Return result.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetJointAttribute
//
///////////////////////////////////////////////////////////////////////////////

const CJointAttribute& CWorldJointObject::getJointAttribute() const
{
	//Return result.
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMajorDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CWorldJointObject::getMajorDirection() const
{
	//Get joint type.
	_INTEGER jointType = getJointType();
	//Check joint type.
	if(jointType == CJointAttribute::classicBallJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicBall.direction);
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicCorkscrew.direction);
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicHinge.direction);
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicSlider.direction);
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicUniversal.majorDirection);
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicUpVector.direction);
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointCustom6DOF.majorDirection);
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointCustomBall.direction);
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointCustomHinge.direction);
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointCustomSlider.direction);
	}
	//Return result.
	return C4DVector3();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetMajorDirection
//
///////////////////////////////////////////////////////////////////////////////

void CWorldJointObject::setMajorDirection(const C4DVector3& vector)
{
	//Get joint type.
	_INTEGER jointType = getJointType();
	//Check joint type.
	if(jointType == CJointAttribute::classicBallJoint)
	{
		//Set direction.
		jointData.jointClassicBall.direction[0] = vector.x();
		jointData.jointClassicBall.direction[1] = vector.y();
		jointData.jointClassicBall.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Set direction.
		jointData.jointClassicCorkscrew.direction[0] = vector.x();
		jointData.jointClassicCorkscrew.direction[1] = vector.y();
		jointData.jointClassicCorkscrew.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Set direction.
		jointData.jointClassicHinge.direction[0] = vector.x();
		jointData.jointClassicHinge.direction[1] = vector.y();
		jointData.jointClassicHinge.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Set direction.
		jointData.jointClassicSlider.direction[0] = vector.x();
		jointData.jointClassicSlider.direction[1] = vector.y();
		jointData.jointClassicSlider.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Set direction.
		jointData.jointClassicUniversal.majorDirection[0] = vector.x();
		jointData.jointClassicUniversal.majorDirection[1] = vector.y();
		jointData.jointClassicUniversal.majorDirection[2] = vector.z();
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Set direction.
		jointData.jointClassicUpVector.direction[0] = vector.x();
		jointData.jointClassicUpVector.direction[1] = vector.y();
		jointData.jointClassicUpVector.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Set direction.
		jointData.jointCustom6DOF.majorDirection[0] = vector.x();
		jointData.jointCustom6DOF.majorDirection[1] = vector.y();
		jointData.jointCustom6DOF.majorDirection[2] = vector.z();
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Set direction.
		jointData.jointCustomBall.direction[0] = vector.x();
		jointData.jointCustomBall.direction[1] = vector.y();
		jointData.jointCustomBall.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Set direction.
		jointData.jointCustomHinge.direction[0] = vector.x();
		jointData.jointCustomHinge.direction[1] = vector.y();
		jointData.jointCustomHinge.direction[2] = vector.z();
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Set direction.
		jointData.jointCustomSlider.direction[0] = vector.x();
		jointData.jointCustomSlider.direction[1] = vector.y();
		jointData.jointCustomSlider.direction[2] = vector.z();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMinorDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CWorldJointObject::getMinorDirection() const
{
	//Get joint type.
	_INTEGER jointType = getJointType();
	//Check joint type.
	if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointClassicUniversal.minorDirection);
	}
	//Check joint type.
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Return result.
		return C4DVector3(jointData.jointCustom6DOF.minorDirection);
	}
	//Return result.
	return C4DVector3();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetMinorDirection
//
///////////////////////////////////////////////////////////////////////////////

void CWorldJointObject::setMinorDirection(const C4DVector3& vector)
{
	//Get joint type.
	_INTEGER jointType = getJointType();
	//Check joint type.
	if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Set direction.
		jointData.jointClassicUniversal.minorDirection[0] = vector.x();
		jointData.jointClassicUniversal.minorDirection[1] = vector.y();
		jointData.jointClassicUniversal.minorDirection[2] = vector.z();
	}
	//Check joint type.
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Set direction.
		jointData.jointCustom6DOF.minorDirection[0] = vector.x();
		jointData.jointCustom6DOF.minorDirection[1] = vector.y();
		jointData.jointCustom6DOF.minorDirection[2] = vector.z();
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// IsSelfCollision
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CWorldJointObject::isSelfCollision() const
{
	//Return result.
	return selfCollision;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSelfCollision
//
///////////////////////////////////////////////////////////////////////////////

void CWorldJointObject::setSelfCollision(_BOOL selfCollision)
{
	//Set value.
	this->selfCollision = selfCollision;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDefaultMajorDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CWorldJointObject::getDefaultMajorDirection(_INTEGER jointType)
{
	//Check joint type.
	if(jointType == CJointAttribute::nullJoint)
	{
		//Do nothing.
	}
	else if(jointType == CJointAttribute::classicBallJoint)
	{
		//Return result.
		return C4DVector3(0.0f,-1.0f,0.0f);
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Return result.
		return C4DVector3(0.0f,0.0f,-1.0f);
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Return result.
		return C4DVector3(0.0f,0.5f,0.0f);
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Return result.
		return C4DVector3(0.0f,-1.0f,0.0f);
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Return result.
		return C4DVector3(1.0f,0.0f,0.0f);
	}
	//Return result.
	return C4DVector3();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDefaultMinorDirection
//
///////////////////////////////////////////////////////////////////////////////

C4DVector3 CWorldJointObject::getDefaultMinorDirection(_INTEGER jointType)
{
	//Check joint type.
	if(jointType == CJointAttribute::nullJoint)
	{
		//Do nothing.
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Return result.
		return C4DVector3(0.0f,0.0f,1.0f);
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Return result.
		return C4DVector3(0.0f,0.0f,1.0f);
	}
	//Return result.
	return C4DVector3();
}

///////////////////////////////////////////////////////////////////////////////
//
// GetDefaultAttribute
//
///////////////////////////////////////////////////////////////////////////////

CJointAttribute CWorldJointObject::getDefaultAttribute(_INTEGER jointType)
{
	//Attribute.
	CJointAttribute attribute;

	//Major direction.
	C4DVector3 majorDirection = getDefaultMajorDirection(jointType);
	//Minor direction.
	C4DVector3 minorDirection = getDefaultMinorDirection(jointType);

	//Check joint type.
	if(jointType == CJointAttribute::nullJoint)
	{
		//Do nothing.
	}
	else if(jointType == CJointAttribute::classicBallJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicBallJoint);
		//Set values.
		attribute.jointData.jointClassicBall.maxConeAngle = 0.0f;
		attribute.jointData.jointClassicBall.maxTwistAngle = 0.0f;
		//Set direction.
		attribute.jointData.jointClassicBall.direction[0] = majorDirection.x();
		attribute.jointData.jointClassicBall.direction[1] = majorDirection.y();
		attribute.jointData.jointClassicBall.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::classicCorkscrewJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicCorkscrewJoint);
		//Set direction.
		attribute.jointData.jointClassicCorkscrew.direction[0] = majorDirection.x();
		attribute.jointData.jointClassicCorkscrew.direction[1] = majorDirection.y();
		attribute.jointData.jointClassicCorkscrew.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::classicHingeJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicHingeJoint);
		//Set direction.
		attribute.jointData.jointClassicHinge.direction[0] = majorDirection.x();
		attribute.jointData.jointClassicHinge.direction[1] = majorDirection.y();
		attribute.jointData.jointClassicHinge.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::classicSliderJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicSliderJoint);
		//Set direction.
		attribute.jointData.jointClassicSlider.direction[0] = majorDirection.x();
		attribute.jointData.jointClassicSlider.direction[1] = majorDirection.y();
		attribute.jointData.jointClassicSlider.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::classicUniversalJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicUniversalJoint);
		//Set direction.
		attribute.jointData.jointClassicUniversal.majorDirection[0] = majorDirection.x();
		attribute.jointData.jointClassicUniversal.majorDirection[1] = majorDirection.y();
		attribute.jointData.jointClassicUniversal.majorDirection[2] = majorDirection.z();
		//Set direction.
		attribute.jointData.jointClassicUniversal.minorDirection[0] = minorDirection.x();
		attribute.jointData.jointClassicUniversal.minorDirection[1] = minorDirection.y();
		attribute.jointData.jointClassicUniversal.minorDirection[2] = minorDirection.z();
	}
	else if(jointType == CJointAttribute::classicUpVectorJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::classicUpVectorJoint);
		//Set direction.
		attribute.jointData.jointClassicUpVector.direction[0] = majorDirection.x();
		attribute.jointData.jointClassicUpVector.direction[1] = majorDirection.y();
		attribute.jointData.jointClassicUpVector.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::custom6DOFJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::custom6DOFJoint);
		//Set direction.
		attribute.jointData.jointCustom6DOF.majorDirection[0] = majorDirection.x();
		attribute.jointData.jointCustom6DOF.majorDirection[1] = majorDirection.y();
		attribute.jointData.jointCustom6DOF.majorDirection[2] = majorDirection.z();
		//Set direction.
		attribute.jointData.jointCustom6DOF.minorDirection[0] = minorDirection.x();
		attribute.jointData.jointCustom6DOF.minorDirection[1] = minorDirection.y();
		attribute.jointData.jointCustom6DOF.minorDirection[2] = minorDirection.z();
		//Min angular.
		attribute.jointData.jointCustom6DOF.minAngulaLimits[0] = - 175.0f / 180.0f * (_FLOAT)_PI;
		attribute.jointData.jointCustom6DOF.minAngulaLimits[1] = - 175.0f / 180.0f * (_FLOAT)_PI;
		attribute.jointData.jointCustom6DOF.minAngulaLimits[2] = - 175.0f / 180.0f * (_FLOAT)_PI;
		//Max angular.
		attribute.jointData.jointCustom6DOF.maxAngulaLimits[0] = + 175.0f / 180.0f * (_FLOAT)_PI;
		attribute.jointData.jointCustom6DOF.maxAngulaLimits[1] = + 175.0f / 180.0f * (_FLOAT)_PI;
		attribute.jointData.jointCustom6DOF.maxAngulaLimits[2] = + 175.0f / 180.0f * (_FLOAT)_PI;
		//Min angular.
		attribute.jointData.jointCustom6DOF.minLinearLimits[0] = - 0.05f;
		attribute.jointData.jointCustom6DOF.minLinearLimits[1] = - 0.05f;
		attribute.jointData.jointCustom6DOF.minLinearLimits[2] = - 0.05f;
		//Max angular.
		attribute.jointData.jointCustom6DOF.maxLinearLimits[0] = + 0.05f;
		attribute.jointData.jointCustom6DOF.maxLinearLimits[1] = + 0.05f;
		attribute.jointData.jointCustom6DOF.maxLinearLimits[2] = + 0.05f;
	}
	else if(jointType == CJointAttribute::customBallJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::customBallJoint);
		//Set direction.
		attribute.jointData.jointCustomBall.direction[0] = majorDirection.x();
		attribute.jointData.jointCustomBall.direction[1] = majorDirection.y();
		attribute.jointData.jointCustomBall.direction[2] = majorDirection.z();
		//Set value.
		attribute.jointData.jointCustomBall.maxConeAngle = 175.0f / 180.0f * (_FLOAT)_PI;
		attribute.jointData.jointCustomBall.maxTwistAngle = 0.0f;
		attribute.jointData.jointCustomBall.minTwistAngle = 0.0f;
	}
	else if(jointType == CJointAttribute::customHingeJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::customHingeJoint);
		//Set direction.
		attribute.jointData.jointCustomHinge.direction[0] = majorDirection.x();
		attribute.jointData.jointCustomHinge.direction[1] = majorDirection.y();
		attribute.jointData.jointCustomHinge.direction[2] = majorDirection.z();
	}
	else if(jointType == CJointAttribute::customSliderJoint)
	{
		//Set joint type.
		attribute.setType(CJointAttribute::customSliderJoint);
		//Set direction.
		attribute.jointData.jointCustomSlider.direction[0] = majorDirection.x();
		attribute.jointData.jointCustomSlider.direction[1] = majorDirection.y();
		attribute.jointData.jointCustomSlider.direction[2] = majorDirection.z();
	}
#ifdef _DEBUG
	else assert(_FALSE);
#endif
	//Return result.
	return attribute;
}
