///////////////////////////////////////////////////////////////////////////////
//
// HAARFilter.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _HAAR_FILTER_H_
#define _HAAR_FILTER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ImageFilter.h"
#include "HAARAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// HAARFilter
//
///////////////////////////////////////////////////////////////////////////////

class CHAARFilter :
	public CImageFilter,
	public CHAARAttribute
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
	 * Whether tracking face.
	 */
	_BOOL faceTracking;

public:
	CHAARFilter(void);
	virtual ~CHAARFilter(void);

public:

	/**
	 * Enable detection.
	 *
	 * @param None No parameters needed.</p>
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL enableDetection();

public:

	/** 
	 * Whether face tracking.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if face tracking was needed.</p>
	 */
	_BOOL isFaceTracking() const;
	/** 
	 * Set face tracking.
	 *
	 * @param faceTracking Whether face tracking.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFaceTracking(_BOOL faceTracking);

public:

	/**
	 * Handle message.
	 *
	 * @param d3dxEvent D3DX event.
	 * @return
	 *     <p>Result of function.</p>
	 */
	virtual HRESULT handleMessage(const D3DXEvent& d3dxEvent);

};

#define IS_HAARFILTER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CHAARFilter::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_HAAR_FILTER_H_