#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "Ball.h"
#include "Field.h"

class Game {
public:
    Game();
    ~Game();

    void run();

    static const int NUM_PLAYERS = 5;

private:
    bool handleEvents(SDL_Event&);
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;
    Field* field;
    std::vector<GameObject*> gameObjects;
    std::vector<Player*> team1;
    std::vector<Player*> team2;
    bool running;
    
};