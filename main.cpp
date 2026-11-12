#include "raylib.h"
#include <cmath>
#include <vector>

using namespace std;

int main() {

    InitWindow(800, 600, "Satellite Simulation");
    SetTargetFPS(60);

    //Satellite Globals
    float angle = 0.0f;
    float radius = 150.0f;
    int oneFullOrbit = 0;

    vector<Vector2> trail;

    while(!WindowShouldClose()) {
        
        BeginDrawing();

        ClearBackground(BLACK);
        //Text
        DrawText(TextFormat("Orbits: %d", oneFullOrbit), 10, 10, 20, WHITE);

        
        //Movement
        angle += 0.02f;
        if (angle >= 2 * PI) {
            oneFullOrbit++;
            angle = 0.0f;
        }

        float satX = 400 + cos(angle) * radius;
        float satY = 300 + sin(angle) * radius;
        trail.push_back({satX, satY});

        

        //Earth
        DrawCircle(400, 300, 50, BLUE);

        //Trail of the Satellite
        for (size_t x = 0; x < trail.size(); x++) {
            DrawCircleV(trail[x], 2, Fade(WHITE, 0.5f));
        }

        if (trail.size() > 200) {
        trail.erase(trail.begin());

        }

        //Satellite
        DrawCircle(satX, satY, 10, WHITE);

        
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}