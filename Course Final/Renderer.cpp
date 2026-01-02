#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cmath>
#include <algorithm>

void Renderer::setBackground() {
    glClearColor(0.10f, 0.12f, 0.16f, 1.0f); 
}
void Renderer::drawButton(float x, float y, float w, float h) {
    glColor3f(0.75f, 0.25f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
    glLineWidth(2.0f);
    glColor3f(0.15f, 0.05f, 0.05f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void Renderer::drawPanel(float x, float y, float w, float h) {
    glColor3f(0.18f, 0.32f, 0.55f); 
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}
void Renderer::drawExitIcon(float x, float y, float w, float h) {
    glLineWidth(4.0f);
    glColor3f(0.95f, 0.9f, 0.9f); 
    float pad = w * 0.25f;
    glBegin(GL_LINES);
    glVertex2f(x + pad, y + pad);
    glVertex2f(x + w - pad, y + h - pad);
    glVertex2f(x + w - pad, y + pad);
    glVertex2f(x + pad, y + h - pad);
    glEnd();
}
void Renderer::drawRect(float x, float y, float size, bool open, bool matched) {
   
    if (matched) {
        glColor3f(0.25f, 0.85f, 0.55f); 
    }
    else if (open) {
        glColor3f(0.95f, 0.92f, 0.7f); 
    }
    else {
        glColor3f(0.20f, 0.35f, 0.6f); 
    }
    
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
    
    glLineWidth(2.0f);
    glColor3f(0.06f, 0.08f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}
void Renderer::drawSymbol(int id, float x, float y, float size) {
    glColor3f(0.1f, 0.1f, 0.1f); 
    glLineWidth(3.0f);
    float centerX = x + size / 2;
    float centerY = y + size / 2;
    float radius = size * 0.3f; 
    float pad = size * 0.1f; 

    int symbolType = id % 4; 

    switch (symbolType) {
    case 0:
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i += 10) {
            float degInRad = i * 3.14159f / 180;
            glVertex2f(centerX + cos(degInRad) * radius, centerY + sin(degInRad) * radius);
        }
        glEnd();
        break;
    case 1: 
        glBegin(GL_LINE_LOOP);
        glVertex2f(centerX, centerY + radius);
        glVertex2f(centerX - radius, centerY - radius);
        glVertex2f(centerX + radius, centerY - radius);
        glEnd();
        break;
    case 2: 
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 5; ++i) {
            float angle = i * 144 * 3.14159f / 180; 
            glVertex2f(centerX + radius * cos(angle), centerY + radius * sin(angle));
        }
        glEnd();
        break;
    case 3: 
        glBegin(GL_LINES);
        glVertex2f(centerX - radius, centerY);
        glVertex2f(centerX + radius, centerY);
        glVertex2f(centerX, centerY - radius);
        glVertex2f(centerX, centerY + radius);
        glEnd();
        break;
    }
}
void Renderer::drawDigit(int d, float x, float y, float s) {
    glLineWidth(3.0f);
    glColor3f(0.95f, 0.95f, 0.95f);

    float w = s;
    float h = s * 1.6f;

    auto L = [&](float x1, float y1, float x2, float y2) {
        glBegin(GL_LINES);
        glVertex2f(x + x1, y + y1);
        glVertex2f(x + x2, y + y2);
        glEnd();
        };

    
    bool seg[10][7] = {
        {1,1,1,1,1,1,0}, 
        {0,1,1,0,0,0,0}, 
        {1,1,0,1,1,0,1}, 
        {1,1,1,1,0,0,1}, 
        {0,1,1,0,0,1,1}, 
        {1,0,1,1,0,1,1}, 
        {1,0,1,1,1,1,1}, 
        {1,1,1,0,0,0,0}, 
        {1,1,1,1,1,1,1}, 
        {1,1,1,1,0,1,1}  
    };

    if (seg[d][0]) L(0, h, w, h);        
    if (seg[d][1]) L(w, h, w, h / 2);    
    if (seg[d][2]) L(w, h / 2, w, 0);    
    if (seg[d][3]) L(0, 0, w, 0);        
    if (seg[d][4]) L(0, h / 2, 0, 0);    
    if (seg[d][5]) L(0, h, 0, h / 2);    
    if (seg[d][6]) L(0, h / 2, w, h / 2);
}

void Renderer::drawNumber(int value, float x, float y, float s) {
    if (value == 0) {
        drawDigit(0, x, y, s);
        return;
    }

    float offset = 0.0f;
    int v = value;

    while (v > 0) {
        int d = v % 10;
        drawDigit(d, x - offset, y, s);
        offset += s * 1.2f;
        v /= 10;
    }
}

void Renderer::drawGreenButton(float x, float y, float w, float h) {

    glColor3f(0.25f, 0.85f, 0.55f); 
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();

    
    glLineWidth(2.0f);
    glColor3f(0.06f, 0.08f, 0.06f); 
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void Renderer::drawCheckIcon(float x, float y, float w, float h) {

    glColor3f(0.95f, 0.95f, 0.95f);
    glLineWidth(5.0f);


    float cx = x + w * 0.5f;
    float cy = y + h * 0.5f;

   
    float size = std::min(w, h) * 0.45f;

   
    float ax = size * 0.25f;
    float ay = size * 0.05f;
    float bx = size * 0.0f;
    float by = size * 0.25f;
    float cx2 = size * 0.7f;
    float cy2 = size * 0.4f;

 
    glBegin(GL_LINES);
    glVertex2f(cx - ax, cy + ay);
    glVertex2f(cx - bx, cy - by);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(cx - bx, cy - by);
    glVertex2f(cx + cx2, cy + cy2);
    glEnd();
}
