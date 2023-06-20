#include "Player.h"

Player::Player(int x, int y, int radius, SDL_Renderer* renderer, const char* surfaceTexturePath, const char* sideTexturePath)
    : GameObject(x, y, radius, renderer), startX(0), startY(0) {

    SDL_Surface* surface1 = IMG_Load(surfaceTexturePath);
    surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface1);
    SDL_FreeSurface(surface1);

    SDL_Surface* surface2 = IMG_Load(sideTexturePath);
    sideTexture = SDL_CreateTextureFromSurface(renderer, surface2);
    SDL_FreeSurface(surface2);
}

Player::~Player() {
    SDL_DestroyTexture(surfaceTexture);
    SDL_DestroyTexture(sideTexture);
}

void Player::handleEvent(SDL_Event& event) {
    const double SPEED_FACTOR = 0.1f;

    if(event.type == SDL_MOUSEBUTTONDOWN) {
        if((event.button.x - x) * (event.button.x - x) + (event.button.y - y) * (event.button.y - y) <= radius * radius) {
            startX = event.button.x;
            startY = event.button.y;
        }
    } else if(event.type == SDL_MOUSEBUTTONUP) {
        if(startX != 0 || startY != 0) {
            int dx = event.button.x - startX;
            int dy = event.button.y - startY;

            setVelocity(-dx * SPEED_FACTOR, -dy * SPEED_FACTOR);

            startX = 0;
            startY = 0;
        }
    }
}

void Player::renderSurface() {
    SDL_Rect dst;
    dst.x = x - radius;
    dst.y = y - radius;
    dst.w = 2 * radius;
    dst.h = 2 * radius;

    double angleDegrees = angle * 180 / M_PI;
    SDL_RenderCopyEx(renderer, surfaceTexture, NULL, &dst, angleDegrees, NULL, SDL_FLIP_NONE);
}
