#version 400 core

uniform sampler2D al_tex;
in vec2 varying_texcoord;
	
void main()
{
   vec4 c1 = texture2D(al_tex, varying_texcoord);
   gl_FragColor = c1;
}