#pragma once
class Renderer {
public:
 
    static void drawRect(float x, float y, float size, bool open, bool matched);

    static void drawSymbol(int id, float x, float y, float size);
  
    static void setBackground();
    static void drawButton(float x, float y, float w, float h);
    static void drawExitIcon(float x, float y, float w, float h);
    static void drawPanel(float x, float y, float w, float h);
    static void drawDigit(int d, float x, float y, float s);
    static void drawNumber(int value, float x, float y, float s);

 
    static void drawGreenButton(float x, float y, float w, float h);
    static void drawCheckIcon(float x, float y, float w, float h);
};
