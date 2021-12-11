#version 400 core

attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
out vec2 varying_texcoord;

void main()
{
   varying_texcoord = al_texcoord;
   gl_Position = al_projview_matrix * al_pos;
}