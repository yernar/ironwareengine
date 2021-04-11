Texture2D tex;
Texture2D specTex;

SamplerState splr;

// for global dynamic light
cbuffer LightCBuf
{
    float3 lightPos;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

float4 main( float3 viewPos : Position, float3 n : Normal, float2 tc : TexCoord ) : SV_Target
{
    // fragment to light vector data
    const float3 vToL = lightPos - viewPos;
    const float distToL = length( vToL );
    const float3 dirToL = vToL / distToL;
	// attenuation
    const float att = attConst + attLin * distToL + attQuad * ( distToL * distToL );
    const float luminosity = 1.f / att;
	// diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * luminosity * max( 0.f, dot( dirToL, n ) ) * (float3)tex.Sample( splr, tc );
    // reflected light vector
    const float3 w = n * dot( vToL, n );
    const float3 r = w * 2.f - vToL;
	// calculate specular intensity based on angle between viewing vector and reflection vector, narrow with power function
    // multiplying by luminosity because we are using point light here
    float4 sampledSpec = specTex.Sample( splr, tc );
    float3 specularColor = sampledSpec.rgb;
    float specularPower = sampledSpec.a;
    // * ( diffuseColor * diffuseIntensity ) 
    const float3 specular = luminosity * specularColor * pow( max( 0.f, dot( normalize( -r ), normalize( viewPos ) ) ), specularPower );
	// final color
    return float4( saturate( ( diffuse + ambient + specular ) ), 1.f ) * tex.Sample( splr, tc );
}