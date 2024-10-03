///////////////////////////////////////////////////////////////////////////////
//
// Sketch1.cpp
//  
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "Sketch1.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "SimpleSphere.h"
#include "D3DXJointObject.h"
#include "PhysicsJointObject.h"
#include "JointObjectSketcher.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define SKETCHER_INSTANCE(p)								((CJointObjectSketcher *)(p))
#define RED_COLOR											D3DCOLOR_RGBA(255,0,0,255)
#define GREEN_COLOR											D3DCOLOR_RGBA(0,255,0,255)
#define BLUE_COLOR											D3DCOLOR_RGBA(0,0,255,255)
#define YELLOW_COLOR										D3DCOLOR_RGBA(255,255,0,255)
#define WHITE_COLOR											D3DCOLOR_RGBA(255,255,255,255)

///////////////////////////////////////////////////////////////////////////////
//
// Global
//
///////////////////////////////////////////////////////////////////////////////

//Set base of object.
const C4DBase CSketch1::base(L"CSketch1",L"CSketch0");

///////////////////////////////////////////////////////////////////////////////
//
// CSketch1
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketch1::CSketch1(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// CSketch1
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CSketch1::~CSketch1(void)
{

}

///////////////////////////////////////////////////////////////////////////////
//
// DrawObjects
//
///////////////////////////////////////////////////////////////////////////////

void CSketch1::drawObjects(IDirect3DDevice9* pd3dDevice)
{
	//Call function.
	CSketch0::drawObjects(pd3dDevice);

#ifdef _DEBUG
	assert(sketcher != _NULL);
#endif
	//Get joint sketcher.
	CJointObjectSketcher* jointSketcher = (CJointObjectSketcher *)sketcher;

	//Get world joint.
	CWorldObject* worldJoint = jointSketcher->getOwner();
#ifdef _DEBUG
	assert(worldJoint != _NULL);
#endif
	//Check world joint.
	if(!worldJoint->isJointObject() || !worldJoint->isRenderablePhysicsObject()) return;

	//Get physics joint.
	CPhysicsJointObject* physicsJoint = (CPhysicsJointObject *)((CPhysicsObject *)(worldJoint->getPhysics()));
#ifdef _DEBUG
	assert(physicsJoint != _NULL);
#endif
	//Get renderable joint.
	CD3DXJointObject* renderableJoint = (CD3DXJointObject *)((CD3DXRenderableObject *)worldJoint->getRenderable());
#ifdef _DEBUG
	assert(renderableJoint != _NULL);
#endif

	//Get physics child.
	CPhysicsObject* physicsChild = (CPhysicsObject*)_NULL;
	//Get world child.
	CWorldObject* worldChild = renderableJoint->getJointChild();
	//Check result.
	if(worldChild != _NULL)
	{
		//Check physics type.
		if(!worldChild->isPhysicsObject()) return;
		//Set physics child.
		physicsChild = (CPhysicsObject *)(worldChild->getPhysics());
	}
	
	//Get effect.
	CD3DXEffect* pEffect = getEffect();
#ifdef _DEBUG
	assert(pEffect != NULL);
#endif

	//Set use world.
	pEffect->setUseWorld(_FALSE);
	//Commit changes.
	pEffect->commitChanges();

	//Check result.
	if(physicsChild != _NULL)
	{
		//Get child position.
		C4DVector3 childPosition = physicsChild->getPosition();
		//Get child axis direction.
		C4DVector3 childDirection = physicsJoint->getRelativeDirection(_TRUE);

		//Set color.
		pEffect->setColor(GREEN_COLOR);
		//Commit changes.
		pEffect->commitChanges();

		//Check flag.
		if(SKETCHER_INSTANCE(sketcher)->drawJointSphere)
		{
			//Sphere.
			CSimpleSphere sphere;
			//Set center.
			sphere.x() = childPosition.x();
			sphere.y() = childPosition.y();
			sphere.z() = childPosition.z();
			//Set radius.
			sphere.r() = childDirection.length();
			//Draw sphere.
			drawSphere(pd3dDevice,sphere);
		}
		//Vector.
		C4DVector3 vector = physicsChild->getRotationAccompany(- childDirection);
		//Check flag.
		if(SKETCHER_INSTANCE(sketcher)->drawJointPosition)
		{
			//Draw ray.
			drawRay(pd3dDevice,childPosition,vector,_FALSE);
		}
		//Get direction in child axis.
		C4DVector3 direction = physicsChild->getRotationAccompany(physicsJoint->getMajorDirection());
		//Check flag.
		if(SKETCHER_INSTANCE(sketcher)->drawJointDirection)
		{
			//Draw ray.
			drawRay(pd3dDevice,childPosition + vector,direction,_TRUE);
		}
	}

	//Check type of joint.
	if(renderableJoint->getJointType() == CJointAttribute::classicUpVectorJoint) return;

	//Get physics parent.
	CPhysicsObject* physicsParent = (CPhysicsObject*)_NULL;
	//Get world parent.
	CWorldObject* worldParent = renderableJoint->getJointParent();
	//Check result.
	if(worldParent != _NULL)
	{
		//Check physics type.
		if(!worldParent->isPhysicsObject()) return;
		//Set physics parent.
		physicsParent = (CPhysicsObject *)(worldParent->getPhysics());
	}

	//Check result.
	if(physicsParent != _NULL)
	{
		//Get parent position.
		C4DVector3 parentPosition = physicsParent->getPosition();
		//Get parent axis direction.
		C4DVector3 parentDirection = physicsJoint->getRelativeDirection(_FALSE);

		//Set color.
		pEffect->setColor(YELLOW_COLOR);
		//Commit changes.
		pEffect->commitChanges();

		//Check draw sphere.
		if(SKETCHER_INSTANCE(sketcher)->drawJointSphere)
		{
			//Sphere.
			CSimpleSphere sphere;
			//Set center.
			sphere.x() = parentPosition.x();
			sphere.y() = parentPosition.y();
			sphere.z() = parentPosition.z();
			//Set radius.
			sphere.r() = parentDirection.length();
			//Draw sphere.
			drawSphere(pd3dDevice,sphere);
		}
		//Vector.
		C4DVector3 vector = physicsParent->getRotationAccompany(- parentDirection);
		//Check result.
		if(SKETCHER_INSTANCE(sketcher)->drawJointPosition)
		{
			//Draw ray.
			drawRay(pd3dDevice,parentPosition,vector,_FALSE);
		}
		//Get direction in parent axis.
		C4DVector3 direction = physicsParent->getRotationAccompany(physicsJoint->getMinorDirection());
		//Check result.
		if(SKETCHER_INSTANCE(sketcher)->drawJointDirection)
		{
			//Draw ray.
			drawRay(pd3dDevice,parentPosition + vector,direction,_TRUE);
		}
	}
}
