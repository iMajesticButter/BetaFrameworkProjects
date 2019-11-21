//------------------------------------------------------------------------------
//
// File Name:	chromaticaberration.frag
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

vec2 redOffset = vec2(0.008, 0.008);
vec2 greenOffset = vec2(-0.008, 0.008);
vec2 blueOffset = vec2(0, -0.008);

void main() {
	float val = distance(vec2(0.5, 0.5), textureCoordinate);

    vec4 redVal = texture2D(renderedTexture, textureCoordinate + clamp(redOffset * val, 0, 1));
	vec4 greenVal = texture2D(renderedTexture, textureCoordinate + clamp(greenOffset * val, 0, 1));
	vec4 blueVal = texture2D(renderedTexture, textureCoordinate + clamp(blueOffset * val, 0, 1));

	fragColor = vec4(redVal.r, greenVal.g, blueVal.b, 1.0);
}
