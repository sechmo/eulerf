#include <raylib.h>
#include "simulation.h"

int main(void)
{
    Simulation sim{100, 200};

    
    InitWindow(800, 450, "raylib example - basic window");

    

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText(TextFormat("You have a simulatino of size %d x %d", sim.height, sim.width), 190, 200, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
