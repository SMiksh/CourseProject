#pragma once

class Renderer;

class GameObject {
public:
    virtual void update(float dt) = 0;
    virtual void render(Renderer& renderer) = 0;
    virtual ~GameObject() = default;
};
