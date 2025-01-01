/*
  Orin Framework © 2025
  Basic math example
*/
#include "orin.hpp"

int main() {
  // Creates the window constants for the size
  const int screenWidth = 960;
  const int screenHeight = 540;
  
  // Initialize the window width the parameters (width, height, title)
  InitWindow(screenWidth, screenHeight, "Window Example");

  // Creates the initial position
  Vector2 position = { 0.0f, 0.0f };
  
  // Creates the initial velocity
  Vector2 velocity = { 0.0f, 0.0f };

  // Assign the speed
  float speed = 5.0f;

  // While the window shouldn't close
  while (!WindowShouldClose()) {
    // Clear the background with black
    ClearBackground(BLACK);

    // Check if the 'W' key is pressed
    if (IsKeyDown(KEY_W)) {
        velocity.y++;  // Increase the Y velocity
    }
    // Check if the 'S' key is pressed
    if (IsKeyDown(KEY_S)) {
        velocity.y--;  // Decrease the Y velocity
    }
    // Check if the 'A' key is pressed
    if (IsKeyDown(KEY_A)) {
        velocity.x--;  // Decrease the X velocity
    }  
    // Check if the 'D' key is pressed
    if (IsKeyDown(KEY_D)) {
        velocity.x++;  // Increase the X velocity
    }

    // Normalize the velocity
    Vector2Normalize(velocity);

    // Adds the position from (velocity * deltaTime * speed)
    position.x += velocity.x * GetDeltaTime() * speed;
    position.y += velocity.y * GetDeltaTime() * speed;
    
    // Begin drawing mode
    BeginDrawing();
    {
      // Draw a basic rectangle at pos(0, 0), size(48, 48) pixels
      DrawRectangle(position.x, position.y, 48.0f, 48.0f);
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
