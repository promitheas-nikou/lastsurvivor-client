#pragma once
#include "UIComponent.h"
class SimpleUIComponent :
    public virtual UIComponent
{
protected:

    ALLEGRO_BITMAP* texture;

    SimpleUIComponent(ALLEGRO_BITMAP* t);

public:

    void Draw() override;

    virtual ~SimpleUIComponent() = default;
};

