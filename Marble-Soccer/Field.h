#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Field {
public:
    Field(SDL_Renderer* renderer);
    ~Field();

    void render();

private:
    SDL_Texture* texture;
    SDL_Renderer* renderer;
};