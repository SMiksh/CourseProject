#pragma once
class Card {
public:
    Card(int id, float x, float y, float size);
    void open();
    void close();
    bool isOpen() const;
    bool isMatched() const;
    void setMatched();
    bool contains(float mx, float my) const;
    int getId() const;
    float x, y;
    float size;
private:
    int id;
    bool opened = false;
    bool matched = false;
};