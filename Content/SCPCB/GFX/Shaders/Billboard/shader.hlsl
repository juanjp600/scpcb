Texture2D diff;
SamplerState smp;

cbuffer cbMatrices {
    matrix projectionMatrix;
    matrix viewMatrix;
    matrix modelMatrix;
};

cbuffer cbFragment {
    float4 spriteColor;
};

struct VS_INPUT {
    float4 position  : POSITION0;
    float2 texCoords : TEXCOORD0;
};

struct PS_INPUT {
    float4 position  : SV_POSITION;
    float2 texCoords : TEXCOORD0;
};

struct PS_OUTPUT {
    float4 color : SV_Target0;
};

PS_INPUT VS(VS_INPUT input) {
    PS_INPUT output = (PS_INPUT)0;

    output.position = mul(input.position,modelMatrix);
    output.position = mul(output.position,viewMatrix);
    output.position = mul(output.position,projectionMatrix);
    output.texCoords = input.texCoords;
    return output;
}

PS_OUTPUT PS(PS_INPUT input) {
    PS_OUTPUT output = (PS_OUTPUT)0;
    float4 diffColor = diff.Sample(smp, input.texCoords);
    output.color = spriteColor * diffColor;
    return output;
}