#include "Game.h"
#include "Renderer.h"
#include <algorithm>
#include <random>
#include <ctime>

Game::Game(int screenW_, int screenH_)
    : screenW(screenW_), screenH(screenH_) {

    std::srand((unsigned)time(nullptr));

    const int cols = 4;
    const int rows = 2;

    float totalGapFactor = 0.2f;
    float maxCardW = screenW / (cols + (cols + 1) * totalGapFactor);
    float maxCardH = screenH / (rows + (rows + 1) * totalGapFactor);
    float cardSize = std::min(maxCardW, maxCardH);
    float gap = cardSize * totalGapFactor;

    float gridWidth = cols * cardSize + (cols - 1) * gap;
    float gridHeight = rows * cardSize + (rows - 1) * gap;

    float startX = (screenW - gridWidth) * 0.5f;
    float startY = (screenH - gridHeight) * 0.5f;

    std::vector<int> ids;
    for (int i = 0; i < (cols * rows) / 2; ++i) {
        ids.push_back(i);
        ids.push_back(i);
    }

    std::shuffle(ids.begin(), ids.end(), std::mt19937{ std::random_device{}() });

    int idx = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            float x = startX + c * (cardSize + gap);
            float y = startY + r * (cardSize + gap);
            cards.emplace_back(ids[idx++], x, y, cardSize);
        }
    }
}

void Game::click(float x, float y) {
    if (win) return;
    if (second) return;

    for (auto& c : cards) {
        if (!c.isOpen() && !c.isMatched() && c.contains(x, y)) {
            c.open();
            if (!first) first = &c;
            else second = &c;
            break;
        }
    }
}

void Game::update(float dt) {
    if (win) return;

    if (first && second) {
        timer += dt;
        if (timer > 0.6f) {
            moves++;

            if (first->getId() == second->getId()) {
                first->setMatched();
                second->setMatched();
            }
            else {
                first->close();
                second->close();
            }

            first = nullptr;
            second = nullptr;
            timer = 0.0f;

            if (checkWin()) {
                win = true;
            }
        }
    }
}

bool Game::checkWin() const {
    for (const auto& c : cards) {
        if (!c.isMatched())
            return false;
    }
    return true;
}

int Game::getMoves() const {
    return moves;
}
bool Game::isWin() const {
    return win;
}


void Game::render() {
    for (auto& c : cards) {
        Renderer::drawRect(c.x, c.y, c.size, c.isOpen(), c.isMatched());
        if (c.isOpen()) {
            Renderer::drawSymbol(c.getId(), c.x, c.y, c.size);
        }
    }

 
    if (!win) {
        Renderer::drawNumber(moves, 20.0f, screenH - 60.0f, 30.0f);
    }

    if (win) {
        renderWinScreen();
    }
}

void Game::renderWinScreen() {

    Renderer::drawPanel(0, 0, (float)screenW, (float)screenH);


    float panelW = screenW * 0.5f;
    float panelH = screenH * 0.3f;
    float px = (screenW - panelW) * 0.5f;
    float py = (screenH - panelH) * 0.5f;

    Renderer::drawPanel(px, py, panelW, panelH);

   
}
