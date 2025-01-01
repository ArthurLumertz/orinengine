/*
  Orin Framework © 2025
  Texture example
*/
#include "orin.hpp"

int main() {
  // Creates the window constants for the size
  const int screenWidth = 960;
  const int screenHeight = 540;
  
  // Initialize the window width the parameters (width, height, title)
  InitWindow(screenWidth, screenHeight, "Window Example");

  // Load a 2d texture from the corresponding file path
  // Supports png, jpg, gif, bmp, tga, hdr
  Texture2D texture = LoadTexture("image.png");

  // While the window shouldn't close
  while (!WindowShouldClose()) {
    // Clear the background with black
    ClearBackground(BLACK);

    // Begin drawing mode
    BeginDrawing();
    {
      // Draw the texture at pos(0, 0), size(48, 48) pixels
      DrawTexture(texture, 0.0f, 0.0f, 48.0f, 48.0f);
    }
    // End drawing mode
    EndDrawing();

    // Updates the window (run the game loop)
    UpdateWindow();
  }

  // Unloads the texture from memory
  UnloadTexture(texture);

  // Closes the window when the loop is exited
  CloseWindow();
  
  return 0;
}
