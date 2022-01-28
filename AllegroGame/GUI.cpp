#include "GUI.h"

void GUI::ClickRightDown(int xRel, int yRel)
{
}

void GUI::ClickLeftDown(int xRel, int yRel)
{
}

void GUI::ClickRightUp(int xRel, int yRel)
{
}

void GUI::ClickLeftUp(int xRel, int yRel)
{
}

void GUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
}

void GUI::KeyUp(ALLEGRO_KEYBOARD_EVENT& event)
{
}

void GUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	switch (event.button)
	{
	case 1:
		ClickLeftDown(event.x, event.y);
		break;
	case 2:
		ClickRightDown(event.x, event.y);
		break;
	}
}
void GUI::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{
	switch (event.button)
	{
	case 1:
		ClickLeftUp(event.x, event.y);
		break;
	case 2:
		ClickRightUp(event.x, event.y);
		break;
	}
}

void GUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{}

void GUI::HandleEvent(ALLEGRO_EVENT& event)
{
	for (int i = 0; i < UIcomponents.size(); i++)
	{
		UIComponent* tmp = UIcomponents[i];
		ALLEGRO_MOUSE_STATE state;
		al_get_mouse_state(&state);
		if(tmp->ContainsPoint(state.x, state.y))
		{
			switch (event.type)
			{
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				switch (event.mouse.button)
				{
				case 1:
					tmp->ClickLeftDown(event.mouse.x, event.mouse.y);
					break;
				case 2:
					tmp->ClickRightDown(event.mouse.x, event.mouse.y);
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				switch (event.mouse.button)
				{
				case 1:
					tmp->ClickLeftUp(event.mouse.x, event.mouse.y);
					break;
				case 2:
					tmp->ClickRightUp(event.mouse.x, event.mouse.y);
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
				tmp->Hover(state.x, state.y);
				break;
				//		case ALLEGRO_EVENT_KEY_CHAR:
				//			break;
			case ALLEGRO_EVENT_KEY_DOWN:
				tmp->KeyDown(event.keyboard.keycode);
				break;
			case ALLEGRO_EVENT_KEY_UP:
				tmp->KeyUp(event.keyboard.keycode);
				break;
			}
		}
	}
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
	if(activeSubGUI!=nullptr)
		activeSubGUI->HandleEvent(event);
}


void GUI::DrawGUI()
{
	DrawThisGUI();
	ALLEGRO_TRANSFORM temp_gui_transform = *al_get_current_transform();
	for (int i = 0; i < UIcomponents.size(); i++)
	{
		UIComponent* tmp = UIcomponents[i];
		al_translate_transform(&temp_gui_transform, tmp->GetXpos(), tmp->GetYpos());
		al_use_transform(&temp_gui_transform);
		UIcomponents[i]->Draw();
		al_translate_transform(&temp_gui_transform, -tmp->GetXpos(), -tmp->GetYpos());
	}
	al_use_transform(&temp_gui_transform);
	if (activeSubGUI != nullptr)
		activeSubGUI->DrawGUI();
}
