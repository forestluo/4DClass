///////////////////////////////////////////////////////////////////////////////
//
// ColorAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _COLOR_ATTRIBUTE_H_
#define _COLOR_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXUtility.h"

///////////////////////////////////////////////////////////////////////////////
//
// ColorAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CColorAttribute
{
private:

	/**
	 * Global color.
	 */
	D3DCOLOR globalColor;
	/**
	 * Light color.
	 */
	D3DXVECTOR4 lightColor;

public:
	CColorAttribute(void);
	virtual ~CColorAttribute(void);

public:

	/**
	 * Get color.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Color of object.</p>
	 */
	D3DCOLOR getColor() const;
	/**
	 * Set color.
	 *
	 * @param color Global color.
	 * @return
	 *     <p>Color of object.</p>
	 */
	void setColor(const D3DCOLOR& color);
	
public:

	/**
	 * Get light color.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Light color.</p>
	 */
	D3DXVECTOR4 getLightColor() const;
	/**
	 * Set light color.
	 *
	 * @param color Light color.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setLightColor(const D3DXVECTOR4& color);

};

///////////////////////////////////////////////////////////////////////////////
#endif //_COLOR_ATTRIBUTE_H_
