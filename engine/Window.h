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
        
        Window(const std::string &name, int width, int height);
        ~Window();
        
        const bool shouldClose() const;
        
        const void update() const;
        const void swap() const;
        const bool focused() const;
        const glm::vec2 getSize() const;
        
    private:
        const void setIcon(const std::string &icon) const;
        bool init(const std::string &name, int width, int height);
    };
}

void bufferCallback(GLFWwindow* w, int width, int height);
void focusCallback(GLFWwindow* w, int focused);
void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam);