#include "Card.h"

Card::Card(int id, float x, float y, float size)
    : id(id), x(x), y(y), size(size) {
}

void Card::open() { opened = true; }
void Card::close() { if (!matched) opened = false; }

bool Card::isOpen() const { return opened; }
bool Card::isMatched() const { return matched; }
void Card::setMatched() { matched = true; }

int Card::getId() const { return id; }

bool Card::contains(float mx, float my) const {
    return mx >= x && mx <= x + size &&
        my >= y && my <= y + size;
}
