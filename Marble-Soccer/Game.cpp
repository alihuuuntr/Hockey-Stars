#include "Game.h"

Game::Game() {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Marble Soccer",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    field = new Field(renderer);

    const int PLAYER_RADIUS = SCREEN_HEIGHT / (2 * NUM_PLAYERS + 1);  
    const int TEAM1_X = SCREEN_WIDTH / 4;  // Team 1 starts at 1/4 of the screen width
    const int TEAM2_X = 3 * SCREEN_WIDTH / 4;  // Team 2 starts at 3/4 of the screen width

    team1.resize(NUM_PLAYERS);
    team2.resize(NUM_PLAYERS);

    for(int i = 0; i < Game::NUM_PLAYERS; i++) {

        gameObjects.push_back(new Player(100, 100 + i * 100, 30, renderer, "assets/kazakhstan.png", "assets/side_kz.png"));  // Team 1
        gameObjects.push_back(new Player(700, 100 + i * 100, 30, renderer, "assets/canada.png", "assets/side_ca.png"));  // Team 2
    }

    gameObjects.push_back(new Ball(400, 300, 20, renderer, "assets/puck.png", "assets/side_puck.png"));

    running = true;
}

Game::~Game() {
    for(GameObject* gameObject : gameObjects) {
        delete gameObject;
    }
    delete field;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    bool running = true;
    SDL_Event event;

    while(running) {
        frameStart = SDL_GetTicks();

        if(!handleEvents(event)) {  
            break; 
        }
        update();
        render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

bool Game::handleEvents(SDL_Event& event) {

    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            return false;
        }

        for(GameObject* gameObject : gameObjects) {
            if(Player* player = dynamic_cast<Player*>(gameObject)) {
                player->handleEvent(event);
            }
        }
    }
    return true;
}

void Game::update() {
    for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
        (*it)->update();

        for(auto it2 = std::next(it); it2 != gameObjects.end(); ++it2) {
            (*it)->handleCollisionWith(**it2);
        }
    }
}

void Game::render() {
    //SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderClear(renderer);
    field->render();

    for(GameObject* gameObject : gameObjects) {
        gameObject->renderSide();
    }
    for(GameObject* gameObject : gameObjects) {
        gameObject->renderSurface();
    }

    SDL_RenderPresent(renderer);
}
