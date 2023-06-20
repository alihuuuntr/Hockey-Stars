#pragma once

#include "GameObject.h"

class Ball : public GameObject {
public:
    Ball(int x, int y, double radius, SDL_Renderer* renderer, const char* textureFile, const char* sideTexturePath);
    void renderSurface() override;
};