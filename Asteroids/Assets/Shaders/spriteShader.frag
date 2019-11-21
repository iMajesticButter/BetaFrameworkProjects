#version 330 core

uniform vec4 blendColor;
uniform vec4 tintColor;
uniform sampler2D diffuse;
uniform vec2 uvOffset;
uniform vec2 uvStride;

in vec4 vertexColor;
in vec2 textureCoordinate;

out vec4 fragColor;

void main()
{
	vec4 texel = texture2D(diffuse, textureCoordinate);

	// Don't bother drawing if pixel is mostly transparent
	//if(texel.a < 0.4)
	//	discard;

	float lowerBound = step(uvOffset.x, textureCoordinate.x) * step(uvOffset.y, textureCoordinate.y);
	float upperBound = (1-step(uvOffset.x + uvStride.x, textureCoordinate.x)) * (1-step(uvOffset.y + uvStride.y, textureCoordinate.y));
	float bounds = lowerBound * upperBound;

	fragColor = texel * vertexColor * blendColor * tintColor * bounds;
}
