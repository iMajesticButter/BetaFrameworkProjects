#version 330 core

const float WARP_FACTOR = 0.3;
const float SCALE_FACTOR = 1.2;

in vec2 textureCoordinate;

out vec4 fragColor;

uniform sampler2D renderedTexture;

vec2 applyWarp(vec2 coord) {
    //remap coordinate from (0 to 1) to (-1 to 1)
    vec2 vector = (coord-0.5)*2;
    float magSquared = vector.x*vector.x + vector.y*vector.y;

    vector += vector * WARP_FACTOR * magSquared;
    vector /= SCALE_FACTOR;

    //remap coordinate from (-1 to 1) to (0 to 1)
    return (vector+1)*0.5;
}

vec4 getClampedColor(vec2 coord) {
    float valid = step(0, coord.x)  *    step(0, coord.y)
             * (1-step(1, coord.x)) * (1-step(1, coord.y));

    return texture(renderedTexture, coord) * valid;
}

void main() {
    vec2 warped = applyWarp(textureCoordinate);
    vec4 color = getClampedColor(warped);
    fragColor = vec4(color.rgb, 1);
}
