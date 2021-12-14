#version 330 core

uniform sampler2D textBumpyMetal; // ‐> unidades de textura (int)
uniform sampler2D textBeachStones; // tipo sampler2D para texturas 2D
uniform sampler2D textCorrosion; // ‐> unidades de textura (int)

uniform vec3 lightAmbient; // intensidades de la luz
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

uniform vec4 materialDiffuse;

uniform vec3 ocreSiena;
uniform vec3 azulCeruleo;

in vec2 vUv0; // out del vertex shader
in vec3 vGlobalNormal; // coordenadas de la normal en camera space
in vec4 vGlobalVertex; // coordenadas del vértice en camera space

out vec4 fFragColor; // out del fragment shader

float diff(vec3 vVertex, vec3 vNormal) {
    vec3 lightDir = lightPosition.xyz; // directional light ?
    if(lightPosition.w == 1) // positional light ?
        lightDir = lightPosition.xyz - vVertex;
        
    return max(dot(vNormal, normalize(lightDir)), 0.0);
}

void main() {
    vec3 colorCorrosion = vec3(texture(textCorrosion, vUv0)); // configuración!

    if(colorCorrosion.r > 0.6)
        discard;

    vec3 ambient = lightAmbient * materialDiffuse.rgb;

    if(gl_FrontFacing) {
        vec3 colorMetal = vec3(texture(textBumpyMetal, vUv0)); // configuración!
        colorMetal *= (ocreSiena + ambient);

        float diff = diff(vec3(vGlobalVertex), vGlobalNormal); // positive normal
        vec3 diffuse = vec3(lightDiffuse) * diff * materialDiffuse.rgb;

        fFragColor = vec4(colorMetal * diffuse, 1.0);
    } else {
        vec3 colorStones = vec3(texture(textBeachStones, vUv0)); // acceso a téxel
        colorStones *= (azulCeruleo  + ambient);

        float diff = diff(vec3(vGlobalVertex), -vGlobalNormal); // negative normal
        vec3 diffuse = vec3(lightDiffuse) * diff * materialDiffuse.rgb;

        fFragColor = vec4(colorStones * diffuse, 1.0);
    }
}