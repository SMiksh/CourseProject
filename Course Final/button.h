#pragma once
class Button {
public:
    bool contains(float mx, float my) const {
        return mx >= x && mx <= x + w &&
            my >= y && my <= y + h;
    }
    float x, y, w, h;
};