///////////////////////////////////////////////////////////////////////////////
//
// PhysicsWorld.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsWorld.h"
#include "NewtonPhysics.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// AllocMemory
//
// This is the call back for allocation newton memory.
//
///////////////////////////////////////////////////////////////////////////////

void* AllocMemory(int sizeInBytes)
{
#ifdef _DEBUG
	assert(sizeInBytes > 0);
#endif
	//Returnr result.
	return malloc(sizeInBytes);
}

///////////////////////////////////////////////////////////////////////////////
//
// FreeMemory
//
// This is the callback for freeing Newton Memory.
//
///////////////////////////////////////////////////////////////////////////////

void FreeMemory(void *ptr,int sizeInBytes)
{
#ifdef _DEBUG
	assert(ptr != _NULL);
#endif
	//Free it.
	free(ptr);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsWorld
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsWorld::CPhysicsWorld(void)
{
	//Set default value.
	world = _NULL;
	debugger = _NULL;
	physicsManager = _NULL;

	//Set the memory allocators.
	::NewtonSetMemorySystem(::AllocMemory,::FreeMemory);

	//Create the Newton world.
	world = ::NewtonCreate();
#ifdef _DEBUG
	assert(world != _NULL);
#endif

	//Use the standard x87 floating point model.
	::NewtonSetPlatformArchitecture(WORLD_INSTANCE(world),0);

	//Set a fix world size.
	dVector minSize(-100.0f,-100.0f,-100.0f);
	dVector maxSize( 100.0f, 100.0f, 100.0f);
	//Set world size.
	::NewtonSetWorldSize(WORLD_INSTANCE(world),&minSize[0],&maxSize[0]);

#ifdef USE_VISUAL_DEBUGGER
	//Initialize Newton Visual Debugger
	debugger = ::NewtonDebuggerCreateServer();
#endif

	//Configure the Newton world to use iterative solve mode 0.
	::NewtonSetSolverModel(WORLD_INSTANCE(world),0);
}

///////////////////////////////////////////////////////////////////////////////
//
// CPhysicsWorld
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CPhysicsWorld::~CPhysicsWorld(void)
{
	//Clear value.
	physicsManager = _NULL;

#ifdef USE_VISUAL_DEBUGGER
	//Destroy the debugger server.
	if(debugger != _NULL)
	{
		//Destroy server.
		::NewtonDebuggerDestroyServer(debugger);
	}
#endif
	//Check world.
	if(world != _NULL)
	{
		//Destroy all rigid bodies.
		//This is no necessary because Newton Destroy world will also destroy all bodies.
		//But if you want to change level and restart you can call this function to clean the world without destroying the world.
		::NewtonDestroyAllBodies(WORLD_INSTANCE(world));
		//Finally destroy the newton world .
		::NewtonDestroy(WORLD_INSTANCE(world));
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// SetWorldSize
//
///////////////////////////////////////////////////////////////////////////////

void CPhysicsWorld::setWorldSize(const C4DVector3& minBox,const C4DVector3& maxBox)
{
	dVector minPos(minBox.x(),minBox.y(),minBox.z());
	dVector maxPos(maxBox.x(),maxBox.y(),maxBox.z());

#ifdef _DEBUG
	assert(world != _NULL);
#endif
	//Add some extra padding.
	minPos.m_x -=  50.0f;
	minPos.m_y -=  100.0f;
	minPos.m_z -=  50.0f;
	//Add some extra padding.
	maxPos.m_x +=  50.0f;
	maxPos.m_y +=  100.0f;
	maxPos.m_z +=  50.0f;
	//Set the new world size.
	::NewtonSetWorldSize(WORLD_INSTANCE(world),&minPos[0],&maxPos[0]);
}
