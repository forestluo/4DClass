//--------------------------------------------------------------------------------------
// File: EffectStateManager.h
//
// Base implementation of a custom ID3DXEffectStateManager interface
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma once
#ifndef _EFFECTStateManager_H_
#define _EFFECTStateManager_H_



//--------------------------------------------------------------------------------------
// Base implementation of a custom ID3DXEffectStateManager interface
//--------------------------------------------------------------------------------------
class CStateManagerInterface : public ID3DXEffectStateManager
{
public:

    virtual         ~CStateManagerInterface()
    {
    };       // virtual destructor, for cleanup purposes
    virtual void    DirtyCachedValues() = 0;       // Cause any cached state change values to be invalid
    virtual LPCWSTR EndFrameStats() = 0;        // Called once per frame retrieve statistics

    // Create a state manager interface for the device
    static CStateManagerInterface*
        CStateManagerInterface::Create( LPDIRECT3DDEVICE9 pDevice );
};

#endif //_EFFECTStateManager_H_
