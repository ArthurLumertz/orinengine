#include "orin.hpp"

//#include <iostream>
#include <GLFW/glfw3.h>
#include <GLUT/glut.h>
//#include <OpenAL/al.h>
//#include <OpenAL/alc.h>
#include <thread>
#include <filesystem>
#include <cmath>
#include <chrono>
#include <string>
#include <random>
#include "stb_image.h"
#include "stb_vorbis.h"

#define MAX_VERTICES 10000

const float DEG_TO_RAD = M_PI / 180.0f;
const float RAD_TO_DEG = 180.0f / M_PI;

bool keys[KEY_LAST];
bool keysJustPressed[KEY_LAST];
bool buttons[BUTTON_LAST];
bool buttonsJustPressed[BUTTON_LAST];

bool mouseGrabbed = false;

GLFWwindow* window = nullptr;
int width;
int height;

float prevMouseX;
float prevMouseY;
float mouseDX;
float mouseDY;
float mouseX;
float mouseY;

int targetFPS = 60;
int useVSync = ORIN_FALSE;

Camera2D camera;

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

bool isDrawing = false;

static GLuint lastId = -999;

static std::vector<std::string> logList;

static std::random_device rd;
static std::mt19937 gen(rd());

//ALCdevice* device = nullptr;
//ALCcontext* context = nullptr;
//ALuint buffer = 0;
//ALuint source = 0;

class Tessellator {
private:
    float vertexBuffer[MAX_VERTICES * 3];
    float textureCoordinateBuffer[MAX_VERTICES * 2];
    float colorBuffer[MAX_VERTICES * 4];
    
    int vertices;
    
    bool hasTexture;
    float textureU;
    float textureV;
    
    bool hasColor;
    float r;
    float g;
    float b;
    float a;
public:
    void init() {
        clear();
    }
    
    void clear() {
        memset(vertexBuffer, 0, sizeof(vertexBuffer));
        memset(textureCoordinateBuffer, 0, sizeof(textureCoordinateBuffer));
        memset(colorBuffer, 0, sizeof(colorBuffer));
        
        hasTexture = false;
        hasColor = false;
        vertices = 0;
    }
    
    void flush() {
        if (vertices > 0) {
            glEnableClientState(GL_VERTEX_ARRAY);
            if (hasTexture) {
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (hasColor) {
                glEnableClientState(GL_COLOR_ARRAY);
            }
            
            glVertexPointer(3, GL_FLOAT, 0, vertexBuffer);
            if (hasTexture) {
                glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinateBuffer);
            }
            if (hasColor) {
                glColorPointer(4, GL_FLOAT, 0, colorBuffer);
            }
            
            glDrawArrays(GL_QUADS, 0, vertices);
            
            glDisableClientState(GL_VERTEX_ARRAY);
            if (hasTexture) {
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            }
            if (hasColor) {
                glDisableClientState(GL_COLOR_ARRAY);
            }
            
            clear();
        }
    }
    
    void vertex(float x, float y, float z) {
        vertexBuffer[vertices * 3] = x;
        vertexBuffer[vertices * 3 + 1] = y;
        vertexBuffer[vertices * 3 + 2] = z;
        
        if (hasTexture) {
            textureCoordinateBuffer[vertices * 2] = textureU;
            textureCoordinateBuffer[vertices * 2 + 1] = textureV;
        }
        if (hasColor) {
            colorBuffer[vertices * 4] = r;
            colorBuffer[vertices * 4 + 1] = g;
            colorBuffer[vertices * 4 + 2] = b;
            colorBuffer[vertices * 4 + 3] = a;
        }
        
        vertices++;
        if (vertices >= MAX_VERTICES) {
            flush();
        }
    }
    
    void texture(float u, float v) {
        hasTexture = true;
        textureU = u;
        textureV = v;
    }
    
    void color(float r, float g, float b, float a) {
        hasColor = true;
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    
    void vertexUV(float x, float y, float z, float u, float v) {
        texture(u, v);
        vertex(x, y, z);
    }
};

static Tessellator* t = new Tessellator();

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

bool InitWindow(const int initialWidth, const int initialHeight, const char* title) {
    if (!glfwInit()) {
        Log(ORIN_FATAL, "Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
        return false;
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
        return false;
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
    Log(ORIN_INFO, "Created window");
    
    prevMouseX = GetMouseX();
    prevMouseY = GetMouseY();
    
    camera.position = { 0.0f, 0.0f };
    //camera.target = { 0.0f, 0.0f };
    camera.zoom = 1.0f;
    
//    device = alcOpenDevice(nullptr);
//    if (!device) {
//        Log(ORIN_FATAL, "Failed to open audio device!");
//        const ALCenum error = alcGetError(device);
//        Log(ORIN_FATAL, ("OpenAL Error: " + std::to_string(error)).c_str());
//        exit(EXIT_FAILURE);
//        return false;
//    }
//
//    context = alcCreateContext(device, nullptr);
//    if (!context || alcGetError(device) != ALC_NO_ERROR) {
//        Log(ORIN_FATAL, "Failed to create OpenAL context!");
//        const ALCenum error = alcGetError(device);
//        Log(ORIN_FATAL, ("OpenAL Error: " + std::to_string(error)).c_str());
//        exit(EXIT_FAILURE);
//        return false;
//    }
//
//    if (!alcMakeContextCurrent(context) || alcGetError(device) != ALC_NO_ERROR) {
//        Log(ORIN_FATAL, "Failed to make OpenAL context current!");
//        const ALCenum error = alcGetError(device);
//        Log(ORIN_FATAL, ("OpenAL Error: " + std::to_string(error)).c_str());
//        exit(EXIT_FAILURE);
//        return false;
//    }
//
//    Log(ORIN_INFO, "Initialized OpenAL");
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

bool WindowShouldClose() {
    return glfwWindowShouldClose(window);
}

void CloseWindow() {
    delete t;
    t = nullptr;
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
    Log(ORIN_INFO, "Window closed.");
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
    
    float xx = GetMouseX();
    float yy = GetMouseY();
    mouseDX = xx - prevMouseX;
    mouseDY = yy - prevMouseY;
    prevMouseX = xx;
    prevMouseY = yy;
    
    if (mouseGrabbed) {
        glfwSetCursorPos(window, GetWindowWidth() / 2, GetWindowHeight() / 2);
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
    static const char* prefixes[] = {
        "[SUCCESS]: ",
        "[ERROR]: ",
        "[WARNING]: ",
        "[FATAL]: ",
        "[INFO]: "
    };

    static const bool isError[] = {
        false,
        true,
        false,
        true,
        false
    };

    if (mode < 0 || mode >= sizeof(prefixes) / sizeof(prefixes[0])) {
        return;
    }

    const char* prefix = prefixes[mode];
    bool logToErrorStream = isError[mode];

    std::string msg = prefix;
    msg += str;

    if (logToErrorStream) {
        std::cerr << msg << std::endl;
    } else {
        std::cout << msg << std::endl;
    }

    logList.push_back(msg);
}

std::vector<std::string>& GetLog() {
    return logList;
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
    isDrawing = true;
    
    float w = GetViewportWidth();
    float h = GetViewportHeight();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w, 0.0f, h, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-camera.position.x, -camera.position.y, 0.0f);
    
    t->init();
}

void EndDrawing() {
    t->flush();
    isDrawing = false;
}

void BindTexture(const Texture2D& texture) {
    GLuint id = static_cast<GLuint>(texture.id);
    if (lastId != id) {
        glBindTexture(GL_TEXTURE_2D, id);
        lastId = id;
    }
}

void DrawRectangle(float x, float y, float width, float height) {
    t->vertex(x, y, 0.0f);
    t->vertex(x + width, y, 0.0f);
    t->vertex(x + width, y + height, 0.0f);
    t->vertex(x, y + height, 0.0f);
}

void DrawRectangle(float x, float y, float width, float height, float degrees) {
    float radians = -degrees * DEG_TO_RAD;

    float centerX = x + width / 2.0f;
    float centerY = y + height / 2.0f;

    float corners[4][2] = {
        { -width / 2.0f, -height / 2.0f },
        {  width / 2.0f, -height / 2.0f },
        {  width / 2.0f,  height / 2.0f },
        { -width / 2.0f,  height / 2.0f }
    };

    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cosf(radians) - corners[i][1] * sinf(radians);
        float yy = corners[i][0] * sinf(radians) + corners[i][1] * cosf(radians);

        t->vertex(centerX + xx, centerY + yy, 0.0f);
    }
}

void DrawTexture(Texture2D& texture, float x, float y, float width, float height) {
    BindTexture(texture);
    
    t->vertexUV(x, y, 0.0f, 0.0f, 0.0f);
    t->vertexUV(x + width, y, 0.0f, 1.0f, 0.0f);
    t->vertexUV(x + width, y + height, 0.0f, 1.0f, 1.0f);
    t->vertexUV(x, y + height, 0.0f, 0.0f, 1.0f);
}

void DrawTexture(Texture2D& texture, float x, float y, float width, float height, float degrees) {
    BindTexture(texture);

    float radians = -degrees * DEG_TO_RAD;
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

    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cosf(radians) - corners[i][1] * sinf(radians);
        float yy = corners[i][0] * sinf(radians) + corners[i][1] * cosf(radians);

        float wx = centerX + xx;
        float wy = centerY + yy;

        t->vertexUV(wx, wy, 0.0f, texCoords[i][0], texCoords[i][1]);
    }
}

void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height) {
    float x0 = (float) subTexture.x / texture.width;
    float y0 = (float) subTexture.y / texture.height;
    float x1 = (float) (subTexture.x + subTexture.width) / texture.width;
    float y1 = (float) (subTexture.y + subTexture.height) / texture.height;
    
    BindTexture(texture);
    
    t->vertexUV(x, y, 0.0f, x0, y0);
    t->vertexUV(x + width, y, 0.0f, x1, y0);
    t->vertexUV(x + width, y + height, 0.0f, x1, y1);
    t->vertexUV(x, y + height, 0.0f, x0, y1);
}

void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height, float degrees) {
    BindTexture(texture);

    float radians = -degrees * DEG_TO_RAD;
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

    for (int i = 0; i < 4; i++) {
        float xx = corners[i][0] * cos(radians) - corners[i][1] * sin(radians);
        float yy = corners[i][0] * sin(radians) + corners[i][1] * cos(radians);

        float wx = centerX + xx;
        float wy = centerY + yy;

        t->vertexUV(wx, wy, 0.0f, texCoords[i][0], texCoords[i][1]);
    }
}

void SetCamera(const Camera2D& cam) {
    camera = cam;
}

void SetColor(float r, float g, float b, float a) {
    if (isDrawing) {
        t->color(r, g, b, a);
        return;
    }
    
    glColor4f(r, g, b, a);
}

void SetColor(const Color& color) {
    SetColor(color.r, color.g, color.b, color.a);
}

int GetWindowWidth() {
    return width;
}

int GetWindowHeight() {
    return height;
}

float GetViewportWidth() {
    float z = std::max(1.0f, camera.zoom);
    return width / z;
}

float GetViewportHeight() {
    float z = std::max(1.0f, camera.zoom);
    return height / camera.zoom;
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
    return static_cast<int>(mouseX);
}

int GetMouseY() {
    return static_cast<int>(mouseY);
}

Vector2 GetMousePosition() {
    return { mouseX, mouseY };
}

float GetMouseDX() {
    float result = mouseDX;
    mouseDX = 0.0f;
    return result;
}

float GetMouseDY() {
    float result = mouseDY;
    mouseDY = 0.0f;
    return result;
}

Vector2 GetMouseDelta() {
    return { GetMouseDX(), GetMouseDY() };
}

float GetElapsedTime() {
    return elapsedTime;
}

float GetTime() {
    return (float) glfwGetTime();
}

void SetFPS(int fps) {
    fps = std::max(1, fps);
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
        
        Log(ORIN_INFO, (std::string("Loaded texture [") + filePath + "]").c_str());
        
        return { static_cast<int>(texture), width, height };
    } else {
        Log(ORIN_ERROR, ("Failed to load texture: " + std::string(filePath)).c_str());
        return { 0 };
    }
}

void UnloadTexture(const Texture2D& texture) {
    GLuint id = static_cast<GLuint>(texture.id);
    glDeleteTextures(1, &id);
}

//Audio LoadAudio(const char* filePath) {
//    Audio audio = { 0, 0, 0, 0 };
//    
//    int channels;
//    int sampleRate;
//    short* samples = nullptr;
//    
//    std::filesystem::path sourcePath = std::filesystem::path(__FILE__).parent_path();
//    std::filesystem::path audioPath = sourcePath / filePath;
//    std::string audioFilePath = audioPath.string();
//    
//    int sampleCount = stb_vorbis_decode_filename(audioFilePath.c_str(), &channels, &sampleRate, &samples);
//    if (sampleCount == -1) {
//        Log(ORIN_ERROR, ("Failed to load audio: " + std::string(filePath)).c_str());
//        return audio;
//    }
//    
//    alGenBuffers(1, &audio.buffer);
//    alBufferData(audio.buffer, (channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16, samples, sampleCount * sizeof(short), sampleRate);
//    free(samples);
//    
//    alGenSources(1, &audio.source);
//    alSourcei(audio.source, AL_BUFFER, audio.buffer);
//    
//    Log(ORIN_INFO, ("Loaded audio [" + std::string(filePath) + "]").c_str());
//    return audio;
//}
//
//void PlayAudio(const Audio& audio) {
//    alSourcePlay(audio.source);
//}
//
//void UnloadAudio(const Audio& audio) {
//    alDeleteBuffers(1, &audio.buffer);
//    alDeleteSources(1, &audio.source);
//}

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

float Vector2Dot(const Vector2& v1, const Vector2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

Vector2 Vector2Add(const Vector2& v1, const Vector2& v2) {
    float xx = v1.x + v2.x;
    float yy = v1.y + v2.y;
    return { xx, yy };
}

Vector2 Vector2Sub(const Vector2& v1, const Vector2& v2) {
    float xx = v1.x - v2.x;
    float yy = v1.y - v2.y;
    return { xx, yy };
}

Vector2 Vector2Mul(const Vector2& v1, const Vector2& v2) {
    float xx = v1.x * v2.x;
    float yy = v1.y * v2.y;
    return { xx, yy };
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

float Vector3Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3Add(const Vector3& v1, const Vector3& v2) {
    float xx = v1.x + v2.x;
    float yy = v1.y + v2.y;
    float zz = v1.z + v2.z;
    return { xx, yy, zz };
}

Vector3 Vector3Sub(const Vector3& v1, const Vector3& v2) {
    float xx = v1.x - v2.x;
    float yy = v1.y - v2.y;
    float zz = v1.z - v2.z;
    return { xx, yy, zz };
}

Vector3 Vector3Mul(const Vector3& v1, const Vector3& v2) {
    float xx = v1.x * v2.x;
    float yy = v1.y * v2.y;
    float zz = v1.z * v2.z;
    return { xx, yy, zz };
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

float Vector4Dot(const Vector4& v1, const Vector4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Vector4 Vector4Add(const Vector4& v1, const Vector4& v2) {
    float xx = v1.x + v2.x;
    float yy = v1.y + v2.y;
    float zz = v1.z + v2.z;
    float ww = v1.w + v2.w;
    return { xx, yy, zz, ww };
}

Vector4 Vector4Sub(const Vector4& v1, const Vector4& v2) {
    float xx = v1.x - v2.x;
    float yy = v1.y - v2.y;
    float zz = v1.z - v2.z;
    float ww = v1.w - v2.w;
    return { xx, yy, zz, ww };
}

Vector4 Vector4Mul(const Vector4& v1, const Vector4& v2) {
    float xx = v1.x * v2.x;
    float yy = v1.y * v2.y;
    float zz = v1.z * v2.z;
    float ww = v1.w * v2.w;
    return { xx, yy, zz, ww };
}

bool RectIntersects(const Rectangle& r1, const Rectangle& r2) {
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

bool PointInRect(const Rectangle& rect, float x, float y) {
    return (x >= rect.x && x <= rect.x + rect.width &&
            y >= rect.y && y <= rect.y + rect.height);
}

bool PointInBoundingBox(const BoundingBox& box, const Vector3& point) {
    return (point.x >= box.min.x && point.x <= box.max.x) &&
           (point.y >= box.min.y && point.y <= box.max.y) &&
           (point.z >= box.min.z && point.z <= box.max.z);
}

bool BoundingBoxIntersects(const BoundingBox& box1, const BoundingBox& box2) {
    return (box1.max.x >= box2.min.x && box1.min.x <= box2.max.x) &&
           (box1.max.y >= box2.min.y && box1.min.y <= box2.max.y) &&
           (box1.max.z >= box2.min.z && box1.min.z <= box2.max.z);
}

bool IsRectangleInViewport(const Rectangle& rect) {
    float viewportWidth = GetViewportWidth();
    float viewportHeight = GetViewportHeight();
    
    float viewLeft = camera.position.x - viewportWidth;
    float viewRight = camera.position.x + viewportWidth;
    float viewTop = camera.position.y - viewportHeight;
    float viewBottom = camera.position.y + viewportHeight;
    
    return !(rect.x + rect.width < viewLeft ||
            rect.x > viewRight ||
            rect.y + rect.height < viewTop ||
            rect.y > viewBottom);
}

bool IsBoundingBoxInViewport(const BoundingBox& box) {
    float viewportWidth = GetViewportWidth();
    float viewportHeight = GetViewportHeight();
    
    float viewLeft = camera.position.x - viewportWidth;
    float viewRight = camera.position.x + viewportWidth;
    float viewTop = camera.position.y - viewportHeight;
    float viewBottom = camera.position.y + viewportHeight;
    
    return !(box.max.x < viewLeft ||
             box.min.x > viewRight ||
             box.max.y < viewTop ||
             box.min.y > viewBottom);
}

int Random(const int min, const int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

float Random(const float min, const float max) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

int Clamp(const int value, const int min, const int max) {
    return value < min ? min : (value > max ? max : value);
}

float Clamp(const float value, const float min, const float max) {
    return value < min ? min : (value > max ? max : value);
}

void DisableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mouseGrabbed = true;
}

void EnableCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    mouseGrabbed = false;
}
