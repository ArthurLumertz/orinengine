<h1>Orin</h1>
<p>C++ game framework made in OpenGL.</p>
<p>Similar to LibGDX, RayLib and MonoGame.</p>
<h3>Setup</h3>
<p>To setup, download the files inside ./src and add them to the project's directory.</p>
<p>After this, create a main file and start using Orin:</p>
<br>
<h3>Basic example</h3>
<p>This example shows you how to open a window and render basic graphics on it. It shows how to create a camera and load/unload textures.</p>
<p>Keep in mind this library is in its development stage! Several new performance updates will be coming in 2025.</p>

```cpp
#include "orin.hpp"

int main() {
  // Initializes a basic window
  InitWindow(960, 540, "Hello world");

  // Create a camera Camera(position, zoom)
  Camera2D camera(Vector2{ 0.0f, 0.0f }, 0.0f);

  // Load a basic texture
  Texture2D texture = LoadTexture("image.png");

  // While the window shouldn't close
  while (!WindowShouldClose()) {
    ClearBackground(WHITE); // Clear the background with white color
    
    BeginDrawing(); // Begin rendering
    SetColor(BLACK); // Sets the rendering color to black

    // Draw a basic rectangle at the position 0, 0 with the size of 48, 48
    DrawRectangle(0, 0, 48, 48);

    SetColor(WHITE); // Sets the rendering color to white before drawing texture
    // Draws the texture at the position 48, 0, with the size of 48, 48
    DrawTexture(texture, 48, 0, 48, 48);
    
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
