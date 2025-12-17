#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <GL/gl.h>


// палитра: фон Ч тЄмный, закрыта€ карта Ч синий, открыта€ Ч светла€, совпавша€ Ч зелЄна€
void Renderer::setBackground() {
    glClearColor(0.10f, 0.12f, 0.16f, 1.0f); // тЄмный фон
}

void Renderer::drawButton(float x, float y, float w, float h) {
    glColor3f(0.75f, 0.25f, 0.25f); // спокойный красный

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
    glColor3f(0.18f, 0.32f, 0.55f); // спокойный синий

    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void Renderer::drawExitIcon(float x, float y, float w, float h) {
    glLineWidth(4.0f);
    glColor3f(0.95f, 0.9f, 0.9f); // почти белый, контрастный

    float pad = w * 0.25f;

    glBegin(GL_LINES);
    glVertex2f(x + pad, y + pad);
    glVertex2f(x + w - pad, y + h - pad);

    glVertex2f(x + w - pad, y + pad);
    glVertex2f(x + pad, y + h - pad);
    glEnd();
}


void Renderer::drawRect(float x, float y, float size, bool open, bool matched) {
    // цвет
    if (matched) {
        glColor3f(0.25f, 0.85f, 0.55f); // зелЄна€
    }
    else if (open) {
        glColor3f(0.95f, 0.92f, 0.7f); // светло-жЄлта€ / беж
    }
    else {
        glColor3f(0.20f, 0.35f, 0.6f); // сине-серый закрытой карты
    }

    // основной квадратик
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();

    // тонка€ рамка (чуть темнее)
    glLineWidth(2.0f);
    glColor3f(0.06f, 0.08f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x, y + size);
    glEnd();
}
