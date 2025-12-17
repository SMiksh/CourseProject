#pragma once

class Renderer {
public:
    // рисует карточку; renderer сам решает цвета в зависимости от состояния
    static void drawRect(float x, float y, float size, bool open, bool matched);
    // устанавливаем приятный фон (вызывается в main один раз)
    static void setBackground();
    static void drawButton(float x, float y, float w, float h);
    static void drawExitIcon(float x, float y, float w, float h);
    static void drawPanel(float x, float y, float w, float h);
    static void drawDigit(int d, float x, float y, float s);
    static void drawNumber(int value, float x, float y, float s);

};
