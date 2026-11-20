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
double orbitalSP = 0.2f;

int main() {

    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        //Declarations
        angle += orbitalSP;
        double satX = 400 * cos(angle) * radius;
        double satY = 500 * sin(angle) * radius;
        

        BeginDrawing();
        ClearBackground(BLACK);

        //Earth
        DrawCircle(400, 300, 50, BLUE);

        //Satellite
        DrawCircle(satX, satY, 10, WHITE);

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