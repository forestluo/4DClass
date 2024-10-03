///////////////////////////////////////////////////////////////////////////////
//
// D3DXFileMesh.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXFileMesh.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SDKmesh.h"

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
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define MESH_INSTANCE(p)									((CDXUTXFileMesh *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CD3DXFileMesh::base(L"CD3DXFileMesh",L"CD3DXRenderable");

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXFileMesh
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXFileMesh::CD3DXFileMesh(void)
{
	//Create mesh.
	mesh = new CDXUTXFileMesh();
#ifdef _DEBUG
	assert(mesh != _NULL);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXFileMesh
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXFileMesh::~CD3DXFileMesh(void)
{
	//Check result.
	if(mesh != _NULL)
	{
		//Delete instance.
		delete MESH_INSTANCE(mesh);
		//Clear value.
		mesh = (CDXUTXFileMesh *)_NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// GetMesh
//
///////////////////////////////////////////////////////////////////////////////

_OBJECT CD3DXFileMesh::getMesh() const
{
	//Return result.
	return mesh;
}

///////////////////////////////////////////////////////////////////////////////
//
// GetFileName
//
///////////////////////////////////////////////////////////////////////////////

const CNormalString& CD3DXFileMesh::getFileName() const
{
	//Return result.
	return fileName;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetFileName
//
///////////////////////////////////////////////////////////////////////////////

void CD3DXFileMesh::setFileName(const CNormalString& fileName)
{
#ifdef _DEBUG
	assert(fileName.length() > 0);
#endif
	//Set file name.
	this->fileName = fileName;
}

/////////////////////////////////////////////////////////////////////////////////
//
// LoadFromFile
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXFileMesh::loadFromFile(IDirect3DDevice9* pd3dDevice,const CNormalString& fileName)
{
	//Result.
	HRESULT hr;
	//Vertices.
    LPVOID pVertices = _NULL;

#ifdef _DEBUG
	assert(mesh != _NULL);
	assert(pd3dDevice != _NULL && fileName.length() > 0);
#endif
	//Get result.
	V_RETURN(MESH_INSTANCE(mesh)->Create(pd3dDevice,fileName.getCString()));
	//Lock vertex buffer.
    if( SUCCEEDED( MESH_INSTANCE(mesh)->GetMesh()->LockVertexBuffer( 0, &pVertices ) ) )
    {
		//Sphere.
		XNA::Sphere xnaSphere;
		//Calculate sphere.
		ComputeBoundingSphereFromPoints(&xnaSphere,
			MESH_INSTANCE(mesh)->GetMesh()->GetNumVertices(),
			(XMFLOAT3 *)pVertices,
			MESH_INSTANCE(mesh)->GetMesh()->GetNumBytesPerVertex());

		//Box.
		XNA::AxisAlignedBox xnaBox;
		//Calculate AA box.
		ComputeBoundingAxisAlignedBoxFromPoints(&xnaBox,
			MESH_INSTANCE(mesh)->GetMesh()->GetNumVertices(),
			(XMFLOAT3 *)pVertices,
			MESH_INSTANCE(mesh)->GetMesh()->GetNumBytesPerVertex());

		//Unlock vertex buffer.
        MESH_INSTANCE(mesh)->GetMesh()->UnlockVertexBuffer();

		//Box.
		CSimpleBox box;
		//Set value.
		box.x() = xnaBox.Center.x;
		box.y() = xnaBox.Center.y;
		box.z() = xnaBox.Center.z;
		box.dx() = xnaBox.Extents.x;
		box.dy() = xnaBox.Extents.y;
		box.dz() = xnaBox.Extents.z;
		//Set box.
		setBox(box);

		//Sphere.
		CSimpleSphere sphere;
		//Set value.
		sphere.r() = xnaSphere.Radius;
		sphere.x() = xnaSphere.Center.x;
		sphere.y() = xnaSphere.Center.y;
		sphere.z() = xnaSphere.Center.z;
		//Set sphere.
		setSphere(sphere);
    }
	//Return result.
	return hr;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXFileMesh::pick(CPickRay& pickRay)
{
	//Intersection.
	CPickIntersection* pIntersection = (CPickIntersection *)_NULL;

#ifdef _DEBUG
	assert(mesh != _NULL);
#endif

    // When calling D3DXIntersect, one can get just the closest intersection and not
    // need to work with a D3DXBUFFER.  Or, to get all intersections between the ray and 
    // the mesh, one can use a D3DXBUFFER to receive all intersections.  We show both
    // methods.
	if( !pickRay.isAllHitsNeeded() )
    {
        // Collect only the closest intersection
        BOOL bHit;
        DWORD dwFace;
        FLOAT fBary1, fBary2, fDist;
        D3DXIntersect( MESH_INSTANCE(mesh)->GetMesh(),
						&D3DXVECTOR3(pickRay.getPickOrigin()),
						&D3DXVECTOR3(pickRay.getPickDirection()),
						&bHit, &dwFace, &fBary1, &fBary2, &fDist, NULL, NULL );
        if( bHit )
        {
			//Create pick intersection.
			pIntersection = new CPickIntersection();
#ifdef _DEBUG
			assert(pIntersection != NULL);
#endif
			//Declare pick.
			PickIntersection pick;
			//Initialize it.
			ZeroMemory(&pick,sizeof(PickIntersection));
			//Set value.
			pick.dwFace = 0;
			pick.fBary1 = fBary1;
			pick.fBary2 = fBary2;
			pick.fDist = fDist;
			//Add it into picks.
			pIntersection->addIntersection(pick);
        }
    }
    else
    {
        // Collect all intersections
        BOOL bHit;
		DWORD dwNumIntersections;
        LPD3DXBUFFER pBuffer = NULL;
        if( SUCCEEDED( D3DXIntersect( MESH_INSTANCE(mesh)->GetMesh(),
										&D3DXVECTOR3(pickRay.getPickOrigin()),
										&D3DXVECTOR3(pickRay.getPickDirection()),
										&bHit, NULL, NULL, NULL, NULL,&pBuffer, &dwNumIntersections ) ) )
        {
			if( dwNumIntersections > 0 )
			{
				//Create pick intersection.
				pIntersection = new CPickIntersection();
#ifdef _DEBUG
				assert(pIntersection != NULL);
#endif
				D3DXINTERSECTINFO* pIntersectInfoArray = ( D3DXINTERSECTINFO* )pBuffer->GetBufferPointer();
				//Add all intersections.
				for( DWORD iIntersection = 0; iIntersection < dwNumIntersections; iIntersection++ )
				{
					//Declare pick.
					PickIntersection pick;
					//Initialize it.
					ZeroMemory(&pick,sizeof(PickIntersection));
					//Set value.
					pick.dwFace = pIntersectInfoArray[iIntersection].FaceIndex;
					pick.fBary1 = pIntersectInfoArray[iIntersection].U;
					pick.fBary2 = pIntersectInfoArray[iIntersection].V;
					pick.fDist = pIntersectInfoArray[iIntersection].Dist;
					//Add it into picks.
					pIntersection->addIntersection(pick);
				}
			}
			SAFE_RELEASE( pBuffer );
		}
	}
	//Return null.
	return pIntersection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Render
//
/////////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXFileMesh::render(IDirect3DDevice9* pd3dDevice,CD3DXEffect* pEffect)
{
#ifdef _DEBUG
	assert(mesh != _NULL);
	assert(pd3dDevice != NULL && pEffect != NULL);
#endif
	//Check material defined.
	if(pEffect->isMaterialDefinded())
	{
		//Return result.
		return MESH_INSTANCE(mesh)->Render(pEffect->getEffectHandle(),
							pEffect->getParameterHandle(CD3DXEffect::semMaterialTexture),
							pEffect->getParameterHandle(CD3DXEffect::semMaterialDiffuse),
							pEffect->getParameterHandle(CD3DXEffect::semMaterialAmbient),
							pEffect->getParameterHandle(CD3DXEffect::semMaterialSpecular),
							pEffect->getParameterHandle(CD3DXEffect::semMaterialEmissive));
	}
	//Return result.
	return MESH_INSTANCE(mesh)->Render(pEffect->getEffectHandle());
}

///////////////////////////////////////////////////////////////////////////////
//
// HandleMessage
//
///////////////////////////////////////////////////////////////////////////////

HRESULT CD3DXFileMesh::handleMessage(const D3DXEvent& d3dxEvent)
{
	//Result.
	HRESULT hr;

#ifdef _DEBUG
	assert(mesh != _NULL);
#endif

	//Check event id.
	switch(d3dxEvent.d3dxEventID)
	{
	//Release D3D9 resources created in the OnD3D9CreateDevice callback.
	case d3dxOnD3D9DestroyDevice:
		//Destroy.
		V_RETURN(MESH_INSTANCE(mesh)->Destroy());
		break;
	//Release D3D9 resources created in the OnD3D9ResetDevice callback.
	case d3dxOnD3D9LostDevice:
		//Invalidate device objects.
		V_RETURN(MESH_INSTANCE(mesh)->InvalidateDeviceObjects());
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
		assert(d3dxEvent.d3dxResetDevice9.pd3dDevice != NULL);
#endif
		//Restore device objects
		V_RETURN(MESH_INSTANCE(mesh)->RestoreDeviceObjects(d3dxEvent.d3dxResetDevice9.pd3dDevice));
		break;
	}
	//Return result.
	return CD3DXRenderable::handleMessage(d3dxEvent);
}
