#version 330 core

uniform sampler2D textBumpyMetal; // ‐> unidades de textura (int)
uniform sampler2D textBeachStones; // tipo sampler2D para texturas 2D
uniform sampler2D textCorrosion; // ‐> unidades de textura (int)

// uniform float BF; // blending factor
// uniform float intLuzAmb; // luz ambiente blanca

in vec2 vUv0; // out del vertex shader

out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorStones = vec3(texture(textBeachStones, vUv0)); // acceso a téxel
    vec3 colorMetal = vec3(texture(textBumpyMetal, vUv0)); // configuración!
    vec3 colorCorrosion = vec3(texture(textCorrosion, vUv0)); // configuración!

    if (colorCorrosion.r <= 0.6)
    {
        if(gl_FrontFacing)
            fFragColor = vec4(colorMetal, 1.0);
        else
            fFragColor = vec4(colorStones, 1.0);
    }
    else                               
        discard;
}