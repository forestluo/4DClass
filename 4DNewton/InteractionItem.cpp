///////////////////////////////////////////////////////////////////////////////
//
// InteractionItem.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "InteractionItem.h"

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define DEFAULT_MODE										1
#define MAX_FRICTION_ANGULAR_GRAVITY						250.0f
#define MAX_FRICTION_LINEAR_ACCELERATION					1000.0f
#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionItem
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CInteractionItem::CInteractionItem(void)
{
	//Set default value.
	mode = DEFAULT_MODE;
	controlledBody = (NewtonBody *)_NULL;
	bodyPickController = (NewtonUserJoint *)_NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// CInteractionItem
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CInteractionItem::~CInteractionItem(void)
{

}

/////////////////////////////////////////////////////////////////////////////////
//
// ClearController
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionItem::clearController()
{
	//Check pick controller.
	if(bodyPickController != _NULL)
	{
		//Destroy joint.
		::CustomDestroyJoint((NewtonUserJoint *)bodyPickController);
		//Clear value.
		bodyPickController = (NewtonUserJoint *)_NULL;
	}
	//Clear controlled body.
	controlledBody = (NewtonBody *)_NULL;
}

/////////////////////////////////////////////////////////////////////////////////
//
// CreateController
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionItem::createController(_OBJECT body,_INTEGER mode,const C4DVector3& point)
{
	//Set pick point.
	pickPoint = point;
	//Point.
	dVector p(point.x(),point.y(),point.z());

#ifdef _DEBUG
	assert(body != _NULL);
#endif
	//Set body.
	controlledBody = (NewtonBody *)body;

	//Create pick body joint.
	bodyPickController = ::CreateCustomKinematicController((NewtonBody *)body,&p[0]);
#ifdef _DEBUG
	assert(bodyPickController != _NULL);
#endif
	//Check mode.
	if(mode == 0)
	{
		::CustomKinematicControllerSetPickMode((NewtonUserJoint *)bodyPickController,mode);
		::CustomKinematicControllerSetMaxAngularFriction((NewtonUserJoint *)bodyPickController,10.0f);
		::CustomKinematicControllerSetMaxLinearFriction((NewtonUserJoint *)bodyPickController,MAX_FRICTION_LINEAR_ACCELERATION);
	}
	else if(mode == 1)
	{
		::CustomKinematicControllerSetPickMode((NewtonUserJoint *)bodyPickController,mode);
		::CustomKinematicControllerSetMaxAngularFriction((NewtonUserJoint *)bodyPickController,MAX_FRICTION_ANGULAR_GRAVITY);
		::CustomKinematicControllerSetMaxLinearFriction((NewtonUserJoint *)bodyPickController,MAX_FRICTION_LINEAR_ACCELERATION);
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// PickBody
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionItem::pickBody(_OBJECT body,const C4DVector3& point)
{
	//Check body.
	if(body == _NULL || body != controlledBody)
	{
		//Clear controller.
		clearController();
		//Check body.
		if(body != _NULL)
		{
			//Create controller.
			createController(body,mode,point);
			//Move body.
			moveBody(body,C4DVector3(0.0f,0.0f,0.0f));
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////
//
// MoveBody
//
/////////////////////////////////////////////////////////////////////////////////

void CInteractionItem::moveBody(_OBJECT body,const C4DVector3& direction)
{
	//Check body.
	if(body != _NULL && body == controlledBody)
	{
		//Check controller.
		if(bodyPickController != _NULL)
		{
			//Add direction.
			pickPoint += direction;
			//Point.
			dVector p(pickPoint.x(),pickPoint.y(),pickPoint.z());
			//Set pick body to target position.
			::CustomKinematicControllerSetTargetPosit((NewtonUserJoint *)bodyPickController,&p[0]);
		}
	}
}
