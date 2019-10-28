#version 330 core

const float dencity = 0.8;
const float opacity = 0.3;
const float opacityNoise = 0.2;
const float flickering = 0.03;

const vec2 resolution = vec2(800, 600);

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D renderedTexture;
uniform float in_time;

//psudo random
float rand(vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233))) * 43758.5453123);
}

void main() {
    vec3 color = texture2D(renderedTexture, textureCoordinate).rgb;
    color = clamp(color, vec3(0.05), vec3(1));

    float count = resolution.y*dencity;
    vec2 sl = vec2(sin(textureCoordinate.y*count), cos(textureCoordinate.y*count));
    vec3 scanlines = vec3(sl.x, sl.y, sl.x);

    color += color * scanlines * opacity;
    color += color * vec3(rand(textureCoordinate*in_time)) * opacityNoise;
    color += color * sin(110.0*in_time) * flickering;

    fragColor = vec4(color, 1);
}
