///////////////////////////////////////////////////////////////////////////////
//
// D3DXPickAttribute.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "D3DXPickAttribute.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
/////////////////////////////////////////////////////////////////////////////////

#include "DxMath.h"
#include "D3DXVertex.h"

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPickAttribute
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPickAttribute::CD3DXPickAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CD3DXPickAttribute
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CD3DXPickAttribute::~CD3DXPickAttribute(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// Pick
//
///////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXPickAttribute::pick(CPickRay& pickRay)
{
	//Return null.
	return (CPickIntersection *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick0
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXPickAttribute::pick0(LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count)
{
	//Intersection.
	CPickIntersection* pIntersection = (CPickIntersection *)_NULL;
	//Get vertext buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = vertexBuffer;
	//Check result.
	if(pVertexBuffer == _NULL || count < 3) return pIntersection;

	//Vertex
	_4DVERTEX0* pVertexArray = NULL;
	//Lock buffer.
	if(SUCCEEDED(pVertexBuffer->Lock(0,0,(void **)&pVertexArray,D3DLOCK_READONLY | D3DLOCK_DISCARD)))
	{
		FLOAT fBary1, fBary2;
		FLOAT fDist;

		//Do while.
		for(_INTEGER i = 0;i < count;i ++)
		{
			//Initialize points.
			D3DXVECTOR3 v0 = D3DXVECTOR3(pVertexArray->_x,pVertexArray->_y,pVertexArray->_z);
			//Add stride size.
			pVertexArray ++;

			D3DXVECTOR3 v1 = D3DXVECTOR3(pVertexArray->_x,pVertexArray->_y,pVertexArray->_z);
			//Add stride size.
			pVertexArray ++;

			D3DXVECTOR3 v2 = D3DXVECTOR3(pVertexArray->_x,pVertexArray->_y,pVertexArray->_z);
			//Add stride size.
			pVertexArray ++;

			//Check if the Pick ray passes through this point.
			if(::IntersectTriangle(D3DXVECTOR3(pickRay.getPickOrigin()),
								 D3DXVECTOR3(pickRay.getPickDirection()),
								 v0,v1,v2,&fDist,&fBary1,&fBary2))
			{
				//Check intersection.
				if(pIntersection == NULL)
				{
					//Create pick intersection.
					pIntersection = new CPickIntersection();
#ifdef _DEBUG
					assert(pIntersection != NULL);
#endif
				}
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
		//Unlock buffer.
		pVertexBuffer->Unlock();
	}
	//Return intersection.
	return pIntersection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick0
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXPickAttribute::pick0(LPDIRECT3DINDEXBUFFER9 indexBuffer,LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count)
{
	//Intersection.
	CPickIntersection* pIntersection = (CPickIntersection *)_NULL;
	//Get index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = indexBuffer;
	//Check result.
	if(pIndexBuffer == _NULL) return (CPickIntersection *)_NULL;
	//Get vertext buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = vertexBuffer;
	//Check result.
	if(pVertexBuffer == _NULL || count <= 0) return (CPickIntersection *)_NULL;

	//Vertex
	_4DVERTEX0* pVertexArray = NULL;
	//Lock buffer.
	if(SUCCEEDED(pVertexBuffer->Lock(0,0,(void **)&pVertexArray,D3DLOCK_READONLY | D3DLOCK_DISCARD)))
	{
		//Index
		DWORD* pIndexArray = NULL;
		//Lock buffer.
		if(SUCCEEDED(pIndexBuffer->Lock(0,0,(void **)&pIndexArray,D3DLOCK_READONLY | D3DLOCK_DISCARD)))
		{
			//Do while.
			for(int i = 0;i < count;i ++)
			{
				_4DVERTEX0* pVertex;

				FLOAT fBary1, fBary2;
				FLOAT fDist;

				//Get index.
				int nIndex0 = pIndexArray[3 * i];
				int nIndex1 = pIndexArray[3 * i + 1];
				int nIndex2 = pIndexArray[3 * i + 2];

				//Get offset.
				pVertex = pVertexArray + nIndex0;
				//Initialize point.
				D3DXVECTOR3 v0 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);

				//Get offset.
				pVertex = pVertexArray + nIndex1;
				//Initialize point.
				D3DXVECTOR3 v1 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);;

				//Get offset.
				pVertex = pVertexArray + nIndex2;
				//Initialize point.
				D3DXVECTOR3 v2 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);;

				//Check if the Pick ray passes through this point.
				if(::IntersectTriangle(D3DXVECTOR3(pickRay.getPickOrigin()),
									 D3DXVECTOR3(pickRay.getPickDirection()),
									 v0, v1, v2, &fDist, &fBary1, &fBary2 ) )
				{
					//Check intersection.
					if(pIntersection == NULL)
					{
						//Create pick intersection.
						pIntersection = new CPickIntersection();
#ifdef _DEBUG
						assert(pIntersection != NULL);
#endif
					}
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
			//Unlock buffer.
			pVertexBuffer->Unlock();
		}
		//Unlock buffer.
		pIndexBuffer->Unlock();
	}
	//Return null.
	return pIntersection;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Pick3
//
/////////////////////////////////////////////////////////////////////////////////

CPickIntersection* CD3DXPickAttribute::pick3(LPDIRECT3DINDEXBUFFER9 indexBuffer,LPDIRECT3DVERTEXBUFFER9 vertexBuffer,CPickRay& pickRay,_INTEGER count)
{
	//Intersection.
	CPickIntersection* pIntersection = (CPickIntersection *)_NULL;
	//Get index buffer.
	LPDIRECT3DINDEXBUFFER9 pIndexBuffer = indexBuffer;
	//Check result.
	if(pIndexBuffer == _NULL) return (CPickIntersection *)_NULL;
	//Get vertext buffer.
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = vertexBuffer;
	//Check result.
	if(pVertexBuffer == _NULL || count <= 0) return (CPickIntersection *)_NULL;

	//Vertex
	_4DVERTEX3* pVertexArray = NULL;
	//Lock buffer.
	if(SUCCEEDED(pVertexBuffer->Lock(0,0,(void **)&pVertexArray,D3DLOCK_READONLY | D3DLOCK_DISCARD)))
	{
		//Index
		DWORD* pIndexArray = NULL;
		//Lock buffer.
		if(SUCCEEDED(pIndexBuffer->Lock(0,0,(void **)&pIndexArray,D3DLOCK_READONLY | D3DLOCK_DISCARD)))
		{
			//Do while.
			for(_INTEGER i = 0;i < count;i ++)
			{
				_4DVERTEX3* pVertex;

				FLOAT fBary1, fBary2;
				FLOAT fDist;

				//Get index.
				int nIndex0 = pIndexArray[3 * i];
				int nIndex1 = pIndexArray[3 * i + 1];
				int nIndex2 = pIndexArray[3 * i + 2];

				//Get offset.
				pVertex = pVertexArray + nIndex0;
				//Initialize point.
				D3DXVECTOR3 v0 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);

				//Get offset.
				pVertex = pVertexArray + nIndex1;
				//Initialize point.
				D3DXVECTOR3 v1 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);;

				//Get offset.
				pVertex = pVertexArray + nIndex2;
				//Initialize point.
				D3DXVECTOR3 v2 = D3DXVECTOR3(pVertex->_x,pVertex->_y,pVertex->_z);;

				//Check if the Pick ray passes through this point.
				if(::IntersectTriangle(D3DXVECTOR3(pickRay.getPickOrigin()),
									 D3DXVECTOR3(pickRay.getPickDirection()),
									 v0, v1, v2, &fDist, &fBary1, &fBary2 ) )
				{
					//Check intersection.
					if(pIntersection == NULL)
					{
						//Create pick intersection.
						pIntersection = new CPickIntersection();
#ifdef _DEBUG
						assert(pIntersection != NULL);
#endif
					}
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
			//Unlock buffer.
			pVertexBuffer->Unlock();
		}
		//Unlock buffer.
		pIndexBuffer->Unlock();
	}
	//Return null.
	return pIntersection;
}
