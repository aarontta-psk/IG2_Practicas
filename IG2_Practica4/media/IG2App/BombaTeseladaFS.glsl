#version 330 core

uniform sampler2D textChecker; // ‐> unidades de textura (int)
uniform sampler2D textSpace; // tipo sampler2D para texturas 2D
uniform sampler2D textMetal; // ‐> unidades de textura (int)

// uniform float BF; // blending factor
// uniform float intLuzAmb; // luz ambiente blanca

in vec2 vUv0; // out del vertex shader

out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorSpace = vec3(texture(textSpace, vUv0)); // acceso a téxel
    vec3 colorMetal = vec3(texture(textMetal, vUv0)); // configuración!
    vec3 colorChecker = vec3(texture(textChecker, vUv0)); // configuración!

    // vec3 color = mix(colorL, colorM, BF) * intLuzAmb;
    // mix ‐> (1‐BF).colorL + BF.colorM

    if (colorChecker == vec3(1, 1, 1)) // WHITE
        fFragColor = vec4(colorMetal, 1.0); // out
    else                               // BLACK or GREY
        fFragColor = vec4(colorSpace, 1.0); // out
}