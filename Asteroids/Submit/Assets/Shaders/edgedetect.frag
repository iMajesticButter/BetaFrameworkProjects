//------------------------------------------------------------------------------
//
// File Name:	edgedetect.frag
// Author(s):	Brandon Wolenetz
// Project:		BetaFramework Project 1: Asteroids
// Course:		WANIC VGP2 2019-2020
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#version 330 core

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D renderedTexture;

float sigmoid(float a, float f) {
	return 1.0/(1.0+exp(-f*a));
}

void main() {
    vec4 color = texture2D(renderedTexture, textureCoordinate);

    float edgeStrength = length(fwidth(color));
    edgeStrength = sigmoid(edgeStrength - 0.2, 32.0);
    fragColor = color * vec4(vec3(edgeStrength), 1.0);

    fragColor += color/2;
}
