#version 400 core

const int MAX_LIGHTS_NUM = 100;

attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
uniform float input_scalex;
uniform float input_scaley;
uniform int LIGHTS_NUM;
uniform vec3 LIGHTS_POS[MAX_LIGHTS_NUM];
uniform float LIGHTS_BRIGHT[MAX_LIGHTS_NUM];
uniform vec4 ambientLightColor;
out vec2 varying_texcoord;

void main()
{
	varying_texcoord = al_texcoord;
    vec4 tmp_pos = al_projview_matrix * al_pos;

    gl_Position = vec4(tmp_pos.x,tmp_pos.y,tmp_pos.z,tmp_pos.w);
}