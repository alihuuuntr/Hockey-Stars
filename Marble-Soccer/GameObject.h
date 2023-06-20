#pragma once

#include <SDL.h>
#include <SDL_image.h>

class GameObject {
public:
    GameObject(int x, int y, double radius, SDL_Renderer* renderer);
    virtual ~GameObject();

    void update();
    virtual void renderSurface() = 0;
    void renderSide();
    void checkCollision();
    void applyFriction();
    void setVelocity(double vx, double vy);
    void handleCollisionWith(GameObject& other);

protected:
    double x, y;
    double radius;
    double angle;
    double angularVelocity;
    double vx, vy;
    SDL_Texture* surfaceTexture;
    SDL_Texture* sideTexture;
    SDL_Renderer* renderer;
};

