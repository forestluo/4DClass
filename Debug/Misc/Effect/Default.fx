//--------------------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// Structures
//-------------------------------------------------------------------------------------

struct SasCamera
{
    float4x4 WorldToView;	   
    float4x4 Projection;    
    float2 NearFarClipping; 
    float3 Position;
};

struct SasAmbientLight
{
    float3 Color;         // default: {0, 0, 0}
};

struct SasDirectionalLight
{
    float3 Color;         // default: {0, 0, 0}
    float3 Direction;     // default: {0, 0, 0}
};

struct SasPointLight
{
    float3 Color;         // default: {0, 0, 0}
    float3 Position;      // default: {0, 0, 0}
    float  Range;         // default: 0
};

struct SasSpotLight
{
    float3 Color;         // default: {0, 0, 0}
    float3 Position;      // default: {0, 0, 0}
    float  Direction;     // default: {0, 0, 0}
    float  Range;         // default: 0
    float  Theta;         // default: 0
    float  Phi;           // default: 0
};

//--------------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------------
SasAmbientLight AmbientLight =
{
	//Color
	float3(0.01f,0.01f,0.01f)
};

SasDirectionalLight DirectionalLight =
{
	//Color
	float3(0.10f,0.10f,0.10f),
	//Direction
	float3(0.0f,0.0f,10.0f),
};

float4x4 World : WORLD;         
float4x4 View : VIEW;
float4x4 Projection : PROJECTION;


float4 MaterialDiffuse : MATERIALDIFFUSE;
float4 MaterialAmbient : MATERIALAMBIENT;
float4 MaterialEmissive : MATERIALEMISSIVE;
texture MaterialTexture : MATERIALTEXTURE;
bool IsMaterialTextured;


sampler MaterialTextureSampler = sampler_state
{ 
    Texture = (MaterialTexture);
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


//--------------------------------------------------------------------------------------
// VertexShader I/O
//--------------------------------------------------------------------------------------
struct VSInput
{
    float4 Position : POSITION; 
    float3 Normal : NORMAL;
    float2 TexCoords : TEXCOORD0;
};

struct VSOutput
{
    float4 TransformedPosition : POSITION;
    float3 Diffuse : COLOR0;    
    float2 TexCoords : TEXCOORD0; 
};


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
VSOutput VSStandard( VSInput input )
{
    VSOutput output;
    
    float4 worldPosition = mul(input.Position, (float4x4)World);
    float3 worldNormal = mul(input.Normal, (float3x3)World);
    
    output.TransformedPosition = mul(worldPosition, mul(View, Projection));
    output.TexCoords = input.TexCoords;
    output.Diffuse = MaterialEmissive + (MaterialAmbient * AmbientLight.Color); 
    output.Diffuse += (MaterialDiffuse * DirectionalLight.Color *  max(0, dot(worldNormal, -DirectionalLight.Direction)));
    
    return output;    
}



//--------------------------------------------------------------------------------------
// PixelShader I/O
//--------------------------------------------------------------------------------------
struct PSOutput
{
    float4 Color : COLOR0;  // Pixel color    
};


PSOutput PS( VSOutput input ) 
{ 
    PSOutput output;

    if(IsMaterialTextured)
        input.Diffuse *= tex2D(MaterialTextureSampler, input.TexCoords); 
   
    output.Color = float4(input.Diffuse, 1);
    
    return output;
}


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique Standard
{
    pass P0
    {   
        //CullMode = None;
        
        VertexShader = compile vs_2_0 VSStandard();
        PixelShader  = compile ps_2_0 PS(); 
    }
}
