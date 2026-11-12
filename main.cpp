#include "raylib.h"
#include <cmath>

int main() {

    InitWindow(800, 600, "Satellite Simulation");
    SetTargetFPS(60);

    //Satellite Globals
    float angle = 0.0f;
    float radius = 150.0f;

    while(!WindowShouldClose()) {
    
        BeginDrawing();

        ClearBackground(BLACK);
        //Movement
        angle += 0.02f;

        float satX = 400 + cos(angle) * radius;
        float satY = 300 + sin(angle) * radius;

        //Earth
        DrawCircle(400, 300, 50, BLUE);
        //Satellite
        DrawCircle(satX, satY, 10, WHITE);


        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}