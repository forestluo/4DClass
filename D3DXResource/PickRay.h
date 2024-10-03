///////////////////////////////////////////////////////////////////////////////
//
// PickRay.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _PICK_RAY_H_
#define _PICK_RAY_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DVector3.h"
#include "4DMatrix4.h"

///////////////////////////////////////////////////////////////////////////////
//
// PickRay
//
///////////////////////////////////////////////////////////////////////////////

class CPickRay
{
private:
	/**
	 * All hits.
	 */
	_BOOL allHits;
	/**
	 * Direction in view space.
	 */
    C4DVector3 direction;
	/**
	 * View Matrix.
	 */
	C4DMatrix4 viewMatrix;

protected:

	/**
	 * Origin.
	 */
    C4DVector3 pickOrigin;
	/**
	 * Direction.
	 */
    C4DVector3 pickDirection;
	
public:
	CPickRay(void);
	CPickRay(const CPickRay& pickRay);
	virtual ~CPickRay(void);

	const CPickRay& operator = (const CPickRay& pickRay);

public:

	/**
	 * Whether all hits needed.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if all hits needed.</p>
	 */
	_BOOL isAllHitsNeeded() const;
	/**
	 * Set all hits needed.
	 *
	 * @param allHits All hits is needed or not.
	 * @return
	 *    <p>No results returned.</p>
	 */
	void setAllHits(_BOOL allHits);

	/**
	 * Set world matrix.
	 *
	 * @param worldMatrix World matrix.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setWorldMatrix(const C4DMatrix4& worldMatrix);
	/**
	 * Set pick parameters.
	 *
	 * @param viewMatrix View matrix.
	 * @param direction Vector of direction.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setPickParameters(const C4DMatrix4& viewMatrix,const C4DVector3& direction);

public:

	/**
	 * Get pick origin.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vector of pick origin.</p>
	 */
	const C4DVector3& getPickOrigin() const;
	/**
	 * Get pick direction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Vector of pick direction.</p>
	 */
	const C4DVector3& getPickDirection() const;
};

///////////////////////////////////////////////////////////////////////////////
#endif //_PICK_RAY_H_
