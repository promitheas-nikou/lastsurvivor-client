#include "SimpleTextInputUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "ResourceLoader.h"

bool SimpleTextInputUIComponent::KeyChar(ALLEGRO_KEYBOARD_EVENT& evt)
{
    if (evt.keycode == ALLEGRO_KEY_BACKSPACE)
    {
        if (edit_text.size())
            edit_text.pop_back();
    }
    else
    {
        if (evt.unichar > 0)
            edit_text.push_back(evt.unichar);
    }
    return true;
}

void SimpleTextInputUIComponent::Draw(int plane)
{
    if (plane != 1)
        return;
    al_draw_filled_rectangle(0, 0, GetWidth(), GetHeight(), background_color);
    if(flags==ALLEGRO_ALIGN_LEFT)
        al_draw_textf(loaded_fonts["default"][30], text_color, 0, GetHeight() / 2 - 15, flags, "%s%s", pre_text.c_str(), edit_text.c_str());
    else if (flags == ALLEGRO_ALIGN_CENTER)
        al_draw_textf(loaded_fonts["default"][30], text_color, GetWidth() / 2, GetHeight() / 2 - 15, flags, "%s%s", pre_text.c_str(), edit_text.c_str());
    else if (flags == ALLEGRO_ALIGN_RIGHT)
        al_draw_textf(loaded_fonts["default"][30], text_color, GetWidth(), GetHeight() / 2 - 15, flags, "%s%s", pre_text.c_str(), edit_text.c_str());
}

void SimpleTextInputUIComponent::ClearTextBuffer()
{
    edit_text.clear();
}

std::string SimpleTextInputUIComponent::GetTextBuffer()
{
    return edit_text;
}

SimpleTextInputUIComponent::SimpleTextInputUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string pre_txt, std::string edt_txt, int flags) : UIComponent(x, y, w, h), background_color{ bc }, text_color{ tc }, pre_text{ pre_txt }, edit_text{ edt_txt }, flags{ flags }
{}
