#pragma once

#include <allegro5/allegro.h>

class Shader
{
public:
	
	ALLEGRO_SHADER* shader;
	const int ID;

	Shader(int id);

	Shader(int id, const char* vert_filename, const char* frag_filename);

	void Delete();

	void Use();
};

