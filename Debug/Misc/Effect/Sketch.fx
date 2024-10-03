//--------------------------------------------------------------------------------------
// File: Basic.fx
//
// Copyright (c) 4DClass Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Global variables
//--------------------------------------------------------------------------------------
float4   g_Color 		: OBJECTCOLOR = float4(0.9,0.9,0.9,1.0); //Global color

bool     g_bUseWorld		: USEWORLD = true;	//Use world or not
float4x4 g_mWorld		: WORLD;		//World matrix
float4x4 g_mView		: VIEW;			//View matrix
float4x4 g_mProjection		: PROJECTION;		//Projection matrix

//--------------------------------------------------------------------------------------
// Computes position
//--------------------------------------------------------------------------------------
float4 vs_PositionOnly( float4 vPos : POSITION ) : POSITION
{
    //Check value.
    if( g_bUseWorld ) vPos = mul(vPos, g_mWorld);
    //Return result.
    return mul( mul( vPos, g_mView ), g_mProjection );
}

//--------------------------------------------------------------------------------------
// Compute color
//--------------------------------------------------------------------------------------
float4 ps_ConstantColor() : COLOR
{
    return g_Color;
}

//--------------------------------------------------------------------------------------
// Renders scene 
//--------------------------------------------------------------------------------------
technique RenderScene
{
    pass P0
    {          
        VertexShader = compile vs_2_0 vs_PositionOnly();
        PixelShader  = compile ps_2_0 ps_ConstantColor();
    }
}
