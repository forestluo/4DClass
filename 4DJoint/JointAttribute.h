///////////////////////////////////////////////////////////////////////////////
//
// JointAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _JOINT_ATTRIBUTE_H_
#define _JOINT_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"

///////////////////////////////////////////////////////////////////////////////
//
// JointAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CJointAttribute
{
public:

	/**
	 * All joint types.
	 */
	static const _INTEGER nullJoint;
	/**
	 * Custom joint.
	 */
	static const _INTEGER custom6DOFJoint;
	static const _INTEGER customBallJoint;
	static const _INTEGER customHingeJoint;
	static const _INTEGER customSliderJoint;
	/**
	 * Classic joint.
	 */
	static const _INTEGER classicBallJoint;
	static const _INTEGER classicHingeJoint;
	static const _INTEGER classicSliderJoint;
	static const _INTEGER classicUpVectorJoint;
	static const _INTEGER classicCorkscrewJoint;
	static const _INTEGER classicUniversalJoint;

private:

	/**
	 * Type of joint.
	 */
	_INTEGER type;

public:

	/**
	 * Stiffness.
	 */
	_FLOAT stiffness;
	/**
	 * Self-collision.
	 */
	_BOOL selfCollision;

public:

	//Union
	union tagJointData
	{
		struct tagBallJoint
		{
			//Direction.
			_FLOAT3 direction;
			//Max cone angle.
			_FLOAT maxConeAngle;
			//Max twist angle.
			_FLOAT maxTwistAngle;

		} jointClassicBall;

		struct tagHingeJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointClassicHinge;

		struct tagSliderJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointClassicSlider;

		struct tagCorkscrewJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointClassicCorkscrew;

		struct tagUniversalJoint
		{
			//Direction.
			_FLOAT3 majorDirection;
			//Direction.
			_FLOAT3 minorDirection;

		} jointClassicUniversal;

		struct tagUpVectorJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointClassicUpVector;

		struct tagCustomJoint
		{
			//Direction.
			_FLOAT3 majorDirection;
			//Direction.
			_FLOAT3 minorDirection;

			//Limits.
			_FLOAT3 minLinearLimits;
			_FLOAT3 maxLinearLimits;
			_FLOAT3 minAngulaLimits;
			_FLOAT3 maxAngulaLimits;

		} jointCustom6DOF;

		struct tagCustomBallJoint
		{
			//Direction.
			_FLOAT3 direction;

			//Max cone angle.
			_FLOAT maxConeAngle;
			//Max twist angle.
			_FLOAT maxTwistAngle;
			//Min twist angle.
			_FLOAT minTwistAngle;

		} jointCustomBall;

		struct tagCustomHingeJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointCustomHinge;

		struct tagCustomSliderJoint
		{
			//Direction.
			_FLOAT3 direction;

		} jointCustomSlider;

	} jointData;

public:
	CJointAttribute(void);
	CJointAttribute(const CJointAttribute& attribute);
	virtual ~CJointAttribute(void);

	CJointAttribute& operator = (const CJointAttribute& attribute);

public:

	/**
	 * Copy joint.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyJoint(const CJointAttribute& attribute);

public:

	/**
	 * Get type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of primitive.</p>
	 */
	_INTEGER getType() const;

	/**
	 * Set type.
	 *
	 * @param type Type of primitive.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setType(_INTEGER type);

public:

	/**
	 * Is custom joint.
	 *
	 * @param type Type of joint.
	 * @return
	 *     <p>Return true, if it is custom.</p>
	 */
	static _BOOL isCustomJoint(_INTEGER type);

	/**
	 * Is classic joint.
	 *
	 * @param type Type of joint.
	 * @return
	 *     <p>Return true, if it is classic.</p>
	 */
	static _BOOL isClassicJoint(_INTEGER type);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_JOINT_ATTRIBUTE_H_