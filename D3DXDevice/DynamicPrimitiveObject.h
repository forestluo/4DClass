///////////////////////////////////////////////////////////////////////////////
//
// DynamicPrimitiveObject.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _DYNAMIC_PRIMITIVE_OBJECT_H_
#define _DYNAMIC_PRIMITIVE_OBJECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PrimitiveObject.h"

///////////////////////////////////////////////////////////////////////////////
//
// DynamicPrimitiveObject
//
///////////////////////////////////////////////////////////////////////////////

class CDynamicPrimitiveObject : public CPrimitiveObject
{
protected:
	/** 
	 * Source.
	 */
	CD3DXResource* source;
	/** 
	 * Name of source.
	 */
	CNormalString sourceName;

public:
	CDynamicPrimitiveObject(void);
	virtual ~CDynamicPrimitiveObject(void);

public:

	/**
	 * Get source.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Source of resouse.</p>
	 */
	CD3DXResource* getSource() const;

protected:

	/** 
	 * Set source.
	 *
	 * @param resource Resource.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSource(CD3DXResource* resource);

public:

	/**
	 * Get source name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Source name.</p>
	 */
	const CNormalString& getSourceName() const;

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

///////////////////////////////////////////////////////////////////////////////
#endif //_DYNAMIC_PRIMITIVE_OBJECT_H_