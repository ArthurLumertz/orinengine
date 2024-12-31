#include "orin.hpp"

#include <GLFW/glfw3.h>
#include <thread>
#include <filesystem>
#include <cmath>
#include "stb_image.h"

GLFWwindow* window = nullptr;

int frameCount = 0;
float deltaTime;
float lastTime = GetTime();

int targetFPS = 60;
float currentFPS = 0.0f;

int lastId = -999;

void InitWindow(const int width, const int height, const char* title) {
    if (!glfwInit()) {
        Log(ORIN_FATAL, "Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        Log(ORIN_FATAL, "Failed to create GLFW window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    glfwSwapInterval(0);
    Log(ORIN_SUCCESS, "Window initialized successfully.");
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool WindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void CloseWindow() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    Log(ORIN_SUCCESS, "Window closed.");
}

void UpdateWindow() {
    float now = GetTime();
    deltaTime = now - lastTime;
    lastTime = now;
    
    float targetFrameTime = 1.0f / targetFPS;
    if (deltaTime < targetFrameTime) {
       float sleepTime = targetFrameTime - deltaTime;
       std::this_thread::sleep_for(std::chrono::duration<float>(sleepTime));
    }
    
    frameCount++;
    
    if (window) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void ClearBackground(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClearBackground(const Color& color) {
    ClearBackground(color.r, color.g, color.b, color.a);
}

void Log(int mode, const char* str) {
    const char* message = nullptr;
    bool isError = false;
    
    switch (mode) {
        case ORIN_SUCCESS:
            message = "[SUCCESS]: ";
            break;
        case ORIN_ERROR:
            message = "[ERROR]: ";
            isError = true;
            break;
        case ORIN_WARNING:
            message = "[WARNING]: ";
            break;
        case ORIN_FATAL:
            message = "[FATAL]: ";
            isError = true;
            break;
        default:
            message = "[INFO]: ";
            break;
    }
    
    if (isError) {
        std::cerr << "[LOG]" << message << str << std::endl;
    } else {
        std::cout << "[LOG]" << message << str << std::endl;
    }
}

void SetWindowSize(const int width, const int height) {
    if (window) {
        glfwSetWindowSize(window, width, height);
    }
}

void SetWindowTitle(const char* title) {
    if (window) {
        glfwSetWindowTitle(window, title);
    }
}

void BeginDrawing() {
    SetColor(WHITE);
}

void EndDrawing() {
}

void DrawRectangle(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void DrawTexture(Texture2D& texture, float x, float y, float width, float height) {
    glEnable(GL_TEXTURE_2D);
    if (lastId != texture.id) {
        glBindTexture(GL_TEXTURE_2D, texture.id);
        lastId = texture.id;
    }
    
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(x, y);
    glTexCoord2f(1, 0);
    glVertex2f(x + width, y);
    glTexCoord2f(1, 1);
    glVertex2f(x + width, y + height);
    glTexCoord2f(0, 1);
    glVertex2f(x, y + height);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void SetCamera(const Camera2D& camera) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, GetWindowWidth() / camera.zoom, 0.0f, GetWindowHeight() / camera.zoom, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetColor(float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
}

void SetColor(const Color& color) {
    SetColor(color.r, color.g, color.b, color.a);
}

int GetWindowWidth() {
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int GetWindowHeight() {
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    return height;
}

bool IsKeyPressed(const int key) {
    return glfwGetKey(window, key);
}

bool IsMousePressed(const int button) {
    return glfwGetMouseButton(window, button);
}

float GetTime() {
    return (float) glfwGetTime();
}

void SetFPS(const int fps) {
    targetFPS = fps;
}

float GetDeltaTime() {
    return deltaTime;
}

int GetFPS() {
    static float lastTimeCheck = GetTime();
    float now = GetTime();
    
    if (now - lastTimeCheck >= 1.0f) {
        currentFPS = (float) frameCount;
        frameCount = 0;
        lastTimeCheck = now;
    }
    
    return (int) currentFPS;
}

Texture2D LoadTexture(const char* filePath) {
    int width;
    int height;
    int channels;
    
    std::filesystem::path sourcePath = std::filesystem::path(__FILE__).parent_path();
    std::filesystem::path texturePath = sourcePath / filePath;
    std::string textureFilePath = texturePath.string();
    
    std::cout << textureFilePath << std::endl;
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(textureFilePath.c_str(), &width, &height, &channels, 0);
    if (data) {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
        if (channels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        
        stbi_image_free(data);
        return { (int) texture };
    } else {
        Log(ORIN_ERROR, ("Failed to load texture: " + std::string(filePath)).c_str());
        return { 0 };
    }
}

void UnloadTexture(Texture2D& texture) {
    GLuint id = static_cast<GLuint>(texture.id);
    glDeleteTextures(1, &id);
}

float Vector2Length(const Vector2& v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}
