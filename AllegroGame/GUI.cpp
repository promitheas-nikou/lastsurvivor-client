#include "GUI.h"

PlayerEntity* GUI_GLOBAL_PLAYER_OBJECT;

bool GUI::ClickRightDown(int xRel, int yRel)
{
	return false;
}

bool GUI::ClickLeftDown(int xRel, int yRel)
{
	return false;
}

bool GUI::ClickRightUp(int xRel, int yRel)
{
	return false;
}

bool GUI::ClickLeftUp(int xRel, int yRel)
{
	return false;
}

bool GUI::KeyDown(ALLEGRO_KEYBOARD_EVENT& event)
{
	return false;
}

bool GUI::KeyUp(ALLEGRO_KEYBOARD_EVENT& event)
{
	return false;
}

void GUI::SetActiveSubGUI(GUI* gui)
{
	activeSubGUI = gui;
}

bool GUI::KeyChar(ALLEGRO_KEYBOARD_EVENT& event)
{
	return false;
}

bool GUI::MouseButtonDown(ALLEGRO_MOUSE_EVENT& event)
{
	switch (event.button)
	{
	case 1:
		return ClickLeftDown(event.x, event.y);
		break;
	case 2:
		return ClickRightDown(event.x, event.y);
		break;
	}
}
bool GUI::MouseButtonUp(ALLEGRO_MOUSE_EVENT& event)
{
	switch (event.button)
	{
	case 1:
		return ClickLeftUp(event.x, event.y);
		break;
	case 2:
		return ClickRightUp(event.x, event.y);
		break;
	}
}

bool GUI::MouseButtonMove(ALLEGRO_MOUSE_EVENT& event)
{
	return false;
}

bool GUI::HandleEvent(ALLEGRO_EVENT& event)
{
	if (activeSubGUI != nullptr)
		if(activeSubGUI->HandleEvent(event))
			return true;
	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state(&state);
	if(selectedComponent!=nullptr)
		switch (event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			if(selectedComponent->KeyDown(event.keyboard))
				return true;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if(selectedComponent->KeyUp(event.keyboard))
				return true;
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			if(selectedComponent->KeyChar(event.keyboard))
				return true;
			break;
		}
	for (int i = 0; i < UIcomponents.size(); i++)
	{
		UIComponent* tmp = UIcomponents[i];

		if(tmp->ContainsPoint(state.x, state.y))
		{
			switch (event.type)
			{
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				selectedComponent = tmp;
				switch (event.mouse.button)
				{
				case 1:
					if (tmp->ClickLeftDown(event.mouse.x, event.mouse.y))
						return true;
					break;
				case 2:
					if (tmp->ClickRightDown(event.mouse.x, event.mouse.y))
						return true;
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				switch (event.mouse.button)
				{
				case 1:
					if (tmp->ClickLeftUp(event.mouse.x, event.mouse.y))
						return true;
					break;
				case 2:
					if (tmp->ClickRightUp(event.mouse.x, event.mouse.y))
						return true;
					break;
				}
				break;
			case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
				if (tmp->Hover(state.x, state.y))
					return true;
				break;
				//		case ALLEGRO_EVENT_KEY_CHAR:
				//			break;
			case ALLEGRO_EVENT_KEY_DOWN:
					return this->KeyDown(event.keyboard);
				break;
			case ALLEGRO_EVENT_KEY_UP:
					return this->KeyUp(event.keyboard);
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
					return this->KeyChar(event.keyboard);
				break;
			}
		}
	}
	switch (event.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		if(this->MouseButtonDown(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		if(this->MouseButtonUp(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_MOUSE_AXES: //MOUSE MOVED
		if(this->MouseButtonMove(event.mouse))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		if(IsTyping()&& this->KeyChar(event.keyboard))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		if (!IsTyping() && this->KeyDown(event.keyboard))
			return true;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		if (!IsTyping() && this->KeyUp(event.keyboard))
			return true;
		break;
	}
	return false;
}


PlayerEntity* GUI::GetPlayer()
{
	return GUI_GLOBAL_PLAYER_OBJECT;
}

void GUI::PreDrawThisGUI()
{}

void GUI::PostDrawThisGUI()
{}

UIComponent* GUI::GetSelectedComponent()
{
	return selectedComponent;
}

bool GUI::IsTyping() const
{
	return typing;
}

void GUI::ToggleTyping()
{
	typing = !typing;
}

void GUI::DrawGUI()
{
	this->PreDrawThisGUI();

	ALLEGRO_TRANSFORM temp_gui_transform = *al_get_current_transform();
	for(int p=1;p<=3;p++)
		for (int i = 0; i < UIcomponents.size(); i++)
		{
			UIComponent* tmp = UIcomponents[i];
			al_translate_transform(&temp_gui_transform, tmp->GetXpos(), tmp->GetYpos());
			al_use_transform(&temp_gui_transform);
			UIcomponents[i]->Draw(p);
			al_translate_transform(&temp_gui_transform, -tmp->GetXpos(), -tmp->GetYpos());
		}
	al_use_transform(&temp_gui_transform);
	if (activeSubGUI != nullptr)
		activeSubGUI->DrawGUI();
	this->PostDrawThisGUI();
}
