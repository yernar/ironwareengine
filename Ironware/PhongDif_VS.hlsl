#include "CommonTransforms.hlsli"
#include "CommonShadowOps_VO.hlsli"

struct VSOut
{
    float3 viewPos : Position;
    float3 viewN : Normal;
    float2 tex : TexCoord;
    float4 shadowHomoPos : ShadowPosition;
    float4 pos : SV_Position;
};

VSOut main( float3 pos : Position, float3 n : Normal, float2 tex : TexCoord )
{
    float4 pos4 = float4( pos, 1.f );
    
    VSOut vso;
    vso.viewPos = (float3)mul( pos4, modelView );
    vso.viewN = mul( n, (float3x3)modelView );
    vso.tex = tex;
    vso.pos = mul( pos4, modelViewProjection );
    vso.shadowHomoPos = to_shadow_homo_space( pos, model );
    
    return vso;
}