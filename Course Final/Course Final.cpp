#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "Game.h"
#include "Renderer.h"
#include "Button.h"

Game* g_game = nullptr;
GLFWwindow* g_window = nullptr;
int screenW = 800, screenH = 600;
Button exitButton;

void mouse_cb(GLFWwindow*, int button, int action, int) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double cx, cy;
        glfwGetCursorPos(g_window, &cx, &cy);
        float mx = static_cast<float>(cx);
        float my = static_cast<float>(screenH - cy); // инверсия Y

        std::cout << "Mouse: " << mx << ", " << my << std::endl; // debug

        // проверка кнопки выхода
        if (exitButton.contains(mx, my)) {
            std::cout << "Exit button pressed\n"; // debug
            glfwSetWindowShouldClose(g_window, GLFW_TRUE);
            return;
        }

        if (g_game)
            g_game->click(mx, my);
    }
}

int main() {
    if (!glfwInit()) return -1;

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    screenW = mode->width;
    screenH = mode->height;

    GLFWwindow* window = glfwCreateWindow(screenW, screenH, "MEMO", primary, nullptr);
    if (!window) { glfwTerminate(); return -1; }

    g_window = window;
    glfwMakeContextCurrent(window);
    glViewport(0, 0, screenW, screenH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, screenW, 0, screenH, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // background once
    Renderer::setBackground();

    // ИНИЦИАЛИЗАЦИЯ кнопки (делай это после known screenW/screenH)
    exitButton.w = 140;
    exitButton.h = 50;
    exitButton.x = screenW - exitButton.w - 20;
    exitButton.y = screenH - exitButton.h - 20;
    std::cout << "Exit button at: " << exitButton.x << ", " << exitButton.y << ", w=" << exitButton.w << "\n";

    Game game(screenW, screenH);
    g_game = &game;

    glfwSetMouseButtonCallback(window, mouse_cb);

    // --- игровой цикл
    double last = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - last);
        last = now;
       
        // очистка экрана (используется ранее установленный цвет фона)
        glClear(GL_COLOR_BUFFER_BIT);
        // логика и рендер игры
        game.update(dt);
        game.render();

      

        // отрисовка самой кнопки выхода
        Renderer::drawButton(exitButton.x, exitButton.y, exitButton.w, exitButton.h);
        Renderer::drawExitIcon(exitButton.x, exitButton.y,
            exitButton.w, exitButton.h);
        // swap и события
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
