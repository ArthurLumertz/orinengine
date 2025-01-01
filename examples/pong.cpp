/*
  Orin Framework © 2025
  Pong Example
*/

#include "orin.hpp"

// Paddle and ball rectangles
Rectangle paddle1;
Rectangle paddle2;
Rectangle ball;

// Ball velocity vector
Vector2 ballVelocity;

// Player scores
int player1Points = 0;
int player2Points = 0;

// Game state flag
bool running = false;

// Initializes the game objects and state
void init() {
  // Initialize paddles at their starting positions
  paddle1 = { 16, (GetViewportHeight() - 64) / 2, 8, 64 };
  paddle2 = { GetViewportWidth() - 16, (GetViewportHeight() - 64) / 2, 8, 64 };

  // Initialize ball at the center of the viewport
  ball = { (GetViewportWidth() - 16) / 2, (GetViewportHeight() - 16) / 2, 16, 16 };

  // Generate random initial ball velocity
  float randomX = Random(0.0f, 1.0f);
  float randomY = Random(0.3f, 0.7f);
  ballVelocity = { randomX, randomY };
}

// Resets the game state to its initial configuration
void resetGame() {
  // Reset ball position to center
  ball = { (GetViewportWidth() - 16) / 2, (GetViewportHeight() - 16) / 2, 16, 16 };

  // Generate new random ball velocity
  float randomX = Random(0.0f, 1.0f);
  float randomY = Random(0.3f, 0.7f);
  ballVelocity = { randomX, randomY };

  // Pause the game until input resumes
  running = false;
}

// Updates the game logic based on user input and elapsed time
void update(float delta) {
  // Handle player 1 input (Up and Down keys)
  if (IsKeyDown(KEY_UP)) {
      paddle1.y += GetDeltaTime() * 500.0f; // Move paddle up
      running = true; // Start game if not running
  }
  if (IsKeyDown(KEY_DOWN)) {
      paddle1.y -= GetDeltaTime() * 500.0f; // Move paddle down
      running = true; // Start game if not running
  }

  // If the game is not running, do nothing
  if (!running) {
      return;
  }

  // Clamp paddle positions within the viewport boundaries
  paddle1.y = Clamp(paddle1.y, 0.0f, GetViewportHeight() - 64);
  paddle2.y = Clamp(paddle2.y, 0.0f, GetViewportHeight() - 64);

  // Normalize ball velocity to maintain consistent speed
  Vector2Normalize(ballVelocity);

  // Update ball position based on velocity and delta time
  ball.x += ballVelocity.x * GetDeltaTime() * 500.0f;
  ball.y += ballVelocity.y * GetDeltaTime() * 500.0f;

  // AI logic for paddle 2 (opponent paddle)
  if (ball.x > GetViewportWidth() / 2) {
      // Follow the ball when it's on paddle 2's side
      float desiredY = ball.y - (paddle2.height / 2.0f);
      paddle2.y = std::lerp(paddle2.y, desiredY, 0.03f);
  } else {
      // Return to the center when the ball is on the opposite side
      paddle2.y = std::lerp(paddle2.y, (GetViewportHeight() - 64) / 2, 0.01f);
  }

  // Check for collisions between paddles and ball
  if (RectIntersects(paddle1, ball)) {
      ballVelocity.x = std::abs(ballVelocity.x); // Reflect ball in positive X direction
  }
  if (RectIntersects(paddle2, ball)) {
      ballVelocity.x = -std::abs(ballVelocity.x); // Reflect ball in negative X direction
  }

  // Check if ball goes out of bounds
  if (ball.x <= ball.width / 4) {
      player2Points++; // Award a point to player 2
      resetGame(); // Reset game state
  }
  if (ball.x >= GetViewportWidth() - ball.width) {
      player1Points++; // Award a point to player 1
      resetGame(); // Reset game state
  }

  // Check for ball collisions with top and bottom of the viewport
  if (ball.y <= ball.height / 4) {
      ballVelocity.y = std::abs(ballVelocity.y); // Reflect ball downward
  }
  if (ball.y >= GetViewportHeight() - ball.height) {
      ballVelocity.y = -std::abs(ballVelocity.y); // Reflect ball upward
  }
}

// Renders all game objects to the screen
void render() {
  ClearBackground(BLACK); // Clear the screen with black color

  // Draw paddles and ball
  DrawRectangle(paddle1.x, paddle1.y, paddle1.width, paddle1.height);
  DrawRectangle(paddle2.x, paddle2.y, paddle2.width, paddle2.height);
  DrawRectangle(ball.x, ball.y, ball.width, ball.height);
}

// Cleans up resources when the game ends
void dispose() {
  // No resources to clean up in this example
}

// Entry point of the program
int main() {
  InitWindow(960, 540, "Pong"); // Initialize the window

  init(); // Initialize game objects

  // Main game loop
  while (!WindowShouldClose()) {
      update(GetDeltaTime()); // Update game logic

      BeginDrawing();
      render(); // Render game objects
      EndDrawing();

      UpdateWindow(); // Update window contents
  }

  dispose(); // Dispose of resources

  CloseWindow(); // Close the game window

  return 0; // Exit program
}
