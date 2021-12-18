#pragma once
#include "Entity.h"
#include "GUI.h"
class PlayerEntity :
    public Entity,
	public GUI
{
public:
	void DrawGUI() final;
	void Draw() final;
	friend WorldChunk;
	friend World;
	friend int main();
};

