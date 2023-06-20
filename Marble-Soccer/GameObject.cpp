#include "GameObject.h"
#include <SDL_image.h>
#include <iostream>

GameObject::GameObject(int x, int y, double radius, SDL_Renderer* renderer)
    : x(x), y(y), radius(radius), angle(0), angularVelocity(0), vx(0), vy(0), renderer(renderer), surfaceTexture(nullptr), sideTexture(nullptr) {

    //SDL_Surface* surface1 = IMG_Load("assets/kazakhstan.png");
    //surfaceTexture = SDL_CreateTextureFromSurface(renderer, surface1);
    //SDL_FreeSurface(surface1);

    //SDL_Surface* surface2 = IMG_Load("assets/side_kz.png");
    //sideTexture = SDL_CreateTextureFromSurface(renderer, surface2);
    //SDL_FreeSurface(surface2);
}

GameObject::~GameObject() {
    if(surfaceTexture != nullptr) {
        SDL_DestroyTexture(surfaceTexture);
    }
    if(sideTexture != nullptr) {
        SDL_DestroyTexture(sideTexture);
    }

}

void GameObject::renderSide() {
    SDL_Rect dstSide;

    dstSide.x = x - radius;
    dstSide.y = y - 1.05*radius;
    dstSide.w = 2.08 * radius;
    dstSide.h = 2.15 * radius;

    SDL_RenderCopyEx(renderer, sideTexture, NULL, &dstSide, 0, NULL, SDL_FLIP_NONE);
}



void GameObject::setVelocity(double vx, double vy) {
    this->vx = vx;
    this->vy = vy;
}

void GameObject::update() {
    checkCollision();
    applyFriction();
    x += vx;
    y += vy;
    angle += angularVelocity;
}


void GameObject::checkCollision() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const double ANGULAR_VELOCITY_FACTOR = 0.02;
    const double ELASTICITY = 1.0;

    if(x - radius < 0) {
        x = radius;
        vx = -vx * ELASTICITY;
        angularVelocity += vy * ANGULAR_VELOCITY_FACTOR;
    }

    if(x + radius > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - radius;
        vx = -vx * ELASTICITY;
        angularVelocity -= vy * ANGULAR_VELOCITY_FACTOR;
    }

    if(y - radius < 0) {
        y = radius;
        vy = -vy * ELASTICITY;
        angularVelocity -= vx * ANGULAR_VELOCITY_FACTOR;
    }

    if(y + radius > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - radius;
        vy = -vy * ELASTICITY;
        angularVelocity += vx * ANGULAR_VELOCITY_FACTOR;
    }
}

void GameObject::handleCollisionWith(GameObject& other) {
    const double ELASTICITY = 0.8;

    double dx = x - other.x;
    double dy = y - other.y;
    double distance = std::sqrtl(dx * dx + dy * dy);

    if(distance < radius + other.radius) {
 
        double ux = dx / distance;
        double uy = dy / distance;

        // Calculate the velocities along the collision axis
        double v1 = vx * ux + vy * uy;
        double v2 = other.vx * ux + other.vy * uy;

        // Calculate the final velocities along the collision axis after an elastic collision
        double new_v1 = v2;
        double new_v2 = v1;

        // Update the object velocities
        vx += (new_v1 - v1) * ux * ELASTICITY;
        vy += (new_v1 - v1) * uy * ELASTICITY;
        other.vx += (new_v2 - v2) * ux * ELASTICITY;
        other.vy += (new_v2 - v2) * uy * ELASTICITY;

        // Update the object angular velocities
        angularVelocity -= (new_v1 - v1) * 0.005f;
        other.angularVelocity += (new_v2 - v2) * 0.005f;

        // Move the objects to prevent overlapping
        double overlap = (radius + other.radius) - distance;
        x += overlap * ux / 2 + 1;
        y += overlap * uy / 2 + 1;
        other.x -= overlap * ux / 2 - 1;
        other.y -= overlap * uy / 2 - 1;
    }
}


void GameObject::applyFriction() {
    const double FRICTION_FACTOR = 0.98;
    const double MIN_VELOCITY = 0.25;
    const double ANGULAR_FRICTION_FACTOR = 0.99f;

    double newVX = vx * FRICTION_FACTOR;
    double newVY = vy * FRICTION_FACTOR;

    if(newVX > -MIN_VELOCITY && newVX < MIN_VELOCITY && 
       newVY > -MIN_VELOCITY && newVY < MIN_VELOCITY) {
        newVX = 0;
        newVY = 0;
    }

    setVelocity(newVX, newVY);
    angularVelocity *= ANGULAR_FRICTION_FACTOR;
    if(abs(angularVelocity) < 0.01) {
        angularVelocity = 0;
    }
}
