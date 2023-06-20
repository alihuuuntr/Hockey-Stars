#include "Ball.h"

Ball::Ball(int x, int y, double radius, SDL_Renderer* renderer, const char* surfaceTexturePath, const char* sideTexturePath)
    : GameObject(x, y, radius, renderer) {

    SDL_Surface* surface1 = IMG_Load(surfaceTexturePath);
    surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);

    SDL_Surface* surface2 = IMG_Load(sideTexturePath);
    sideTexture = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
}

void Ball::renderSurface() {
    SDL_Rect dst;
    dst.x = x - radius;
    dst.y = y - radius;
    dst.w = 2 * radius;
    dst.h = 2 * radius;

    double angleDegrees = 0;

    // Uncomment the following line if you want the puck to rotate
    angleDegrees = angle * 180 / M_PI;

    SDL_RenderCopyEx(renderer, surfaceTexture, NULL, &dst, angleDegrees, NULL, SDL_FLIP_NONE);
}