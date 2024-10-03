///////////////////////////////////////////////////////////////////////////////
//
// D3DXLinestrip.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXLinestrip.h"

////////////////////////////////////////////////////////////////////////////////
//
// Including
//
////////////////////////////////////////////////////////////////////////////////

#include "D3DXVertex.h"

////////////////////////////////////////////////////////////////////////////////
//
// XNA
//
////////////////////////////////////////////////////////////////////////////////

#include <xnamath.h>

#include "xnaCollision.h"
using namespace XNA;

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXLinestrip::base(L"CD3DXLinestrip",L"CD3DXRenderable");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXLinestrip
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXLinestrip::CD3DXLinestrip(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXLinestrip
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXLinestrip::~CD3DXLinestrip(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// DrawBox
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXLinestrip::drawBox(IDirect3DDevice9* pd3dDevice,const CSimpleBox& box)
{
    XMMATRIX matWorld = XMMatrixScaling(box.dx(),box.dy(),box.dz());
    XMVECTOR position = XMLoadFloat3(&XMFLOAT3(box.x(),box.y(),box.z()));
    matWorld.r[3] = XMVectorSelect( matWorld.r[3], position, XMVectorSelectControl( 1, 1, 1, 0 ) );
	//Initialize matrix.
	C4DMatrix4 matrix((const _FLOAT *)matWorld.m);
	//Draw cube.
    drawCube(pd3dDevice,matrix);
}

///////////////////////////////////////////////////////////////////////////////
//
// DrawCube
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXLinestrip::drawCube(IDirect3DDevice9* pd3dDevice,const C4DMatrix4& matrix)
{
	///////////////////////////////////////
	//
	// Change parameters type.
	//
	XMMATRIX matWorld(matrix);
	//
	///////////////////////////////////////

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif

	static XMVECTOR verts[8] =
    {
        { -1, -1, -1, 0 },
        { 1, -1, -1, 0 },
        { 1, -1, 1, 0 },
        { -1, -1, 1, 0 },
        { -1, 1, -1, 0 },
        { 1, 1, -1, 0 },
        { 1, 1, 1, 0 },
        { -1, 1, 1, 0 }
    };
    static const DWORD indices[] =
    {
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        3, 7
    };

#ifdef _DEBUG
    // copy to vertex buffer
    assert( 8 <= maxVertexCount );
#endif

    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( getVertexBuffer()->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )

    for( int i=0; i < 8; ++i )
    {
        XMVECTOR v = XMVector3Transform( verts[i], matWorld );
        XMStoreFloat3( &pVerts[i], v );
    }

    V( getVertexBuffer()->Unlock() )

#ifdef _DEBUG
    // copy to index buffer
    assert( 24 <= maxIndexCount );
#endif

    DWORD *pIndices = NULL;
    V( getIndexBuffer()->Lock( 0, 0, (void**)&pIndices, D3DLOCK_DISCARD ) )

    memcpy( pIndices, indices, sizeof(indices) );

    V( getIndexBuffer()->Unlock() )

	/*
    // Draw box
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
	*/
    pd3dDevice->SetIndices( getIndexBuffer() );
    pd3dDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, 8, 0, 12 );
}

///////////////////////////////////////////////////////////////////////////////
//
// DrawSphere
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXLinestrip::drawSphere(IDirect3DDevice9* pd3dDevice,const CSimpleSphere& sphere)
{
	//Radius.
	_FLOAT radius = sphere.r();
	//Origin.
	C4DVector3 origin(sphere.x(),sphere.y(),sphere.z());
	//Draw rings.
    drawRing(pd3dDevice,origin, C4DVector3(radius,0,0),C4DVector3(0,0,radius));
    drawRing(pd3dDevice,origin, C4DVector3(radius,0,0),C4DVector3(0,radius,0));
    drawRing(pd3dDevice,origin, C4DVector3(0,radius,0),C4DVector3(0,0,radius));
}

///////////////////////////////////////////////////////////////////////////////
//
// DrawRing
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXLinestrip::drawRing(IDirect3DDevice9* pd3dDevice,
								const C4DVector3& origin,const C4DVector3& majorAxis,const C4DVector3& minorAxis)
{
	///////////////////////////////////////
	//
	// Change parameters type.
	//
	XMFLOAT3 Origin(origin);
	XMFLOAT3 MajorAxis(majorAxis);
	XMFLOAT3 MinorAxis(minorAxis);
	//
	///////////////////////////////////////

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif

    static const DWORD dwRingSegments = 32;

    XMFLOAT3 verts[ dwRingSegments + 1 ];

    XMVECTOR vOrigin = XMLoadFloat3( &Origin );
    XMVECTOR vMajor = XMLoadFloat3( &MajorAxis );
    XMVECTOR vMinor = XMLoadFloat3( &MinorAxis );

    FLOAT fAngleDelta = XM_2PI / ( float )dwRingSegments;
    // Instead of calling cos/sin for each segment we calculate
    // the sign of the angle delta and then incrementally calculate sin
    // and cosine from then on.
    XMVECTOR cosDelta = XMVectorReplicate( cosf( fAngleDelta ) );
    XMVECTOR sinDelta = XMVectorReplicate( sinf( fAngleDelta ) );
    XMVECTOR incrementalSin = XMVectorZero();
    static const XMVECTOR initialCos =
    {
        1.0f, 1.0f, 1.0f, 1.0f
    };
    XMVECTOR incrementalCos = initialCos;
    for( DWORD i = 0; i < dwRingSegments; i++ )
    {
        XMVECTOR Pos;
        Pos = XMVectorMultiplyAdd( vMajor, incrementalCos, vOrigin );
        Pos = XMVectorMultiplyAdd( vMinor, incrementalSin, Pos );
        XMStoreFloat3( ( XMFLOAT3* )&verts[i], Pos );
        // Standard formula to rotate a vector.
        XMVECTOR newCos = incrementalCos * cosDelta - incrementalSin * sinDelta;
        XMVECTOR newSin = incrementalCos * sinDelta + incrementalSin * cosDelta;
        incrementalCos = newCos;
        incrementalSin = newSin;
    }
    verts[ dwRingSegments ] = verts[0];

#ifdef _DEBUG
    // Copy to vertex buffer
    assert( (dwRingSegments+1) <= maxVertexCount );
#endif

    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( getVertexBuffer()->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )
    memcpy( pVerts, verts, sizeof(verts) );
    V( getVertexBuffer()->Unlock() )

	/*
    // Draw ring
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
	*/
    pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, dwRingSegments );
}

///////////////////////////////////////////////////////////////////////////////
//
// DrawRay
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXLinestrip::drawRay(IDirect3DDevice9* pd3dDevice,
							const C4DVector3& origin,const C4DVector3& direction,_BOOL normalize)
{
	///////////////////////////////////////
	//
	// Change parameters type.
	//
	XMFLOAT3 Origin(origin);
	XMFLOAT3 Direction(direction);
	BOOL bNormalize = normalize;
	//
	///////////////////////////////////////

#ifdef _DEBUG
	assert(pd3dDevice != _NULL);
#endif

    XMFLOAT3 verts[3];
    memcpy( &verts[0], &Origin, 3 * sizeof( FLOAT ) );

    XMVECTOR RayOrigin = XMLoadFloat3( &Origin );
    XMVECTOR RayDirection = XMLoadFloat3( &Direction );
    XMVECTOR NormDirection = XMVector3Normalize( RayDirection );
    if( bNormalize )
        RayDirection = NormDirection;

    XMVECTOR PerpVector;
    XMVECTOR CrossVector = XMVectorSet( 0, 1, 0, 0 );
    PerpVector = XMVector3Cross( NormDirection, CrossVector );

    if( XMVector3Equal( XMVector3LengthSq( PerpVector ), XMVectorSet( 0, 0, 0, 0 ) ) )
    {
        CrossVector = XMVectorSet( 0, 0, 1, 0 );
        PerpVector = XMVector3Cross( NormDirection, CrossVector );
    }
    PerpVector = XMVector3Normalize( PerpVector );

    XMStoreFloat3( ( XMFLOAT3* )&verts[1], XMVectorAdd( RayDirection, RayOrigin ) );
    PerpVector = XMVectorScale( PerpVector, 0.0625f );
    NormDirection = XMVectorScale( NormDirection, -0.25f );
    RayDirection = XMVectorAdd( PerpVector, RayDirection );
    RayDirection = XMVectorAdd( NormDirection, RayDirection );
    XMStoreFloat3( ( XMFLOAT3* )&verts[2], XMVectorAdd( RayDirection, RayOrigin ) );
    
#ifdef _DEBUG
    // Copy to vertex buffer
    assert( 3 <= maxVertexCount );
#endif

    XMFLOAT3* pVerts = NULL;
    HRESULT hr;
    V( getVertexBuffer()->Lock( 0, 0, (void**)&pVerts, D3DLOCK_DISCARD ) )
    memcpy( pVerts, verts, sizeof(verts) );
    V( getVertexBuffer()->Unlock() )

	/*
    // Draw ray
    D3DXCOLOR clr = Color;
    g_pEffect9->SetFloatArray( g_Color, clr, 4 );
    g_pEffect9->CommitChanges();
	*/
    pd3dDevice->DrawPrimitive( D3DPT_LINESTRIP, 0, 2 );
}

///////////////////////////////////////////////////////////////////////////////
//
// Render
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXLinestrip::render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* pEffect)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(pd3dDevice != _NULL && pEffect != _NULL);
#endif

	//Get effect
	ID3DXEffect* lpEffect = pEffect->getEffectHandle();

#ifdef _DEBUG
	assert(lpEffect != _NULL);
#endif

	//Get vertex buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = getVertexBuffer();

#ifdef _DEBUG
	assert(pVertexBuffer != _NULL);
#endif

	//Set stream source.
	pd3dDevice->SetStreamSource(0,pVertexBuffer,0,sizeof(_4DVERTEX0));
	//Set flex vertex format.
	pd3dDevice->SetFVF(D3DFVF_4DVERTEX0);

	//Pass count.
	UINT nPassCount = 0;
	//Beginning of technique.
	V_RETURN(lpEffect->Begin(&nPassCount,0)); //Use default pass.

	//Do while.
	for(UINT i = 0;i < nPassCount;i ++)
	{
		//Begin pass.
		lpEffect->BeginPass(i);
		//Draw objects.
		drawObjects(pd3dDevice);
		//End pass.
		lpEffect->EndPass();
	}

	//End of technique.
	V_RETURN(lpEffect->End());
	//Return OK.
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXLinestrip::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Handle message.
		V_RETURN(CD3DXIndexAttribute::handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(CD3DXVertexAttribute::handleMessage(d3dxEvent));
		break;
	//Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) or that are tied to the back buffer size.
	case d3dxOnD3D9ResetDevice:
#ifdef _DEBUG
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Handle message.
		V_RETURN(CD3DXVertexAttribute::handleMessage(d3dxEvent));
		//Handle message.
		V_RETURN(CD3DXIndexAttribute::handleMessage(d3dxEvent));
		break;
	}
	//Return result.
	return CD3DXRenderable::handleMessage(d3dxEvent);
}
