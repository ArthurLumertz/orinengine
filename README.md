# Orin - C++ Game Framework

A C++ game framework built with OpenGL.

Similar to LibGDX, RayLib, and MonoGame, Orin provides a simple and effective way to build games using OpenGL.

## Setup

To set up Orin, follow these steps:

1. Download the files inside the `./src` directory.
2. Add the files to your project's directory.

After that, create a `main.cpp` file and start using Orin as shown below.

## Basic Example

This example demonstrates how to open a window, render basic graphics, create a camera, and load/unload textures.

> Keep in mind, this library is still in its development stage, and several performance improvements will be coming in 2025!

```cpp
#include "orin.hpp"

int main() {
    // Initializes a basic window with the title "First Application"
    InitWindow(960, 540, "First Application");

    // Create and set up a basic camera (position and zoom)
    Camera2D camera;
    camera.position = { 0.0f, 0.0f };
    camera.zoom = 1.0f;

    // Load a basic texture from an image file
    Texture2D texture = LoadTexture("image.png");

    // Game loop: Run until the user closes the window
    while (!WindowShouldClose()) {
        ClearBackground(WHITE); // Clear the screen with a white background
        
        BeginDrawing(); // Begin rendering

        SetColor(BLACK); // Set the rendering color to black
        // Draw a black rectangle at position (0, 0) with size 48x48
        DrawRectangle(0.0f, 0.0f, 48.0f, 48.0f);

        // Draw a black rectangle rotated 45 degrees at position (0, 48)
        DrawRectangle(0.0f, 48.0f, 48.0f, 48.0f, 45.0f);

        SetColor(WHITE); // Set the rendering color to white before drawing the texture
        // Draw the texture at position (48, 0) with size 48x48
        DrawTexture(texture, 48.0f, 0.0f, 48.0f, 48.0f);
        
        EndDrawing(); // End rendering

        // Update the window
        UpdateWindow();
    }

    // Unloads the texture loaded previously
    UnloadTexture(texture);

    // Closes the window
    CloseWindow();

    return 0;
}
