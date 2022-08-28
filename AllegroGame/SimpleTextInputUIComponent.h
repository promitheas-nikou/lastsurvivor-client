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
    std::string pre_text;
    std::string edit_text;
    int flags;
public:
    virtual bool KeyChar(ALLEGRO_KEYBOARD_EVENT& evt) final;
    virtual void Draw(int plane) final;
    void ClearTextBuffer();
    std::string GetTextBuffer();

    SimpleTextInputUIComponent(int x, int y, int w, int h, ALLEGRO_COLOR bc, ALLEGRO_COLOR tc, std::string pre_txt, std::string edt_txt, int flags);
};

