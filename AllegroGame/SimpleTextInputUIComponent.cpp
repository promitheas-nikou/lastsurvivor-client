#include "SimpleTextInputUIComponent.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "ResourceLoader.h"

bool SimpleTextInputUIComponent::KeyChar(ALLEGRO_KEYBOARD_EVENT& evt)
{
    if (alert)
    {
        edit_text.clear();
        alert = false;
    }
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
    if (alert)
    {
        al_draw_filled_rectangle(0, 0, GetWidth(), GetHeight(), alert_background_color);
        if (flags == ALLEGRO_ALIGN_LEFT)
            al_draw_textf(game_GetFont("default", 30), alert_text_color, 0, GetHeight() / 2 - 15, flags, "%s", edit_text.c_str());
        else if (flags == ALLEGRO_ALIGN_CENTER)
            al_draw_textf(game_GetFont("default", 30), alert_text_color, GetWidth() / 2, GetHeight() / 2 - 15, flags, "%s", edit_text.c_str());
        else if (flags == ALLEGRO_ALIGN_RIGHT)
            al_draw_textf(game_GetFont("default", 30), alert_text_color, GetWidth(), GetHeight() / 2 - 15, flags, "%s", edit_text.c_str());
    }
    else
    {
        al_draw_filled_rectangle(0, 0, GetWidth(), GetHeight(), background_color);
        if (flags == ALLEGRO_ALIGN_LEFT)
            al_draw_textf(game_GetFont("default", 30), text_color, 0, GetHeight() / 2 - 15, flags, "%s%s%s", pre_text.c_str(), edit_text.c_str(), post_text.c_str());
        else if (flags == ALLEGRO_ALIGN_CENTER)
            al_draw_textf(game_GetFont("default", 30), text_color, GetWidth() / 2, GetHeight() / 2 - 15, flags, "%s%s%s", pre_text.c_str(), edit_text.c_str(), post_text.c_str());
        else if (flags == ALLEGRO_ALIGN_RIGHT)
            al_draw_textf(game_GetFont("default", 30), text_color, GetWidth(), GetHeight() / 2 - 15, flags, "%s%s%s", pre_text.c_str(), edit_text.c_str(), post_text.c_str());
    }
}

void SimpleTextInputUIComponent::SetAlert(std::string temp_string, ALLEGRO_COLOR text_color, ALLEGRO_COLOR back_color)
{
    edit_text = temp_string;
    alert_text_color = text_color;
    alert_background_color = back_color;
    alert = true;
}

void SimpleTextInputUIComponent::ClearTextBuffer()
{
    edit_text.clear();
}

std::string SimpleTextInputUIComponent::GetTextBuffer()
{
    return edit_text;
}

void SimpleTextInputUIComponent::SetTextBuffer(std::string s)
{
    edit_text = s;
}

SimpleTextInputUIComponent::SimpleTextInputUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string pre_txt, std::string edt_txt, std::string pst_txt, int flags) : UIComponent(x, y, w, h), background_color{ bc }, text_color{ tc }, pre_text{ pre_txt }, edit_text{ edt_txt }, post_text{ pst_txt }, flags{ flags }, alert{false}, alert_background_color{al_map_rgba(255,255,255,255)}, alert_text_color{al_map_rgba(0,0,0,255)}
{}
