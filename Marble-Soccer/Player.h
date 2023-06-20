#pragma once

#include "GameObject.h"

class Player : public GameObject {
public:
    Player(int x, int y, int radius, SDL_Renderer* renderer, const char* surfaceTexturePath, const char* sideTexturePath);
    ~Player();
    void handleEvent(SDL_Event& event);
    void renderSurface() override;

private:
    int startX, startY;
};
