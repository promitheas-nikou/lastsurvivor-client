#pragma once
#include "SimpleUIComponent.h"
#include "RectangularUIComponent.h"
#include <string>

class SimpleTextInputUIComponent :
    public SimpleUIComponent,
    public RectangularUIComponent
{
private:
    ALLEGRO_COLOR background_color;
    ALLEGRO_COLOR text_color;
    ALLEGRO_COLOR alert_background_color;
    ALLEGRO_COLOR alert_text_color;
    bool alert;
    std::string pre_text;
    std::string edit_text;
    std::string post_text;
    int flags;
public:
    virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& evt) final;
    virtual void Draw(int plane) final;
    void SetAlert(std::string temp_string, ALLEGRO_COLOR text_color, ALLEGRO_COLOR back_color);
    void ClearTextBuffer();
    std::string GetTextBuffer();
    void SetTextBuffer(std::string s);

    SimpleTextInputUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string pre_txt, std::string edt_txt, std::string pst_txt, int flags);
};

