#include "Shader.h"
#include <cstdio>

Shader::Shader(int id): ID(id)
{
	shader = al_create_shader(ALLEGRO_SHADER_GLSL);
	al_attach_shader_source(shader, ALLEGRO_VERTEX_SHADER, al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_VERTEX_SHADER));
	al_attach_shader_source(shader, ALLEGRO_PIXEL_SHADER, al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER));
	al_build_shader(shader);
	printf("COMPILING SHADER #%d:\n\tSUCCESSFULLY COMPILED DEFAULT SHADER #%d\n", ID, ID);
}

Shader::Shader(int id, const char* vert_filename, const char* frag_filename): ID(id)
{
	shader = al_create_shader(ALLEGRO_SHADER_GLSL);
	
	printf("COMPILING SHADER #%d:\n", ID);

	if (al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vert_filename))
		printf("\tSUCCESSFULLY ATTACHED VERTEX SHADER SOURCE FILE: \"%s\"\n", vert_filename);
	else
	{
		printf("\tFAILED TO ATTACH VERTEX SHADER!!!\nERROR: \"%s\"\n", al_get_shader_log(shader));
		return;
	}



	if (al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, frag_filename))
		printf("\tSUCCESSFULLY ATTACHED FRAGMENT SHADER SOURCE FILE: %s\n", frag_filename);
	else
	{
		printf("\tFAILED TO ATTACH FRAGMENT SHADER!!!\nERROR: %s\n", al_get_shader_log(shader));
		return;
	}



	if (al_build_shader(shader))
		printf("\tSUCCESSFULLY COMPILED SHADER #%d\n", ID);
	else
	{
		printf("\tFAILED TO COMPILE SHADER!!!\nERROR: %s\n", al_get_shader_log(shader));
		return;
	}
}

void Shader::Delete()
{
	al_destroy_shader(shader);
}

void Shader::Use()
{
	al_use_shader(shader);
}
