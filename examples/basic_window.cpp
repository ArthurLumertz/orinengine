/*
  Orin Framework © 2025
  Basic window example
*/
#include "orin.hpp"

int main() {
  // Creates the window constants for the size
  const int screenWidth = 960;
  const int screenHeight = 540;
  
  // Initialize the window width the parameters (width, height, title)
  InitWindow(screenWidth, screenHeight, "Window Example");

  // While the window shouldn't close
  while (!WindowShouldClose()) {
    // Clear the background with black
    ClearBackground(BLACK);

    // Begin drawing mode
    BeginDrawing();
    {
      // Draw a basic rectangle at pos(0, 0), size(48, 48) pixels
      DrawRectangle(0.0f, 0.0f, 48.0f, 48.0f);
    }
    // End drawing mode
    EndDrawing();

    // Updates the window (run the game loop)
    UpdateWindow();
  }

  // Closes the window when the loop is exited
  CloseWindow();
  
  return 0;
}
