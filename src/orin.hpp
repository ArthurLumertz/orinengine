#pragma once

#include <iostream>

#define ORIN_VERSION      "0.0.8a"
#define ORIN_MAJOR              0
#define ORIN_MINOR              5

#define ORIN_TRUE             0x1
#define ORIN_FALSE            0x0

#define ORIN_ERROR            0x0
#define ORIN_WARNING          0x1
#define ORIN_FATAL            0x2
#define ORIN_SUCCESS          0x3
#define ORIN_INFO             0x4

#define KEY_SPACE              32
#define KEY_APOSTROPHE         39
#define KEY_COMMA              44
#define KEY_MINUS              45
#define KEY_PERIOD             46
#define KEY_SLASH              47
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59
#define KEY_EQUAL              61
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91
#define KEY_BACKSLASH          92
#define KEY_RIGHT_BRACKET      93
#define KEY_GRAVE_ACCENT       96
#define KEY_WORLD_1            161
#define KEY_WORLD_2            162
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348
#define KEY_LAST               KEY_MENU

#define BUTTON_1         0
#define BUTTON_2         1
#define BUTTON_3         2
#define BUTTON_4         3
#define BUTTON_5         4
#define BUTTON_6         5
#define BUTTON_7         6
#define BUTTON_8         7
#define BUTTON_LAST      BUTTON_8
#define BUTTON_LEFT      BUTTON_1
#define BUTTON_RIGHT     BUTTON_2
#define BUTTON_MIDDLE    BUTTON_3

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

typedef struct {
    Vector3 min;
    Vector3 max;
} BoundingBox;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} Region;

typedef struct {
    float r;
    float g;
    float b;
    float a;
} Color;

typedef struct {
    Vector2 position;
    //Vector2 target;
    float zoom;
} Camera2D;

typedef struct {
    int id;
    int width;
    int height;
} Texture2D;

//typedef struct {
//    unsigned int buffer;
//    unsigned int source;
//    int format;
//    int frequency;
//} Audio;

#define WHITE (Color{ 1.0f, 1.0f, 1.0f, 1.0f })
#define BLACK (Color{ 0.0f, 0.0f, 0.0f, 1.0f })
#define GRAY (Color{ 0.5f, 0.5f, 0.5f, 1.0f })
#define LIGHT_GRAY (Color{ 0.75f, 0.75f, 0.75f, 1.0f })
#define DARK_GRAY (Color{ 0.25f, 0.25f, 0.25f, 1.0f })

#define RED (Color{ 1.0f, 0.0f, 0.0f, 1.0f })
#define GREEN (Color{ 0.0f, 1.0f, 0.0f, 1.0f })
#define BLUE (Color{ 0.0f, 0.0f, 1.0f, 1.0f })
#define YELLOW (Color{ 1.0f, 1.0f, 0.0f, 1.0f })
#define CYAN (Color{ 0.0f, 1.0f, 1.0f, 1.0f })
#define MAGENTA (Color{ 1.0f, 0.0f, 1.0f, 1.0f })

#define ORANGE (Color{ 1.0f, 0.5f, 0.0f, 1.0f })
#define PURPLE (Color{ 0.5f, 0.0f, 0.5f, 1.0f })
#define BROWN (Color{ 0.6f, 0.3f, 0.0f, 1.0f })
#define PINK (Color{ 1.0f, 0.75f, 0.8f, 1.0f })
#define LIME (Color{ 0.75f, 1.0f, 0.0f, 1.0f })

#define TRANSPARENT (Color{ 0.0f, 0.0f, 0.0f, 0.0f })

bool InitWindow(const int width, const int height, const char* title);
void UpdateWindow();
bool WindowShouldClose();
void CloseWindow();

Texture2D LoadTexture(const char* filePath);
void UnloadTexture(const Texture2D& texture);

//Audio LoadAudio(const char* filePath);
//void PlayAudio(const Audio& audio);
//void UnloadAudio(const Audio& audio);

void SetFPS(int fps);
void UseVSync(const int& sync);

void SetWindowSize(const int width, const int height);
void SetWindowTitle(const char* title);

void ClearBackground(float r, float g, float b, float a);
void ClearBackground(const Color& color);

void SetCamera(const Camera2D& camera);

void SetColor(float r, float g, float b, float a);
void SetColor(const Color& color);

void BeginDrawing();
void EndDrawing();

void DrawRectangle(float x, float y, float width, float height);
void DrawRectangle(float x, float y, float width, float height, float degrees);

void DrawTexture(Texture2D& texture, float x, float y, float width, float height);
void DrawTexture(Texture2D& texture, float x, float y, float width, float height, float degrees);

void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height);
void DrawTexturePro(Texture2D& texture, Region& subTexture, float x, float y, float width, float height, float degrees);

int GetWindowWidth();
int GetWindowHeight();

float GetViewportWidth();
float GetViewportHeight();

bool IsKeyDown(const int& key);
bool IsKeyPressed(const int& key);
bool IsMouseDown(const int& button);
bool IsMousePressed(const int& button);

int GetMouseX();
int GetMouseY();
Vector2 GetMousePosition();

float GetMouseDX();
float GetMouseDY();
Vector2 GetMouseDelta();

float GetTime();
float GetElapsedTime();
float GetDeltaTime();

int GetFPS();

void Log(int mode, const char* str);
std::vector<std::string>& GetLog();

float Vector2Length(const Vector2& v);
void Vector2Normalize(Vector2& v);
float Vector2Distance(const Vector2& v1, const Vector2& v2);
float Vector2Dot(const Vector2& v1, const Vector2& v2);
Vector2 Vector2Add(const Vector2& v1, const Vector2& v2);
Vector2 Vector2Sub(const Vector2& v1, const Vector2& v2);
Vector2 Vector2Mul(const Vector2& v1, const Vector2& v2);

float Vector3Length(const Vector3& v);
void Vector3Normalize(Vector3& v);
float Vector3Distance(const Vector3& v1, const Vector3& v2);
float Vector3Dot(const Vector3& v1, const Vector3& v2);
Vector3 Vector3Add(const Vector3& v1, const Vector3& v2);
Vector3 Vector3Sub(const Vector3& v1, const Vector3& v2);
Vector3 Vector3Mul(const Vector3& v1, const Vector3& v2);

float Vector4Length(const Vector4& v);
void Vector4Normalize(Vector4& v);
float Vector4Distance(const Vector4& v1, const Vector4& v2);
float Vector4Dot(const Vector4& v1, const Vector4& v2);
Vector4 Vector4Add(const Vector4& v1, const Vector4& v2);
Vector4 Vector4Sub(const Vector4& v1, const Vector4& v2);
Vector4 Vector4Mul(const Vector4& v1, const Vector4& v2);

bool RectIntersects(const Rectangle& r1, const Rectangle& r2);
bool PointInRect(const Rectangle& rect, float x, float y);

bool PointInBoundingBox(const BoundingBox& box, const Vector3& point);
bool BoundingBoxIntersects(const BoundingBox& box1, const BoundingBox& box2);

bool IsRectangleInViewport(const Rectangle& rect);
bool IsBoundingBoxInViewport(const BoundingBox& bb);

long long GetNanoTime();
long long GetCurrentTimeMillis();

int Random(const int min, const int max);
float Random(const float min, const float max);
bool RandomBool();

int Clamp(const int value, const int min, const int max);
float Clamp(const float value, const float min, const float max);

void DisableCursor();
void EnableCursor();

bool FileExists(const char* fileName);
bool DirectoryExists(const char* dirPath);
bool CreateDirectory(const char* dirPath);
bool DeleteFile(const char* fileName);
bool DeleteDirectory(const char* dirPath);
uint64_t GetFileSize(const char* filePath);
std::string GetCurrentWorkingDirectory();
std::vector<std::string> ListFilesInDirectory(const char* dirPath);

void WriteTextFile(const char* filePath, const std::string& content);
std::string ReadTextFile(const char* filePath);
