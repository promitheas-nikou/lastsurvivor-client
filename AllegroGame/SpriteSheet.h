#pragma once
#include <allegro5/allegro.h>

class SpriteSheet
{
private:
	ALLEGRO_BITMAP* bmp;
	int sw, sh;
	int row, col;
protected:
	void SetTargetBitmap(ALLEGRO_BITMAP* new_bmp);
	ALLEGRO_BITMAP* GetTargetBitmap() const;
public:
	SpriteSheet(ALLEGRO_BITMAP* bitmap, int width, int height);

	void Draw(int x, int y, int width, int height, float r, int texID) const;
	void Draw(int x, int y, int width, int height, int texID) const;
	void Draw(int x, int y, int texID) const;

};

