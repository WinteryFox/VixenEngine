#include "Window.h"

graphics::Window::Window(const std::string &name, const int width, const int height) : glVersionMajor(1), glVersionMinor(1) {
    init(name, width, height);
}

graphics::Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool graphics::Window::init(const std::string &name, int width, int height) {
    if (!glfwInit()) {
        std::cerr << "Could not initialize GLFW" << std::endl;
        return false;
    }
    
    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    
    return true;
}

const void graphics::Window::update() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwPollEvents();
}

const void graphics::Window::swap() const {
    glfwSwapBuffers(window);
}

const bool graphics::Window::shouldClose() const {
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

const glm::vec2 graphics::Window::getSize() const {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return glm::vec2(width, height);
}

const bool graphics::Window::focused() const {
    return true;
}

const void graphics::Window::setIcon() const {
    return;
}
