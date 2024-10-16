/////////////////////////////////////////////////////////////////////////////
// Name:        dCollisionSphereNodeInfo.h
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

#ifndef _D_COLLISION_SPHERE_NODE_H_
#define _D_COLLISION_SPHERE_NODE_H_


#include "dCollisionNodeInfo.h"

class dCollisionSphereNodeInfo: public dCollisionNodeInfo
{
	public:
	D_DEFINE_CLASS_NODE(dCollisionSphereNodeInfo,dCollisionNodeInfo)

	dCollisionSphereNodeInfo();
	dCollisionSphereNodeInfo(dScene* world);
	dCollisionSphereNodeInfo(NewtonCollision* sphere);
	virtual ~dCollisionSphereNodeInfo(void);

	virtual void SetRadius (const dVector& size);
	virtual const dVector& GetRadius () const;

	virtual void BakeTransform (const dMatrix& transform);
	virtual void CalculateInertiaGeometry (dScene* world, dVector& Inertia, dVector& centerOfMass) const; 

//	virtual void UpdateOOBB (dGeometryNodeInfo* geomInfo);
//	virtual dFloat RayCast (const dVector& p0, const dVector& p1) const;

	// draw scene in wire frame mode
	virtual void DrawWireFrame(dScene* const world, dScene::dTreeNode* const myNode, const dVector& color) const;

	// draw scene in solid wire frame mode
	virtual void DrawSolidWireFrame(dScene* const world, dScene::dTreeNode* const myNode, const dVector& color) const;

	// draw scene in Gouraud shaded normal textured mode 
	virtual void DrawGouraudShaded(dScene* const world, dScene::dTreeNode* const myNode, const dVector& color) const;

	// Draw selection gizmo
	virtual void DrawGizmo(dScene* const world, dScene::dTreeNode* const myNode, const dMatrix& coordinaSystem, const dVector& color, dGizmoMode mode, dFloat size) const;
	virtual dGizmoHandle GetHighlightedGizmoHandle(dScene* const world, dScene::dTreeNode* const myNode, const dMatrix& coordinaSystem, const dVector& screenPosition, dGizmoMode mode, dFloat size) const;
	virtual void DrawGizmoHandle(dScene* world, const dMatrix& coordinaSystem, dGizmoMode mode, dGizmoHandle handle, const dVector& color, dFloat size) const;

	protected:
	virtual void SerializeBinary (FILE* file);
	virtual void Serialize (TiXmlElement* rootNode) const; 
	virtual bool Deserialize (TiXmlElement* rootNode, int revisionNumber);
	virtual NewtonCollision* CreateNewtonCollision (NewtonWorld* const world, dScene* const scene, dScene::dTreeNode* const myNode) const;
	
	dVector m_radius;
	
};





#endif