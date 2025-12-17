#pragma once
#include <vector>
#include "Card.h"

class Game {
public:
    int getMoves() const;
    Game(int screenW, int screenH);
    void click(float x, float y);
    void update(float dt);
    void render();

private:
    int moves = 0;
    std::vector<Card> cards;
    Card* first = nullptr;
    Card* second = nullptr;
    float timer = 0.0f;
};
