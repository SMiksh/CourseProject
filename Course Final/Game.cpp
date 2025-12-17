#include "Game.h"
#include "Renderer.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

Game::Game(int screenW, int screenH) {
    std::srand((unsigned)time(nullptr));
    // параметры сетки
    const int cols = 4;
    const int rows = 2;

    // вычисляем размер карточки и отступы так, чтобы сетка была по центру
    float totalGapFactor = 0.2f; // доля размера карточки как gap
    float maxCardW = screenW / (cols + (cols + 1) * totalGapFactor);
    float maxCardH = screenH / (rows + (rows + 1) * totalGapFactor);
    float cardSize = std::min(maxCardW, maxCardH);
    float gap = cardSize * totalGapFactor;

    float gridWidth = cols * cardSize + (cols - 1) * gap;
    float gridHeight = rows * cardSize + (rows - 1) * gap;

    float startX = (screenW - gridWidth) * 0.5f;
    float startY = (screenH - gridHeight) * 0.5f;

    // карточки: пары id
    std::vector<int> ids;
    for (int i = 0; i < (cols * rows) / 2; ++i) {
        ids.push_back(i);
        ids.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(ids.begin(), ids.end(), g);

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
    if (second) return; // ждём окончания проверки
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
            first = second = nullptr;
            timer = 0.0f;
        }
    }
}

int Game::getMoves() const {
    return moves;
}


void Game::render() {
    for (auto& c : cards) {
        Renderer::drawRect(c.x, c.y, c.size, c.isOpen(), c.isMatched());
    }
}
