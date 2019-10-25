//------------------------------------------------------------------------------
//
// File Name:	postEffectScanline.frag
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D renderedTexture;

void main()
{
    //convert to polar coordinates
    vec2 vec = (textureCoordinate - 0.5) * 2;
    vec += vec * 0.25 * (vec.x*vec.x + vec.y*vec.y);

    //and back
    vec2 uv = (vec + 1) / 2;
    float mul = (1-step(1, uv.x)) * (1-step(1,uv.y));
    mul *= (step(0, uv.x)) * (step(0,uv.y));
    float val = clamp((sin(uv.y*600) + 1) / 2, 0.4, 1);
    fragColor = vec4(texture2D(renderedTexture, uv).rgb * val, 1) * mul;
}
