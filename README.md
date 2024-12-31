<h1>Orin Framework</h1>
<p>C++ game framework made in OpenGL.</p>
<p>Similar to LibGDX, RayLib and MonoGame.</p>
<br>
<h3>Setup</h3>
<p>To setup, download the files inside ./src and add them to the project's directory.</p>
<p>After this, create a main file and start using Orin:</p>
<br>
<code>
#include "orin.hpp"

int main() {
  // Initializes a basic window
  InitWindow(960, 540, "Hello world");

  // Create a camera Camera(position, zoom)
  Camera2D camera(Vector2{ 0.0f, 0.0f }, 0.0f);

  // While the window shouldn't close
  while (!WindowShouldClose()) {
    ClearBackground(WHITE); // Clear the background with white color
    
    BeginDrawing(); // Begin rendering
    SetColor(BLACK); // Sets the rendering color to black

    // Draw a basic rectangle at the position 0, 0 with the size of 48, 48
    DrawRectangle(0, 0, 48, 48);
    
    EndDrawing(); // End rendering

    // Update the window
    UpdateWindow();
  }

  // Closes the window
  CloseWindow();

  return 0;
}
</code>
