///////////////////////////////////////////////////////////////////////////////
//
// D3DXEffect.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXEffect.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SDKmisc.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

//Debug Shader
//#define _DEBUG_SHADER

//Matrix
#define SEMANTIC_WORLD										"WORLD"
#define SEMANTIC_VIEW										"VIEW"
#define SEMANTIC_PROJECTION									"PROJECTION"
#define SEMANTIC_VIEWINVERSE								"VIEWINVERSE"
#define SEMANTIC_VIEWPROJECTION								"VIEWPROJECTION"
#define SEMANTIC_WORLDVIEWPROJECTION						"WORLDVIEWPROJECTION"

#define SEMANTIC_SCENEMAP									"SCENEMAP"
#define SEMANTIC_SCENEMAPENABLED							"SCENEMAPENABLED"
#define SEMANTIC_ENVIRONMENTMAP								"ENVIRONMENTMAP"
#define SEMANTIC_ENVIRONMENTMAPENABLED						"ENVIRONMENTMAPENABLED"

#define SEMANTIC_USEWORLD									"USEWORLD"
#define SEMANTIC_LIGHTCOLOR									"LIGHTCOLOR"
#define SEMANTIC_OBJECTCOLOR								"OBJECTCOLOR"

//Matrial
#define SEMANTIC_MATERIALPOWER								"MATERIALPOWER"
#define SEMANTIC_MATERIALDIFFUSE							"MATERIALDIFFUSE"
#define SEMANTIC_MATERIALAMBIENT							"MATERIALAMBIENT"
#define SEMANTIC_MATERIALEMISSIVE							"MATERIALEMISSIVE"
#define SEMANTIC_MATERIALTEXTURE							"MATERIALTEXTURE"
#define SEMANTIC_MATERIALSPECULAR							"MATERIALSPECULAR"

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXEffect::base(L"CD3DXEffect",L"CD3DXResource");

//Parameters.
const _INTEGER CD3DXEffect::semWorld						= 1;
const _INTEGER CD3DXEffect::semView							= 2;
const _INTEGER CD3DXEffect::semProjection					= 3;
const _INTEGER CD3DXEffect::semViewInverse					= 4;
const _INTEGER CD3DXEffect::semViewProjection				= 5;
const _INTEGER CD3DXEffect::semWorldViewProjection          = 6;

const _INTEGER CD3DXEffect::semSceneMap						= 7;
const _INTEGER CD3DXEffect::semSceneMapEnabled				= 8;
const _INTEGER CD3DXEffect::semEnvironmentMap				= 9;
const _INTEGER CD3DXEffect::semEnvironmentMapEnabled		= 10;

const _INTEGER CD3DXEffect::semMaterialPower				= 11;
const _INTEGER CD3DXEffect::semMaterialDiffuse				= 12;
const _INTEGER CD3DXEffect::semMaterialAmbient				= 13;
const _INTEGER CD3DXEffect::semMaterialEmissive				= 14;
const _INTEGER CD3DXEffect::semMaterialTexture				= 15;
const _INTEGER CD3DXEffect::semMaterialSpecular				= 16;

const _INTEGER CD3DXEffect::semUseWorld						= 17;
const _INTEGER CD3DXEffect::semLightColor					= 18;
const _INTEGER CD3DXEffect::semObjectColor					= 19;

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXEffect
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXEffect::CD3DXEffect(void)
{
	//Set default value.
	effectHandle = (LPD3DXEFFECT)_NULL;
	//Set default value.
    frameStamp = -1;

	//Set default value.
    worldHandle = (D3DXHANDLE)_NULL;
    viewHandle = (D3DXHANDLE)_NULL;
    projectionHandle = (D3DXHANDLE)_NULL;
    viewInverseHandle = (D3DXHANDLE)_NULL;
    viewProjectionHandle = (D3DXHANDLE)_NULL;
	worldViewProjectionHandle = (D3DXHANDLE)_NULL;

	sceneMapHandle = (D3DXHANDLE)_NULL;
	environmentMapHandle = (D3DXHANDLE)_NULL;
	sceneMapEnabledHandle = (D3DXHANDLE)_NULL;
	environmentMapEnabledHandle = (D3DXHANDLE)_NULL;

	colorHandle = (D3DXHANDLE)_NULL;
	useWorldHandle = (D3DXHANDLE)_NULL;
	lightColorHandle = (D3DXHANDLE)_NULL;

	powerHandle = (D3DXHANDLE)_NULL;
	diffuseHandle = (D3DXHANDLE)_NULL;
	ambientHandle = (D3DXHANDLE)_NULL;
	emissiveHandle = (D3DXHANDLE)_NULL;
	textureHandle = (D3DXHANDLE)_NULL;
	specularHandle = (D3DXHANDLE)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXEffect
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXEffect::~CD3DXEffect(void)
{
	//Safe release.
	SAFE_RELEASE(effectHandle);
}

///////////////////////////////////////////////////////////////////////////////
//
// AttachVariables
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXEffect::attachVariables(ID3DXEffect* pEffect)
{
#ifdef _DEBUG
	assert(pEffect != _NULL);
#endif

    //Used to avoid redundantly setting view/projection matrices -- ensure that it does not start at 0.
    frameStamp = -1;

    //Effects may not require all of the following matrices.
    //Prior to updating the transformation matrices, the D3DXHANDLE value will
    //be checked to determine whether or not it was declared by the effect.
	//For examples :
	//
	// Transformation Matrices
	//matrix matView      : VIEW;
	//matrix matProj      : PROJECTION;
	//matrix matWorld     : WORLD;
	//
	worldHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_WORLD);
    viewHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_VIEW);
    projectionHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_PROJECTION);
    viewInverseHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_VIEWINVERSE);
    viewProjectionHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_VIEWPROJECTION);
	worldViewProjectionHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_WORLDVIEWPROJECTION);

	sceneMapHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_SCENEMAP);
	environmentMapHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_ENVIRONMENTMAP);
	sceneMapEnabledHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_SCENEMAPENABLED);
	environmentMapEnabledHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_ENVIRONMENTMAPENABLED);

	colorHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_OBJECTCOLOR);
	useWorldHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_USEWORLD);
	lightColorHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_LIGHTCOLOR);
	
	powerHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALPOWER);
	diffuseHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALDIFFUSE);
	ambientHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALAMBIENT);
	emissiveHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALEMISSIVE);
	textureHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALTEXTURE);
	specularHandle = pEffect->GetParameterBySemantic(NULL,SEMANTIC_MATERIALSPECULAR);
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFileName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXEffect::getFileName() const
{
	//Return result.
	return fileName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFileName
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXEffect::setFileName(const CNormalString& fileName)
{
#ifdef _DEBUG
	assert(fileName.length() > 0);
#endif
	//Set file name.
	this->fileName = fileName;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetEffectHandle
//
///////////////////////////////////////////////////////////////////////////////

const LPD3DXEFFECT CD3DXEffect::getEffectHandle() const
{
#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Return result.
	return effectHandle;
}

///////////////////////////////////////////////////////////////////////////////
//
// IsMaterialDefinded
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CD3DXEffect::isMaterialDefinded() const
{
#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Check.
	if(ambientHandle != _NULL) return _TRUE;
	if(diffuseHandle != _NULL) return _TRUE;
	if(textureHandle != _NULL) return _TRUE;
	if(specularHandle != _NULL) return _TRUE;
	if(powerHandle != _NULL) return _TRUE;
	if(emissiveHandle != _NULL) return _TRUE;
	//Return result.
	return _FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetParameterHandle
//
///////////////////////////////////////////////////////////////////////////////

const D3DXHANDLE CD3DXEffect::getParameterHandle(_INTEGER semType) const
{
	//Check type.
	switch(semType)
	{
	case semWorld:
		return worldHandle;
	case semView:
		return viewHandle;
	case semProjection:
		return projectionHandle;
	case semViewInverse:
		return viewInverseHandle;
	case semViewProjection:
		return viewProjectionHandle;
	case semWorldViewProjection:
		return worldViewProjectionHandle;
	case semObjectColor:
		return colorHandle;
	case semMaterialPower:
		return powerHandle;
	case semMaterialDiffuse:
		return diffuseHandle;
	case semMaterialAmbient:
		return ambientHandle;
	case semMaterialEmissive:
		return emissiveHandle;
	case semMaterialTexture:
		return textureHandle;
	case semMaterialSpecular:
		return specularHandle;
	case semUseWorld:
		return useWorldHandle;
	case semLightColor:
		return lightColorHandle;
	case semSceneMap:
		return sceneMapHandle;
	case semEnvironmentMap:
		return environmentMapHandle;
	case semSceneMapEnabled:
		return sceneMapEnabledHandle;
	case semEnvironmentMapEnabled:
		return environmentMapEnabledHandle;
	default:;
	}
	//Return null.
	return (D3DXHANDLE)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CommitChanges
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::commitChanges()
{
#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Return result.
	return effectHandle->CommitChanges();
}

///////////////////////////////////////////////////////////////////////////////
//
// SetUseWorld
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::setUseWorld(_BOOL useWorld)
{
    //Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Check handle.
    if(useWorldHandle != _NULL)
	{
		//Set matrix.
        hr = effectHandle->SetBool(useWorldHandle,useWorld);
	}
	//Return result.
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetColor
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::setColor(const D3DCOLOR& color)
{
    //Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Check handle.
    if(colorHandle != _NULL)
	{
		//Get color.
		D3DXCOLOR vColor = color;
		//Set color.
		hr = effectHandle->SetFloatArray(colorHandle,vColor,4);
	}
	//Return result.
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetLightColor
//
///////////////////////////////////////////////////////////////////////////////

HRESULT	CD3DXEffect::setLightColor(const D3DXVECTOR4& lightColor)
{
    //Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Check handle.
    if(lightColorHandle != _NULL)
	{
		//Set vector.
		hr = effectHandle->SetVector(lightColorHandle,&lightColor);
	}
	//Return result.
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetWorldMatrix
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::setWorldMatrix(const C4DMatrix4& worldMatrix)
{
    //Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
    //If the effect required the world matrix, update it.
    if(worldHandle != _NULL)
	{
		//Matrix.
		D3DXMATRIX mWorld(worldMatrix);
		//Set matrix.
        hr = effectHandle->SetMatrix(worldHandle,&mWorld);
	}
	//Return result.
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetViewProjectionMatrix
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::setViewProjectionMatrix(const C4DMatrix4& viewMatrix,
											 const C4DMatrix4& projectionMatrix,_INTEGER frameStamp)
{
    //Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif

    //Avoid updating the view unless needed
    //The view and projection matrices in this sample do not vary between objects.
    if(this->frameStamp != frameStamp)
    {
		//View matrix.
		D3DXMATRIX mView(viewMatrix);
		//Projection matrix.
		D3DXMATRIX mProjection(projectionMatrix);

        //Update the effect timestamp to avoid setting view/projection matrices until next frame.
        this->frameStamp = frameStamp;
        //If the effect required the view matrix, update it.
        if(viewHandle != _NULL)
		{
			//Set matrix.
            hr = effectHandle->SetMatrix(viewHandle,&mView);
		}
        //If the effect required the projection matrix, update it.
        if(projectionHandle != _NULL)
		{
			//Set matrix.
            hr = effectHandle->SetMatrix(projectionHandle,&mProjection);
		}
        //If this effect requires the true inverse of the view matrix, compute and update it.
        if(viewInverseHandle != _NULL)
        {
			//Matrix
            D3DXMATRIX mViewInversed;
			//Inverse.
            D3DXMatrixInverse(&mViewInversed,NULL,&mView);
			//Set matrix.
            hr = effectHandle->SetMatrix(viewInverseHandle,&mViewInversed);
        }
        //If this effect required the view-projection matrix, it must be computed and updated.
        if(viewProjectionHandle != _NULL)
        {
			//Matrix.
            D3DXMATRIX mViewProjection;
			//Multiply.
            D3DXMatrixMultiply(&mViewProjection,&mView,&mProjection);
			//Set matrix.
            hr = effectHandle->SetMatrix(viewProjectionHandle,&mViewProjection);
        }
    }
	//Return result.
    return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetSceneMap
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::setSceneMap(const CD3DXTexture* sceneMap)
{
	//Result.
	HRESULT hr = S_OK;

#ifdef _DEBUG
	assert(effectHandle != _NULL);
#endif
	//Check scene map handle.
	if(sceneMapHandle != _NULL)
	{
		//Check scene map enabled handle.
		if(sceneMapEnabledHandle != _NULL)
		{
			//Set flag.
			if(FAILED(effectHandle->SetBool(sceneMapEnabledHandle,sceneMap != NULL ? _TRUE : _FALSE))) hr = E_FAIL;
		}
		//Set matrix.
		if(FAILED(effectHandle->SetTexture(sceneMapHandle,sceneMap != NULL ? sceneMap->getTexture() : (LPDIRECT3DBASETEXTURE9)_NULL))) hr = E_FAIL;
	}
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// LoadFromFile
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::loadFromFile(IDirect3DDevice9* pd3dDevice,
									const CNormalString& fileName)
{
	//Result value.
    HRESULT hr;
    //Read the D3DX effect file.
    WCHAR str[MAX_PATH];

#ifdef _DEBUG
	assert(effectHandle == NULL);
	assert(pd3dDevice != NULL && fileName.length() > 0);
#endif

    // Define DEBUG_VS and/or DEBUG_PS to debug vertex and/or pixel shaders with the 
    // shader debugger. Debugging vertex shaders requires either REF or software vertex 
    // processing, and debugging pixel shaders requires REF.  The 
    // D3DXSHADER_FORCE_*_SOFTWARE_NOOPT flag improves the debug experience in the 
    // shader debugger.  It enables source level debugging, prevents instruction 
    // reordering, prevents dead code elimination, and forces the compiler to compile 
    // against the next higher available software target, which ensures that the 
    // unoptimized shaders do not exceed the shader model limitations.  Setting these 
    // flags will cause slower rendering since the shaders will be unoptimized and 
    // forced into software.  See the DirectX documentation for more information about 
    // using the shader debugger.
    DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

#ifdef DEBUG_VS
    dwShaderFlags |= D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT;
#endif
#ifdef DEBUG_PS
    dwShaderFlags |= D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT;
#endif

#ifdef _DEBUG_SHADER
    // Set the D3DXSHADER_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DXSHADER_DEBUG;
	// When the Direct3D 9 debug flag is specified it is most useful to also specify
	// the D3DXSHADER_SKIPOPTIMIZATION flag that prevents the optimization of compiled shaders.
	// Optimized shaders may re-order the instruction sequence to facilitate greater execution speed,
	// and this will not match the source code that is displayed. Non-optimized shaders will 
	// execute in the original order that the code is displayed in the shader-debugger view.
	dwShaderFlags |= D3DXSHADER_SKIPOPTIMIZATION;
#endif

	//Find effect file.
	V_RETURN(DXUTFindDXSDKMediaFileCch(str,MAX_PATH,fileName.getCString()));

	//Error buffer.
	ID3DXBuffer* pErrors = NULL;
	//Create effect from file.
	//(required since we are using D3DXFX_LARGEADDRESS_HANDLE).
	hr = D3DXCreateEffectFromFile(
				//Pointer to the device that will create the effect.
				pd3dDevice,
				//Pointer to the filename. This parameter supports both Unicode and ANSI strings.
				str,
				//Optional NULL-terminated array of preprocessor macro definitions.
				NULL,
				//Optional interface pointer, ID3DXInclude, to use for handling #include directives.
				//If this value is NULL, #includes will either be honored when compiling from a file or
				//will cause an error when compiled from a resource or memory. 
				NULL,
				//If pSrcFile contains a text effect, flags can be a combination of D3DXSHADER Flags and D3DXFX flags;
				//otherwise, pSrcFile contains a binary effect and the only flags honored are D3DXFX flags.
				//The Direct3D 10 HLSL compiler is now the default. See Effect-Compiler Tool for details.
				dwShaderFlags | D3DXFX_LARGEADDRESSAWARE,
				//Pointer to a ID3DXEffectPool object to use for shared parameters. If this value is NULL, no parameters will be shared.
				NULL,
				//Returns a pointer to a buffer containing the compiled effect.
				&effectHandle,
				//Returns a pointer to a buffer containing a listing of compile errors.
				&pErrors);
	//Check result.
	if(pErrors != NULL)
	{
		//Print error message.
		::MessageBoxA(NULL,(char *)pErrors->GetBufferPointer(),"编译错误",MB_OK | MB_ICONERROR);
		//Release error buffer.
		SAFE_RELEASE(pErrors);
	}
	//Do return.
	V_RETURN(hr);
	//Attach variables with object.
	attachVariables(effectHandle);

	//The first technique that is valid is used.
    //This assumes that multiple materials are not packed into the same effect resource.
    //The intention to represent each unique material type with one effect resource.
    //Within the effect resource, techniques (including fallback methods) are ordered
    //in decreasing order of hardware requirements.  Thus, selecting the first valid
    //technique within the effect will chose the most advanced technique that is
    //supported by the underlying hardware.
    D3DXHANDLE hTechnique;

	//Find next valid technique.
    V_RETURN(effectHandle->FindNextValidTechnique(NULL,&hTechnique));
    //It is possible for FindNextValidTechnique to succeed yet return NULL
    //This would indicate no valid techniques were found.
    if(hTechnique == NULL)
	{
#ifdef _DEBUG
        ::MessageBox(NULL,L"没有定义任何有效的渲染技巧。",L"D3DXEffect.LoadFromFile",MB_OK | MB_ICONERROR);
#endif
		return E_FAIL;
	}
    //Prior to rendering from the effect, the desired technique must be set
    V_RETURN(effectHandle->SetTechnique(hTechnique));
	//Return result.
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXEffect::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Release.
		SAFE_RELEASE(effectHandle);
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
#ifdef _DEBUG
		//Check handle.
		assert(effectHandle != _NULL);
#endif
		//Handle event.
		effectHandle->OnLostDevice();
		break;
		//Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED) and aren't tied to the back buffer size.
	case d3dxOnD3D9CreateDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxCreateDevice9.pd3dDevice != NULL);
#endif
		//Load from file.
		V_RETURN(loadFromFile(d3dxEvent.d3dxCreateDevice9.pd3dDevice,fileName.getCString()));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(effectHandle != _NULL);
#endif
		//Handle event.
		effectHandle->OnResetDevice();
		break;
	}
	//Return result.
	return CD3DXResource::handleMessage(d3dxEvent);
}
