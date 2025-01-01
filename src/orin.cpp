#include "orin.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <string>
#include "stb_image.h"

bool keys[KEY_LAST];
bool keysJustPressed[KEY_LAST];
bool buttons[BUTTON_LAST];
bool buttonsJustPressed[BUTTON_LAST];

GLFWwindow* window = nullptr;
int width;
int height;

int mouseX;
int mouseY;

int targetFPS = 60;
int useVSync = ORIN_FALSE;

Camera2D camera = { Vector2{0.0f, 0.0f}, 0.0f };

float deltaTime;
float elapsedTime;

float lastDelta = GetTime();
float lastTime = GetNanoTime();
float lastTimer = GetCurrentTimeMillis();
double nsPerTick = 1000000000.0 / targetFPS;
double unprocessed = 0;
int frameCount = 0;
int frames = 0;
bool shouldRender = true;

static GLuint lastId = -999;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key < 0 || key > KEY_LAST) {
        return;
    }
    
    keys[key] = action != GLFW_RELEASE;
    keysJustPressed[key] = action == GLFW_PRESS;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button < 0 || button > BUTTON_LAST) {
        return;
    }
    
    buttons[button] = action != GLFW_RELEASE;
    buttons[button] = action == GLFW_PRESS;
}

void FramebufferSizeCallback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);
    width = w;
    height = h;
}

void MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
    mouseX = static_cast<int>(xpos);
    mouseY = static_cast<int>(ypos);
}

void InitWindow(const int initialWidth, const int initialHeight, const char* title) {
    if (!glfwInit()) {
        Log(ORIN_FATAL, "Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }
    
    width = initialWidth;
    height = initialHeight;
    
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        Log(ORIN_FATAL, "Failed to create GLFW window.");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MousePositionCallback);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    
    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    glfwSwapInterval(useVSync);
    Log(ORIN_SUCCESS, "Window created");
    
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
    if (!window) {
        return;
    }
    
    float now = GetNanoTime();
    unprocessed += (now - lastTime) / nsPerTick;
    lastTime = now;
    
    float nowDelta = GetTime();
    deltaTime = nowDelta - lastDelta;
    lastDelta = nowDelta;
    
    elapsedTime += deltaTime;
    
    while (unprocessed >= 1) {
        shouldRender = true;
        frames++;
        unprocessed -= 1;
    }
    
    if (GetCurrentTimeMillis() - lastTimer >= 1000) {
        frameCount = frames;
        frames = 0;
        lastTimer += 1000;
    }
    
    if (shouldRender) {
        glfwSwapBuffers(window);
    }
    glfwPollEvents();
}

void ClearBackground(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void ClearBackground(const Color& color) {
    ClearBackground(color.r, color.g, color.b, color.a);
}

void Log(int mode, const char* str) {
    std::string prefix = "";
    bool isError = false;
    
    switch (mode) {
        case ORIN_SUCCESS:
            prefix = "[SUCCESS]: ";
            break;
        case ORIN_ERROR:
            prefix = "[ERROR]: ";
            isError = true;
            break;
        case ORIN_WARNING:
            prefix = "[WARNING]: ";
            break;
        case ORIN_FATAL:
            prefix = "[FATAL]: ";
            isError = true;
            break;
        default:
            prefix = "[INFO]: ";
            break;
    }
    
    prefix = "[LOG]" + prefix;
    if (isError) {
        std::cerr << prefix << str << std::endl;
    } else {
        std::cout << prefix << str << std::endl;
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
    
    float zoom = 1.0f;
    if (camera.zoom >= 1.0) {
        zoom = camera.zoom;
    }
    
    float w = GetWindowWidth() / zoom;
    float h = GetWindowHeight() / zoom;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void DrawRectangle(float x, float y, float width, float height, float degrees) {
    float radians = -degrees * (M_PI / 180.0f);

    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    float corners[4][2] = {
        { -width / 2.0f, -height / 2.0f },
        {  width / 2.0f, -height / 2.0f },
        {  width / 2.0f,  height / 2.0f },
        { -width / 2.0f,  height / 2.0f }
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cos(radians) - corners[i][1] * sin(radians);
        float yy = corners[i][0] * sin(radians) + corners[i][1] * cos(radians);

        glVertex2f(centerX + xx, centerY + yy);
    }
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

void DrawTexture(Texture2D& texture, float x, float y, float width, float height, float degrees) {
    glEnable(GL_TEXTURE_2D);
    if (lastId != texture.id) {
        glBindTexture(GL_TEXTURE_2D, texture.id);
        lastId = texture.id;
    }

    float radians = -degrees * (M_PI / 180.0f);
    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    float corners[4][2] = {
        { -width / 2.0f, -height / 2.0f },
        {  width / 2.0f, -height / 2.0f },
        {  width / 2.0f,  height / 2.0f },
        { -width / 2.0f,  height / 2.0f }
    };

    float texCoords[4][2] = {
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 1.0f, 1.0f },
        { 0.0f, 1.0f }
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cos(radians) - corners[i][1] * sin(radians);
        float yy = corners[i][0] * sin(radians) + corners[i][1] * cos(radians);

        float wx = centerX + xx;
        float wy = centerY + yy;

        glTexCoord2f(texCoords[i][0], texCoords[i][1]);
        glVertex2f(wx, wy);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height) {
    float x0 = (float) subTexture.x / texture.width;
    float y0 = (float) subTexture.y / texture.height;
    float x1 = (float) (subTexture.x + subTexture.width) / texture.width;
    float y1 = (float) (subTexture.y + subTexture.height) / texture.height;
    
    glEnable(GL_TEXTURE_2D);
    if (lastId != texture.id) {
        glBindTexture(GL_TEXTURE_2D, texture.id);
        lastId = texture.id;
    }
    
    glBegin(GL_QUADS);
    glTexCoord2f(x0, y0);
    glVertex2f(x, y);
    glTexCoord2f(x1, y0);
    glVertex2f(x + width, y);
    glTexCoord2f(x1, y1);
    glVertex2f(x + width, y + height);
    glTexCoord2f(x0, y1);
    glVertex2f(x, y + height);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height, float degrees) {
    glEnable(GL_TEXTURE_2D);
    if (lastId != texture.id) {
        glBindTexture(GL_TEXTURE_2D, texture.id);
        lastId = texture.id;
    }

    float radians = -degrees * (M_PI / 180.0f);
    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    float corners[4][2] = {
        { -width / 2.0f, -height / 2.0f },
        {  width / 2.0f, -height / 2.0f },
        {  width / 2.0f,  height / 2.0f },
        { -width / 2.0f,  height / 2.0f }
    };
    
    float x0 = (float) subTexture.x / texture.width;
    float y0 = (float) subTexture.y / texture.height;
    float x1 = (float) (subTexture.x + subTexture.width) / texture.width;
    float y1 = (float) (subTexture.y + subTexture.height) / texture.height;

    float texCoords[4][2] = {
        { x0, y0 },
        { x1, y0 },
        { x1, y1 },
        { x0, y1 }
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cos(radians) - corners[i][1] * sin(radians);
        float yy = corners[i][0] * sin(radians) + corners[i][1] * cos(radians);

        float wx = centerX + xx;
        float wy = centerY + yy;

        glTexCoord2f(texCoords[i][0], texCoords[i][1]);
        glVertex2f(wx, wy);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void SetCamera(const Camera2D& cam) {
    camera = cam;
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

bool IsKeyDown(const int& key) {
    return keys[key];
}

bool IsKeyPressed(const int& key) {
    bool result = keysJustPressed[key];
    keysJustPressed[key] = false;
    return result;
}

bool IsMouseDown(const int& button) {
    return buttons[button];
}

bool IsMousePressed(const int& button) {
    bool result = buttons[button];
    buttons[button] = false;
    return result;
}

int GetMouseX() {
    return mouseX;
}

int GetMouseY() {
    return mouseY;
}

float GetElapsedTime() {
    return elapsedTime;
}

float GetTime() {
    return (float) glfwGetTime();
}

void SetFPS(int fps) {
    if (fps <= 0) {
        fps = 1;
    }
    targetFPS = fps;
    nsPerTick = 1000000000.0 / fps;
}

void UseVSync(const int& sync) {
    if (window) {
        glfwSwapInterval(sync);
    }
}

float GetDeltaTime() {
    return deltaTime;
}

int GetFPS() {
    return frameCount;
}

Texture2D LoadTexture(const char* filePath) {
    int width;
    int height;
    int channels;
    
    std::filesystem::path sourcePath = std::filesystem::path(__FILE__).parent_path();
    std::filesystem::path texturePath = sourcePath / filePath;
    std::string textureFilePath = texturePath.string();
    
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
        
        Log(ORIN_SUCCESS, (std::string("Loaded texture [") + filePath + "]").c_str());
        
        return { static_cast<int>(texture), width, height };
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

void Vector2Normalize(Vector2& v) {
    float length = Vector2Length(v);
    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
    }
}

float Vector2Distance(const Vector2& v1, const Vector2& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    return sqrtf(dx * dx + dy * dy);
}

float Vector3Length(const Vector3& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

void Vector3Normalize(Vector3& v) {
    float length = Vector3Length(v);
    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
}

float Vector3Distance(const Vector3& v1, const Vector3& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    return sqrtf(dx * dx + dy * dy + dz * dz);
}

float Vector4Length(const Vector4& v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

void Vector4Normalize(Vector4& v) {
    float length = Vector4Length(v);
    if (length > 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
        v.w /= length;
    }
}

float Vector4Distance(const Vector4& v1, const Vector4& v2) {
    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;
    float dz = v1.z - v2.z;
    float dw = v1.w - v2.w;
    return sqrtf(dx * dx + dy * dy + dz * dz + dw * dw);
}

bool RectIntersects(Rectangle& r1, Rectangle& r2) {
    return !(r1.x > r2.x + r2.width  ||
             r1.x + r1.width < r2.x  ||
             r1.y > r2.y + r2.height ||
             r1.y + r1.height < r2.y);
}

long long GetNanoTime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());
    return nanos.count();
}

long long GetCurrentTimeMillis() {
    auto now = std::chrono::high_resolution_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    return millis.count();
}

bool PointInRect(Rectangle& rect, float x, float y) {
    return (x >= rect.x && x <= rect.x + rect.width &&
            y >= rect.y && y <= rect.y + rect.height);
}
