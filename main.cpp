#include<iostream>
#include<vector>
#include "raylib.h"

using namespace std;

//Globals
float satX = 400;
float satY = 500;

float satSpeedX = 2;
float satSpeedY = 2;

int main() {

    InitWindow(800, 600, "Satellite Simulation");
    SetTargetFPS(60);

 
    while (!WindowShouldClose()) {
        
        
        
        BeginDrawing();

        //Satellite
        DrawCircle(satX, satY, 10, WHITE);
        //Earth 
        DrawCircle(400, 300, 50, BLUE;

        //Movement
        satX = satX + satSpeedX;
        satY = satY + satSpeedY;
        
                // Bounce off left and right walls
        if (satX <= 0) {
            satX = 0;
            satSpeedX = satSpeedX * -1; 
        }
        if (satX >= 800) {
            satX = 800;
            satSpeedX = satSpeedX * -1; 
        }

        // Bounce off top and bottom walls
        if (satY <= 0) {
            satY = 0;
            satSpeedY = satSpeedY * -1;
        }
        if (satY >= 600) {
            satY = 600;
            satSpeedY = satSpeedY * -1;
        }
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}