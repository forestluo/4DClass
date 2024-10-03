///////////////////////////////////////////////////////////////////////////////
//
// StatusKeeper.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _STATUS_KEEPER_H_
#define _STATUS_KEEPER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DBase.h"
#include "StatusAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// StatueKeeper
//
///////////////////////////////////////////////////////////////////////////////

class CStatusKeeper
{
private:
	//Base description.
	static const C4DBase base;

public:

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	static _LONG getClassCode() {return base.classCode();}

	/**
	 * Get class code.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Hash code of this class.</p>
	 */
	virtual _LONG classCode() const {return base.classCode();}

private:
	/**
	 * Attributes.
	 */
	CStatusAttribute attributes[3];

public:
	CStatusKeeper(void);
	virtual ~CStatusKeeper(void);

public:

	/**
	 * Get scale.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Scale of object.</p>
	 */
	const C4DVector3& getScale() const;
	/**
	 * Get position.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Position of object.</p>
	 */
	const C4DVector3& getPosition() const;
	/**
	 * Get rotation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Rotation of object.</p>
	 */
	const C4DQuaternion& getRotation() const;

public:

	/**
	 * Recover origin.
	 *
	 * @param object Object.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void recoverOrigin(_OBJECT object);

	/**
	 * Keep origin.
	 *
	 * @param object Object.
	 * @param timestamp Timestamp of status.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void keepOrigin(_OBJECT object,_LONG timestamp);
	/**
	 * Keep current.
	 *
	 * @param object Object.
	 * @param timestamp Timestamp of status.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual void keepCurrent(_OBJECT object,_LONG timestamp);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_STATUS_KEEPER_H_
