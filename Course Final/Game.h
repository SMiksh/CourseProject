#pragma once
#include <vector>
#include "Card.h"

class Game {
public:

    Game(int screenW, int screenH);

    void click(float x, float y);
    void update(float dt);
    void render();

    int getMoves() const;
    bool isWin() const;

private:
    bool checkWin() const;
    void renderWinScreen();

private:
    int moves = 0;
    bool win = false;

    std::vector<Card> cards;
    Card* first = nullptr;
    Card* second = nullptr;

    float timer = 0.0f;

 
    int screenW;
    int screenH;
};
