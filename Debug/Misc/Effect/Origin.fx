//--------------------------------------------------------------------------------------
// File: Original.fx
//
// Copyright (c) 4DClass Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4x4 g_mWorld	: WORLD;	//World matrix
float4x4 g_mView	: VIEW;		//View matrix
float4x4 g_mProjection	: PROJECTION;	//Projection matrix

//--------------------------------------------------------------------------------------
// Computes position
//--------------------------------------------------------------------------------------
float4 vs_PositionOnly( float4 vPos : POSITION ) : POSITION
{
    return mul( mul( mul( vPos, g_mWorld ), g_mView), g_mProjection);
}

//--------------------------------------------------------------------------------------
// Compute color
//--------------------------------------------------------------------------------------
float4 ps_OriginalColor( float4 vCol : COLOR ) : COLOR
{
    return vCol;
}

//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
    pass P0
    {          
        VertexShader = compile vs_2_0 vs_PositionOnly();
        PixelShader  = compile ps_2_0 ps_OriginalColor();
    }
}
