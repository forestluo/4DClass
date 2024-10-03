///////////////////////////////////////////////////////////////////////////////
//
// SimulationManager.h
// 
// 4DClass Developer
// Copyright (c) 4DClass. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _SIMULATION_MANAGER_H_
#define _SIMULATION_MANAGER_H_

#pragma once

///////////////////////////////////////////////////////////////////////////////
//
// Including
//
///////////////////////////////////////////////////////////////////////////////

#include "PhysicsTime.h"
#include "PhysicsWorld.h"

///////////////////////////////////////////////////////////////////////////////
//
// CSimulationManager
//
///////////////////////////////////////////////////////////////////////////////

class CSimulationManager :
	public virtual CPhysicsWorld,
	public CPhysicsTime
{
private:
	/**
	 * Pause.
	 */
	_BOOL pause;

private:
	/**
	 * Physics time.
	 */
	_LONG physicTime;
	/**
	 * Current time.
	 */
	_LONG currentTime;
	/**
	 * Accumulator.
	 */
	_LONG timeAccumulator;

public:
	CSimulationManager(void);
	virtual ~CSimulationManager(void);

protected:

	/**
	 * Advance simulation.
	 *
	 * @param microseconds Time in microsenconds.
	 * @return
	 *     <p>Interpolation paragram.</p>
	 */
	void advanceSimulation(_LONG microseconds);

public:

	/**
	 * Do simulation.
	 *
	 * @param None No parameter needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	_LONG doSimulation();

	/**
	 * Pause simulation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void pauseSimulation();

	/**
	 * Resume simulation.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void resumeSimulation();

	/**
	 * Whether is paused.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if it is paused.</p>
	 */
	_BOOL isSimulationPaused();
	
};

///////////////////////////////////////////////////////////////////////////////
#endif //_SIMULATION_MANAGER_H_
