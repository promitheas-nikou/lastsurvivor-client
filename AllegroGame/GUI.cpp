#include "GUI.h"

void GUI::HandleEvent(ALLEGRO_EVENT& event)
{
	if (activeSubGUI == nullptr)
	{
		switch (event.type)
		{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			MouseButtonDown(event.mouse);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			MouseButtonUp(event.mouse);
			break;
		case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
			MouseButtonMove(event.mouse);
			break;
//		case ALLEGRO_EVENT_KEY_CHAR:
//			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			KeyDown(event.keyboard);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			KeyUp(event.keyboard);
			break;
		}
	}
	else
		activeSubGUI->HandleEvent(event);
}

void GUI::DrawGUI()
{
	if (activeSubGUI == nullptr)
		DrawThisGUI();
	else
		activeSubGUI->DrawGUI();
}
