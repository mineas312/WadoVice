#pragma once

#include "DirectX.hpp"
class Animation
{
    public:
        Animation(DirectX *dx);
        virtual void DrawFrame();
        virtual void DXInitialized();
    private:
        DirectX *dx;
};
