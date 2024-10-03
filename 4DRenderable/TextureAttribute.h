///////////////////////////////////////////////////////////////////////////////
//
// TextureAttribute.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _TEXTURE_ATTRIBUTE_H_
#define _TEXTURE_ATTRIBUTE_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DType.h"
#include "ReferenceAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// TextureAttribute
//
///////////////////////////////////////////////////////////////////////////////

class CTextureAttribute :
	public virtual CReferenceAttribute
{
public:

	/**
	 * All types.
	 */
	static const _INTEGER nullTexture;
	static const _INTEGER float2Texture;

private:

	/**
	 * Type of attribute.
	 */
	_INTEGER type;
	/**
	 * Count of vertex.
	 */
	_INTEGER count;

	union tagTextureData
	{
		struct tagFloat2Texture
		{
			_FLOAT2* coordinates;

		} textureFloat2;

	} textureData;


public:
	CTextureAttribute(void);
	virtual ~CTextureAttribute(void);

public:

	/**
	 * Copy.
	 *
	 * @param attribute Attribute.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void copyTexture(const CTextureAttribute& attribute);

public:

	/**
	 * Get texture type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of texture.</p>
	 */
	_INTEGER getTextureType() const;

	/**
	 * Set texture type.
	 *
	 * @param type Type of texture.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setTextureType(_INTEGER type);

public:

	/**
	 * Size of texture.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Size of texture.</p>
	 */
	_INTEGER getTextureSize() const;

public:

	/**
	 * Clear all.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void clearAllTexture();

public:

	/**
	 * Get texture count.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Count of texture.</p>
	 */
	_INTEGER getTextureCount() const;

	/**
	 * Get float2 texture.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Float2 pointer.</p>
	 */
	_FLOAT2* getFloat2Texture() const;

public:

	/**
	 * Create float2 texture.
	 *
	 * @param count Count of texture.
	 * @return
	 *     <p>Texture pointer.</p>
	 */
	_FLOAT2* createFloat2Texture(_INTEGER count);

public:

	/**
	 * Set float2 texture.
	 *
	 * @param count Count of vertex.
	 * @param parameters Float parameters.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFloat2Texture(_INTEGER count,_FLOAT2* parameters);
};

///////////////////////////////////////////////////////////////////////////////
#endif //_TEXTURE_ATTRIBUTE_H_