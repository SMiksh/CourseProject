#pragma once

struct Button {
    float x, y, w, h;

    bool contains(float mx, float my) const {
        return mx >= x && mx <= x + w &&
            my >= y && my <= y + h;
    }
};
