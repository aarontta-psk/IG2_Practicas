#version 330 core

in vec4 vertex;                     // atributos de los vertices a procesar
in vec3 normal;
in vec2 uv0;

uniform mat4 modelViewProjMat;      // matriz de transformacion
uniform mat4 normalMat;             // matriz inversa (normales)
// uniform mat4 modelViewMat;      // matriz de transformacion

out vec2 vUv0;                 // out del vertex shader
out vec3 vCamNormal;
// out vec4 vCamVertex; 

void main() {
    vUv0 = uv0;
    vCamNormal = normalize(mat3(normalMat) * normal);
    // vCamVertex = vec3(modelViewMat * vertex);

    gl_Position = modelViewProjMat * vertex;
}