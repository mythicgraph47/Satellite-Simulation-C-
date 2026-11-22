#include "raylib.h"
#include<cmath>
#include<vector>

using namespace std;

//Declarations
double satX = 400.0f;
double satY = 500.0f;

int main() {
    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //Earth
        DrawCircle(400, 300, 50, BLUE);

        //Satellite
        DrawCircle(satX, satY, 10, WHITE);


        EndDrawing();
    }
    CloseWindow();
    return 0;
}