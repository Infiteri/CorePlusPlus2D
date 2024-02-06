#version 330 core

in vec2 vUV;

uniform vec4 uColor;
uniform sampler2D uColorTexture;

out vec4 outColor;

void main() {
    outColor = texture2D(uColorTexture, vUV);
}
