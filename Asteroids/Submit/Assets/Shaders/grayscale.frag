//------------------------------------------------------------------------------
//
// File Name:	grayscale.frag
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

float avgCol(vec4 color) {
    return (color.r + color.g + color.b) / 3;
}

void main() {
    fragColor = vec4(vec3(avgCol(texture2D(renderedTexture, textureCoordinate))), 1.0);
}
