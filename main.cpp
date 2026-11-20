#include<iostream>
#include "raylib.h"
#include<cmath>
#include<vector>

using namespace std;


//Globals
double satSpeedX = 2.0f;
double satSpeedY = 2.0f;

double angle = 0.0f;
double radius = 150.0f;
double orbitalSP = 0.05f;

//Trail
vector<Vector2> trail;


int main() {

    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        //Declarations
        angle += orbitalSP;
        float satX = 400 + cos(angle) * radius;
        float satY = 300 + sin(angle) * radius;
        
        //Trail
        trail.push_back({satX, satY});

        if (trail.size() > 200) {
            trail.erase(trail.begin());
            // cout << "Trail has reverted" << endl;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        //Earth
        DrawCircle(400, 300, 50, BLUE);

        //Satellite
        DrawCircle(satX, satY, 10, WHITE);
        
        //Trail Movement
        for (size_t x = 0; x < trail.size(); ++x) {
            DrawCircleV(trail[x], 2, Fade(WHITE, 0.5f));
        }
        // for (size_t x = 1; x < trail.size(); ++x) {
        //     float thickness = (float)x / trail.size() * 5.0f;
        //     DrawLineEx(trail[x - 1], trail[x], thickness, WHITE);
        //     cout << "Trail is in progress" << endl;

        //Movement
        //satX += satSpeedX;
        //satY += satSpeedY;

        // if (satX >= 800 || satX <= 0) {
        //     satSpeedX = satSpeedX * -1;
        // }
        // if (satY >= 600 || satY <= 0) {
        //     satSpeedY = satSpeedY * -1;
        // }


        EndDrawing();
    }

    CloseWindow();

}