///////////////////////////////////////////////////////////////////////////////
//
// D3DXEffect.h
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _D3DX_EFFECT_H_
#define _D3DX_EFFECT_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "4DMatrix4.h"
#include "D3DXTexture.h"
#include "D3DXResource.h"

///////////////////////////////////////////////////////////////////////////////
//
// D3DXEffect
//
///////////////////////////////////////////////////////////////////////////////

class CD3DXEffect : public CD3DXResource
{
private:
	//Base description.
	static const C4DBase base;

public:
	/**
	 * All parameters.
	 */
	static const _INTEGER semWorld;
	static const _INTEGER semView;
	static const _INTEGER semProjection;
	static const _INTEGER semViewInverse;
	static const _INTEGER semViewProjection;
	static const _INTEGER semWorldViewProjection;

	static const _INTEGER semSceneMap;
	static const _INTEGER semSceneMapEnabled;
	static const _INTEGER semEnvironmentMap;
	static const _INTEGER semEnvironmentMapEnabled;

	static const _INTEGER semMaterialPower;
	static const _INTEGER semMaterialDiffuse;
	static const _INTEGER semMaterialAmbient;
	static const _INTEGER semMaterialEmissive;
	static const _INTEGER semMaterialTexture;
	static const _INTEGER semMaterialSpecular;

	static const _INTEGER semUseWorld;
	static const _INTEGER semLightColor;
	static const _INTEGER semObjectColor;

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
	 * File name.
	 */
	CNormalString fileName;
	/**
	 * Effect
	 */
	LPD3DXEFFECT effectHandle;

private:

	/**
	 * Used to avoid redundantly setting view & projection matrices.
	 */
    _INTEGER frameStamp;

	/**
	 * Cached handles to common effect parameters.
	 */
	//Matrix
    D3DXHANDLE worldHandle;
    D3DXHANDLE viewHandle;
    D3DXHANDLE viewInverseHandle;
    D3DXHANDLE projectionHandle;
    D3DXHANDLE viewProjectionHandle;
	D3DXHANDLE worldViewProjectionHandle;
	//Texture
	D3DXHANDLE sceneMapHandle;
	D3DXHANDLE environmentMapHandle;
	D3DXHANDLE sceneMapEnabledHandle;
	D3DXHANDLE environmentMapEnabledHandle;
	//Material
	D3DXHANDLE powerHandle;
	D3DXHANDLE diffuseHandle;
	D3DXHANDLE ambientHandle;
	D3DXHANDLE emissiveHandle;
	D3DXHANDLE textureHandle;
	D3DXHANDLE specularHandle;
	//Misc
	D3DXHANDLE colorHandle;
	D3DXHANDLE useWorldHandle;
	D3DXHANDLE lightColorHandle;

public:
	CD3DXEffect(void);
	virtual ~CD3DXEffect(void);

protected:

	/**
	 * Attach variables with effect.
	 */
	virtual void attachVariables(ID3DXEffect* pEffect);

public:

	/**
	 * Get file name.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>File name.</p>
	 */
	const CNormalString& getFileName() const;
	/**
	 * Set file name.
	 *
	 * @param wsFileName Name of file.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setFileName(const CNormalString& fileName);

public:

	/**
	 * Whether material defined.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if material is defined.</p>
	 */
	_BOOL isMaterialDefinded() const;

	/**
	 * Get effect handle.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Effect handle.</p>
	 */
	const LPD3DXEFFECT getEffectHandle() const;
	/**
	 * Get parameter handle.
	 *
	 * @param semType Semantic type.
	 * @return
	 *     <p>Parameter handle.</p>
	 */
	const D3DXHANDLE getParameterHandle(_INTEGER semType) const;

public:

	/**
	 * Commit changes.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT commitChanges();

	/**
	 * Set use world.
	 *
	 * @param useWorld Whether use world.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setUseWorld(_BOOL useWorld);
	/**
	 * Set color.
	 *
	 * @param color Global color.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setColor(const D3DCOLOR& color);
	/**
	 * Set light color.
	 *
	 * @param lightColor Light color.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT	setLightColor(const D3DXVECTOR4& lightColor);
	/**
	 * Set world matrix.
	 *
	 * @param worldMatrix World matrix.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setWorldMatrix(const C4DMatrix4& worldMatrix);
    /**
	 * Set view projection matrix.
	 *
	 * @param viewMatrix View matrix.
	 * @param projectionMatrix Projection matrix.
	 * @param frameStamp Frame stamp.
	 * @return
	 *     <p>Result of function.</p>
	 */
    HRESULT setViewProjectionMatrix(const C4DMatrix4& viewMatrix,
									const C4DMatrix4& projectionMatrix,_INTEGER frameStamp);

public:

	/**
	 * Set scene map.
	 *
	 * @param sceneMap Scene map.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT setSceneMap(const CD3DXTexture* sceneMap);

public:

	/**
	 * Load from file.
	 *
	 * @param pd3dDevice D3DX device.
	 * @param fileName Name of file.
	 * @return
	 *     <p>Result of function.</p>
	 */
	HRESULT loadFromFile(IDirect3DDevice9* pd3dDevice,
							const CNormalString& fileName);

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

#define IS_EFFECT_BASE(p) \
	(C4DBase::isBaseOf((p)->classCode(),CD3DXEffect::getClassCode()))

///////////////////////////////////////////////////////////////////////////////
#endif //_D3DX_EFFECT_H_