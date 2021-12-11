#version 330 core

uniform sampler2D textLightmap; // tipo sampler2D para texturas 2D
uniform sampler2D textSpace; // ‐> unidades de textura (int)

// uniform float BF; // blending factor
// uniform float intLuzAmb; // luz ambiente blanca

in vec2 vUv0; // out del vertex shader

out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorLightmap = vec3(texture(textLightmap, vUv0)); // configuración!
    vec3 colorSpace = vec3(texture(textSpace, vUv0)); // acceso a téxel

    fFragColor = vec4(colorSpace * colorLightmap, 1.0);
    //fFragColor = vec4(mod(colorSpace, colorLightmap), 1.0); // modulo para el color
}