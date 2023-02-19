#include "SimpleCallbackTextDrawUIComponent.h"
#include "ResourceLoader.h"

void SimpleCallbackTextDrawUIComponent::Draw()
{
	int s = sizeCallback();
	al_draw_multiline_text(game_GetFont("default", s), colorCallback(), 0, 0, GetWidth(), s, 0, textCallback().c_str());
}
