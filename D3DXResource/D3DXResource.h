///////////////////////////////////////////////////////////////////////////////
//
// D3DXResource.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef _D3DX_RESOURCE_H_
#define _D3DX_RESOURCE_H_

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXObject.h"
#include "NormalString.h"

///////////////////////////////////////////////////////////////////////////////
//
// Resource
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXResource : public CD3DXObject
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
	 * The name of the resource.
	 */
    CNormalString name;

private:
	/**
	 * Whether reserved for system.
	 */
	_BOOL reserved;
	/**
	 * A reference count of the number of requested instances.
	 */
    _INTEGER reference;

public:
	CD3DXResource(void);
	virtual ~CD3DXResource(void);

public:

	/**
	 * Get name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Name of resource.</p>
	 */
	const CNormalString& getName() const;
	/**
	 * Set name.
	 *
	 * @param wsName Name of resource.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setName(const CNormalString& name);

public:

	/**
	 * Whether reserved.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is reserved.</p>
	 */
	_BOOL isReserved() const;
	/**
	 * Set reserved.
	 *
	 * @param reserved Whether reserved.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setReserved(_BOOL reserved);

public:

	/**
	 * Add reference.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void addReference();
	/**
	 * Release reference.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void releaseReference();
	/**
	 * Count reference.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_INTEGER countReference() const;
};

#define IS_RESOURCE_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXResource::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_RESOURCE_H_