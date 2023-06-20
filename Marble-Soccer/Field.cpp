#include "Field.h"

Field::Field(SDL_Renderer* renderer) : renderer(renderer) {
    SDL_Surface* surface = IMG_Load("assets/ice_texture.png");
    if(!surface) {
        std::cerr << "Failed to load field image: " << IMG_GetError() << std::endl;
        return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!texture) {
        std::cerr << "Failed to create field texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_FreeSurface(surface);
}

Field::~Field() {
    SDL_DestroyTexture(texture);
}

void Field::render() {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}