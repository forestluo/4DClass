///////////////////////////////////////////////////////////////////////////////
//
// SimulationManager.cpp
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include "SimulationManager.h"
#include "NewtonPhysics.h"
#include "EntityManager.h"
#include "PhysicsManager.h"

///////////////////////////////////////////////////////////////////////////////
//
// Definition
//
///////////////////////////////////////////////////////////////////////////////

#define PHYSICS_FPS											120.0f
#define FPS_IN_MICROSECUNDS									(int(1000000.0f/PHYSICS_FPS))
#define MAX_PHYSICS_LOOPS									1

#define WORLD_INSTANCE(p)									((const NewtonWorld *)(p))

///////////////////////////////////////////////////////////////////////////////
//
// CSimulationManager
//
// Default construction.
//
/////////////////////////////////////////////////////////////////////////////////

CSimulationManager::CSimulationManager(void)
{
	//Clear pause.
	pause = _FALSE;
	//Set default value.
	timeAccumulator = FPS_IN_MICROSECUNDS;
	//Set current time.
	physicTime = getTimeInMicroseconds();
	currentTime = getTimeInMicroseconds();
}

///////////////////////////////////////////////////////////////////////////////
//
// CSimulationManager
//
// Default deconstruction.
//
/////////////////////////////////////////////////////////////////////////////////

CSimulationManager::~CSimulationManager(void)
{

}

////////////////////////////////////////////////////////////////////////////////
//
// DoSimulation
//
////////////////////////////////////////////////////////////////////////////////

_LONG CSimulationManager::doSimulation()
{
	//Check pause status.
	if(pause)
	{
		//Set current time.
		currentTime = getTimeInMicroseconds();
	}
	else
	{
		//Do simulation.
		advanceSimulation(getTimeInMicroseconds());
		//Begin.
		if(physicsManager != _NULL)
		{
			//End of physics paragram.
			((CPhysicsManager *)physicsManager)->paragramEnd(currentTime);
		}
	}
	//Return current time.
	return currentTime;
}

///////////////////////////////////////////////////////////////////////////////
//
// PauseSimulation
//
///////////////////////////////////////////////////////////////////////////////

void CSimulationManager::pauseSimulation() {pause = _TRUE;}

///////////////////////////////////////////////////////////////////////////////
//
// ResumeSimulation
//
///////////////////////////////////////////////////////////////////////////////

void CSimulationManager::resumeSimulation() {pause = _FALSE;}

///////////////////////////////////////////////////////////////////////////////
//
// IsSimulationPaused
//
///////////////////////////////////////////////////////////////////////////////

_BOOL CSimulationManager::isSimulationPaused() {return pause;}

///////////////////////////////////////////////////////////////////////////////
//
// AdvanceSimulation
//
///////////////////////////////////////////////////////////////////////////////

void CSimulationManager::advanceSimulation(_LONG milliseconds)
{
#ifdef _DEBUG
	assert(world != _NULL);
#endif

	//Do the physics simulation here
	_LONG deltaTime;
	_LONG physicLoopsTimeAcc;

	//Get the time step.
	deltaTime = milliseconds - currentTime;
	currentTime = milliseconds;
	timeAccumulator += deltaTime;

	physicTime = 0;
	//Advance the simulation at a fix step.
	_INTEGER loops = 0;
	physicLoopsTimeAcc = 0;

	//Do while.
	while((loops < MAX_PHYSICS_LOOPS) && (timeAccumulator >= FPS_IN_MICROSECUNDS))
	{
		//Add loop.
		loops ++;

		//Sample time before the update.
		physicTime = getTimeInMicroseconds();
		//Run the newton update function.
		NewtonUpdate(WORLD_INSTANCE(world),1.0f / PHYSICS_FPS);
		//Calculate the time spent in the physical simulation.
		physicTime = getTimeInMicroseconds() - physicTime;

#ifdef USE_VISUAL_DEBUGGER
		//Call the visual debugger to show the physics scene.
		//::NewtonDebuggerServe(debugger,world);
#endif
		//Subtract time from time accumulator.
		timeAccumulator -= FPS_IN_MICROSECUNDS;
		physicTime ++;
		physicLoopsTimeAcc += physicTime;
	}
	//Check loops.
	if(loops > MAX_PHYSICS_LOOPS)
	{
		//Set physics time.
		physicTime = physicLoopsTimeAcc;
		//Set time accumulator.
		timeAccumulator = FPS_IN_MICROSECUNDS;
	}
#ifdef _DEBUG
	assert(physicsManager != _NULL);
#endif
	//Set paragram.
	((CPhysicsManager *)physicsManager)->setParagram(dFloat(timeAccumulator) / dFloat(FPS_IN_MICROSECUNDS));
}
