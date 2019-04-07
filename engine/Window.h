#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

namespace graphics {
    class Window {
    public:
        GLFWwindow* window;
        const std::string name;
        const int glVersionMajor;
        const int glVersionMinor;
        
        Window(const std::string &name, int width, int height);
        ~Window();
        
        const bool shouldClose() const;
        
        const void update() const;
        const void swap() const;
        const bool focused() const;
        const glm::vec2 getSize() const;
        
    private:
        const void setIcon() const;
        bool init(const std::string &name, int width, int height);
    };
}