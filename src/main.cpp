#include "simulation.h"
#include <raylib.h>
#include <raymath.h>

void handleInput(Camera2D& cam) {

   if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 delta = GetMouseDelta();

      delta = Vector2Scale(delta, -1.0f / cam.zoom);

      cam.target = Vector2Add(cam.target, delta);
   }

   Vector2 render_scale{static_cast<float>(GetRenderWidth()) / GetScreenWidth(),
                        static_cast<float>(GetRenderHeight()) / GetScreenHeight()};

   float wheel_delta = GetMouseWheelMove();
   if (wheel_delta != 0.0f) {

      Vector2 mouse_world = GetScreenToWorld2D(GetMousePosition(), cam);

      cam.offset = Vector2Multiply(GetMousePosition(), render_scale);

      cam.target = mouse_world;

      float scale = 0.2 * wheel_delta;

      cam.zoom = Clamp(expf(logf(cam.zoom) + scale), 0.125f, 64.0f);
   }
}


void drawCell(Vector2 coords, const Cell& c) {

   
      const float cell_size = 1.0f;

      coords = Vector2Scale(coords, cell_size);
      
      Vector2 next_x = Vector2Add(coords, Vector2{cell_size, 0.0f});
      Vector2 next_y = Vector2Add(coords, Vector2{0.0f, cell_size});
      Vector2 next_xy = Vector2Add(coords, Vector2{cell_size, cell_size});
      
      DrawLineV(coords, next_x, LIGHTGRAY);
      DrawLineV(coords, next_y, LIGHTGRAY);
      DrawLineV(next_x, next_xy, LIGHTGRAY);
      DrawLineV(next_y, next_xy, LIGHTGRAY);
   
}

int main(void) {
   Simulation sim{100, 200};

   const int screen_width = 1080;
   const int screen_height = 720;

   InitWindow(screen_width, screen_height, "raylib example - basic window");

   Camera2D cam{
       // Vector2{static_cast<float>(screen_width)/2, static_cast<float>(screen_height)/2},
       .offset = Vector2{0.0f, 0.0f},  // where camera target/origin is in the screen
       .target = Vector2{30.0f, 0.0f}, // camera target in world space

       .rotation = 0.0f,
       .zoom = 1.0f,
   };

   bool should_zoom = false;

   while (!WindowShouldClose()) {

      // Handle input
      handleInput(cam);

      // Draw

      BeginDrawing();

      ClearBackground(RAYWHITE);

      BeginMode2D(cam);

      Vector2 grid_origin{0.0, 0.0};
      Vector2 delta_x{1.0, 0.0};
      Vector2 delta_y{0.0, 1.0};


      for (auto [i, j] : sim.indices()) {

         Vector2 coords{static_cast<float>(i), static_cast<float>(j)};

         drawCell(coords, sim.viewCell(i, j));

      }

      EndMode2D();

      DrawText(
          TextFormat("You have a simulation of size %d x %d", sim.height, sim.width),
          190, 300, 20, BLUE);

      EndDrawing();
   }

   CloseWindow();

   return 0;
}
