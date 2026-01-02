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


float origExitX = 0, origExitY = 0, origExitW = 0, origExitH = 0;

void mouse_cb(GLFWwindow*, int button, int action, int) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double cx, cy;
        glfwGetCursorPos(g_window, &cx, &cy);
        float mx = static_cast<float>(cx);
        float my = static_cast<float>(screenH - cy); 
        std::cout << "Mouse: " << mx << ", " << my << std::endl;

     
        if (exitButton.contains(mx, my)) {
            std::cout << "Exit button pressed\n"; 
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
    
    Renderer::setBackground();

    
    exitButton.w = 140;
    exitButton.h = 50;
    exitButton.x = screenW - exitButton.w - 20;
    exitButton.y = screenH - exitButton.h - 20;

    origExitX = exitButton.x;
    origExitY = exitButton.y;
    origExitW = exitButton.w;
    origExitH = exitButton.h;

    std::cout << "Exit button at: " << exitButton.x << ", " << exitButton.y << ", w=" << exitButton.w << "\n";

    Game game(screenW, screenH);
    g_game = &game;
    glfwSetMouseButtonCallback(window, mouse_cb);

   
    double last = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - last);
        last = now;

      
        glClear(GL_COLOR_BUFFER_BIT);

        // логика и рендер игры
        game.update(dt);
        game.render();

        if (g_game && g_game->isWin()) {
            float winW = origExitW;
            float winH = origExitH;
            float winX = (screenW - winW) * 0.5f;
            float winY = (screenH - winH) * 0.5f + 80.0f; 

            exitButton.x = winX;
            exitButton.y = winY;
            exitButton.w = static_cast<int>(winW);
            exitButton.h = static_cast<int>(winH);

            Renderer::drawGreenButton(winX, winY, winW, winH);
            Renderer::drawCheckIcon(winX, winY, winW, winH);

          
            int moves = g_game->getMoves();
            Renderer::drawNumber(
                moves,
                screenW * 0.5f + 40.0f,   
                winY - 70.0f,             
                20.0f                     
            );
        }

        else {
          
            exitButton.x = static_cast<int>(origExitX);
            exitButton.y = static_cast<int>(origExitY);
            exitButton.w = static_cast<int>(origExitW);
            exitButton.h = static_cast<int>(origExitH);

           
            Renderer::drawButton(exitButton.x, exitButton.y, exitButton.w, exitButton.h);
            Renderer::drawExitIcon(exitButton.x, exitButton.y, exitButton.w, exitButton.h);
        }

     
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
