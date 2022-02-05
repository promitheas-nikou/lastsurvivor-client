#pragma once

#include <allegro5/allegro.h>
#include <string>

class Shader
{
public:
	
	ALLEGRO_SHADER* shader;
	const std::string ID;

	Shader(std::string id);

	Shader(std::string id, const char* vert_filename, const char* frag_filename);

	void Delete();

	void Use();
};

