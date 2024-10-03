///////////////////////////////////////////////////////////////////////////////
//
// DepthFilter.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _DEPTH_FILTER_H_
#define _DEPTH_FILTER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "ImageFilter.h"

///////////////////////////////////////////////////////////////////////////////
//
// DepthFilter
//
///////////////////////////////////////////////////////////////////////////////

class CDepthFilter :
	public CImageFilter
{
public:
	//Mode.
	static const _INTEGER rawMode;
	static const _INTEGER grayColorMode;
	static const _INTEGER mixedColorMode;
	static const _INTEGER adjustColorMode;

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
	 * Mode of filter.
	 */
	_INTEGER mode;

public:
	CDepthFilter(void);
	virtual ~CDepthFilter(void);

public:

	/** 
	 * Get mode.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mode of filter.</p>
	 */
	_INTEGER getMode() const;

	/** 
	 * Set mode.
	 *
	 * @param mode Mode of filter.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setMode(_INTEGER mode);

private:

	/** 
	 * Do copy.
	 *
	 * @param mode Mode of copy.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void doCopy(_INTEGER mode);

private:

	/** 
	 * Copy raw depth.
	 *
	 * @param width Width of resolution.
	 * @param height Height of resolution.
	 * @param imageBuffer Image buffer.
	 * @param depthBuffer Depth buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyRawDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer);

	/** 
	 * Copy gray depth.
	 *
	 * @param width Width of resolution.
	 * @param height Height of resolution.
	 * @param imageBuffer Image buffer.
	 * @param depthBuffer Depth buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyGrayDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer);

	/** 
	 * Copy mixed depth.
	 *
	 * @param width Width of resolution.
	 * @param height Height of resolution.
	 * @param imageBuffer Image buffer.
	 * @param depthBuffer Depth buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyMixedDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer);

	/** 
	 * Copy adjust depth.
	 *
	 * @param width Width of resolution.
	 * @param height Height of resolution.
	 * @param imageBuffer Image buffer.
	 * @param depthBuffer Depth buffer.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyAdjustDepth(_INTEGER width,_INTEGER height,_INTEGER* imageBuffer,_SHORT* depthBuffer);

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

#define IS_DEPTHFILTER_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CDepthFilter::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_DEPTH_FILTER_H_