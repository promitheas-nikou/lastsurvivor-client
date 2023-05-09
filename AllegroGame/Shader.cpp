#include "Shader.h"
#include <cstdio>
#include "Logging.h"
#include "Config.h"
#include "Graphics.h"

Shader::Shader(std::string id): ID(id)
{
	shader = al_create_shader(ALLEGRO_SHADER_GLSL);
	FILE* file = fopen("default_shader.vert", "w");
	const char* data = al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_VERTEX_SHADER);
	fputs(data, file);
	fflush(file);
	fclose(file);
	file = NULL;
	file = fopen("default_shader.frag", "w");
	
	data = al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER);
	fputs(data, file);
	fflush(file);
	fclose(file);
	file = NULL;
	lsg_write_to_session_log(INFO, "DUMPING DEFAULT SHADER SOURCES TO default_shader.vert AND default_shader.frag...");
	al_attach_shader_source(shader, ALLEGRO_VERTEX_SHADER, al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_VERTEX_SHADER));
	al_attach_shader_source(shader, ALLEGRO_PIXEL_SHADER, al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER));
	al_build_shader(shader);
	lsg_write_to_session_log(INFO, "COMPILING DEFAULT SHADER \"%s\":" , ID.c_str());
	lsg_write_to_session_log(INFO, "\tSUCCESSFULLY COMPILED DEFAULT SHADER \"%s\"", ID.c_str());
}

Shader::Shader(std::string id, const char* vert_filename, const char* frag_filename): ID(id)
{
	shader = al_create_shader(ALLEGRO_SHADER_GLSL);
	
	lsg_write_to_session_log(INFO, "COMPILING SHADER \"%s\":", ID.c_str());

	if (al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vert_filename))
		lsg_write_to_session_log(INFO, "\tSUCCESSFULLY ATTACHED VERTEX SHADER SOURCE FILE: \"%s\"", vert_filename);
	else
	{
		lsg_write_to_session_log(ERROR, "\tFAILED TO ATTACH VERTEX SHADER!!!\nERROR: \"%s\"", al_get_shader_log(shader));
		return;
	}



	if (al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, frag_filename))
		lsg_write_to_session_log(INFO, "\tSUCCESSFULLY ATTACHED FRAGMENT SHADER SOURCE FILE: \"%s\"", frag_filename);
	else
	{
		lsg_write_to_session_log(ERROR, "\tFAILED TO ATTACH FRAGMENT SHADER!!!\nERROR: \"%s\"", al_get_shader_log(shader));
		return;
	}



	if (al_build_shader(shader))
		lsg_write_to_session_log(INFO, "\tSUCCESSFULLY COMPILED SHADER \"%s\"", ID.c_str());
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
	al_set_shader_float("input_scalex", SCREEN_X_SCALE);
	al_set_shader_float("input_scaley", SCREEN_Y_SCALE);
}
