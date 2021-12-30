#version 330 core

in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0; // coordenadas de textura 0
uniform mat4 modelViewProjMat; // constante de programa
uniform float sintime; // factor de escala

out vec2 vUv0; // out del vertex shader
out vec2 vUv1; // out del vertex shader

void main() {
    vUv0 = uv0; // se pasan las coordenadas de textura

    //Como st está entre -1 y 1, y queremos valores entre 1.5 y 1, tenemos estas ecuaciones
    // -a + b = 1.5
    //  a + b = 1
    //  a = 0.25, b = 1.25

    float ZF = sintime * 0.25 + 1.25;
    vUv1.s = (uv0.s - 0.5) * ZF + 0.5; 
    vUv1.t = (uv0.t - 0.5) * ZF + 0.5;

    gl_Position = modelViewProjMat * vertex; //obligatorio
                                             // (Clipping coordinates)
}