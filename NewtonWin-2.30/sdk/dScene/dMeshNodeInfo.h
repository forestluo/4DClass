/////////////////////////////////////////////////////////////////////////////
// Name:        dMeshNodeInfo.h
// Purpose:     
// Author:      Julio Jerez
// Modified by: 
// Created:     22/05/2010 08:02:08
// RCS-ID:      
// Copyright:   Copyright (c) <2010> <Newton Game Dynamics>
// License:     
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely
/////////////////////////////////////////////////////////////////////////////

#ifndef _D_MESH_NODE_INFO_H_
#define _D_MESH_NODE_INFO_H_

#include "dNodeInfo.h"
#include "dGeometryNodeInfo.h"

class dMeshNodeInfo: public dGeometryNodeInfo
{
	public:
	struct neMeshInfoFlatPoint
	{
		dFloat m_x, m_y, m_z;
		dFloat m_nx, m_ny, m_nz;
		dFloat m_u0, m_v0;
		dFloat m_u1, m_v1;
	};


	D_DEFINE_CLASS_NODE(dMeshNodeInfo,dGeometryNodeInfo)

	dMeshNodeInfo();
	dMeshNodeInfo(dScene* world);
	dMeshNodeInfo(NewtonMesh* mesh);
	dMeshNodeInfo(const dMeshNodeInfo& me);
	virtual ~dMeshNodeInfo(void);

	virtual NewtonMesh* GetMesh () const;
	virtual void ReplaceMesh (NewtonMesh* mesh);

	virtual void BakeTransform (const dMatrix& matrix);

	virtual void ConvertToPolygons();
	virtual void ConvertToTriangles();

	virtual void WeldTJoints ();
	virtual void RemoveUnusedVertices(dScene* const world, dScene::dTreeNode* const myNode);

	virtual void SmoothNormals (dFloat angleInRadiants);

	virtual void BeginBuild ();
	virtual void AddPolygon (int pointsCount, const neMeshInfoFlatPoint* const points, int materialID);
	virtual void EndBuild ();
	virtual void BuildFromVertexListIndexList(int faceCount, const int* const faceIndexCount, const int* faceMaterialIndex, 
												const dFloat* const vertex, int vertexStrideInBytes, const int* vertexIndex,
												const dFloat* const normal, int normalStrideInBytes, const int* normalIndex,
												const dFloat* const uv0, int uv0StrideInBytes, const int* uv0Index,
												const dFloat* const uv1, int uv1StrideInBytes, const int* uv1Index);


	virtual void CalculateOOBBGizmo (const dMatrix& matrix, dVector& p0, dVector& p1) const;

	virtual dFloat RayCast (const dVector& p0, const dVector& p1) const;

	
	protected:
	virtual void SerializeBinary (FILE* file);
	virtual void Serialize (TiXmlElement* rootNode) const; 
	virtual bool Deserialize (TiXmlElement* rootNode, int revisionNumber);

	NewtonMesh* m_mesh;
};





#endif