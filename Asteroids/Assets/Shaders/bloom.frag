//------------------------------------------------------------------------------
//
// File Name:	bloom.frag
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
uniform vec2 resolution;

float dist = 40;
float strength = 0.2;

vec3 getsample(float offsetx, float offsety) {
	return texture2D(renderedTexture, textureCoordinate + vec2(offsetx, offsety) / resolution).rgb;
}

void main() {

	vec3 color = vec3(0,0,0);

	for(float x = -dist; x < dist; x += dist / 10.0) {
		for(float y = -dist; y < dist; y += dist / 10.0) {
			color += getsample(x, y);
		}
	}

	color /= 100;

	color = (color * strength) + texture2D(renderedTexture, textureCoordinate).rgb;

	fragColor = vec4(color, 1.0);
}
