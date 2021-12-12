#version 330 core

uniform sampler2D textBumpyMetal; // ‐> unidades de textura (int)
uniform sampler2D textBeachStones; // tipo sampler2D para texturas 2D
uniform sampler2D textCorrosion; // ‐> unidades de textura (int)

// uniform vec3 lightAmbient; // intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

// uniform vec4 materialDiffuse;

uniform vec3 ocreSiena;
uniform vec3 azulCeruleo;

// uniform float BF; // blending factor
// uniform float intLuzAmb; // luz ambiente blanca

in vec2 vUv0; // out del vertex shader
in vec3 vCamNormal; // coordenadas de la normal en camera space
// in vec4 vCamVertex; // coordenadas del vértice en camera space

out vec4 fFragColor; // out del fragment shader

void main() {
    vec3 colorCorrosion = vec3(texture(textCorrosion, vUv0)); // configuración!

    if(colorCorrosion.r > 0.6)
        discard;

    if(gl_FrontFacing) {
        vec3 colorMetal = vec3(texture(textBumpyMetal, vUv0)); // configuración!
        colorMetal *= ocreSiena;

        vec3 lightDir = normalize(vec3(lightPosition));
        float diff = max(dot(vCamNormal, lightDir), 0.0); // positive normal
        vec3 diffuse = vec3(lightDiffuse) * diff;

        fFragColor = vec4(colorMetal * diffuse, 1.0);
    } 
    else {
        vec3 colorStones = vec3(texture(textBeachStones, vUv0)); // acceso a téxel
        colorStones *= azulCeruleo;
        
        vec3 lightDir = normalize(vec3(lightPosition));
        float diff = max(dot(-vCamNormal, lightDir), 0.0); // negative normal
        vec3 diffuse = vec3(lightDiffuse) * diff;

        fFragColor = vec4(colorStones * diffuse, 1.0);
    }
}