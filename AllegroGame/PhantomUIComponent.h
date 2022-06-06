#pragma once
#include "UIComponent.h"
class PhantomUIComponent :
    public virtual UIComponent
{
public:

    PhantomUIComponent();

    virtual bool ContainsPoint(int x, int y) const override;

    virtual ~PhantomUIComponent() = default;
};

