#include<iostream>
#include "raylib.h"
#include<cmath>
#include<vector>

using namespace std;


//Globals
// double satSpeedX = 2.0f;
// double satSpeedY = 2.0f;

// double angle = 0.0f;
// double radius = 150.0f;
// double orbitalSP = 0.05f;

float G = 5000.0f;
float earthX = 400.0f;
float earthY = 300.0f;

float satX = 400.0f;
float satY = 500.0f;
float velocityX = 5.0f;
float velocityY = 2.0f;
float accelerationX = 0.0f;
float accelerationY = 0.0f;

//Trail
vector<Vector2> trail;


int main() {

    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {

        float dt = GetFrameTime();

        // angle += orbitalSP;
        // float satX = 400 + cos(angle) * radius;
        // float satY = 300 + sin(angle) * radius;

        float distanceX = earthX - satX;
        float distanceY = earthY - satY;
        float distance = sqrt(distanceX* distanceX + distanceY* distanceY);

        float force = G / (distance * distance);

        accelerationX = force * (distanceX / distance);
        accelerationY = force * (distanceY / distance);

        velocityX += accelerationX;
        velocityY += accelerationY;

        satX += velocityX;
        satY += velocityY;

        //Crash Collision
        if (distance <= 60) {
            velocityX = 0;
            velocityY = 0;
        }

        //Vector jas a direction
        DrawLine(satX, satY, satX + velocityX* 20, satY + velocityY* 20, RED);

        //kinetic energy
        float kineticEnergy = 0.5f* (velocityX* velocityX* + velocityY* velocityY);
        DrawText(TextFormat("Kinetic Energy: %.2f", kineticEnergy), 10, 100, 20, WHITE);
        
        //Trail
        trail.push_back({satX, satY});
        if (trail.size() > 200) {
            trail.erase(trail.begin());
            // cout << "Trail has reverted" << endl;
        }


        //Text
        DrawText(TextFormat("Distance from Earth: %.2f", distance), 10, 10, 20, WHITE);
        DrawText(TextFormat("Velocity X: %.2f", velocityX), 10, 40, 20, WHITE);
        DrawText(TextFormat("Velocity Y: %.2f", velocityY), 10, 70, 20, WHITE);

        //Future Path
        float futureX = satX;
        float futureY = satY;
        float futureVelocityX = velocityX;
        float futureVelocityY = velocityY;


        for (int x = 0; x < 100; ++x) {
        DrawCircle(futureX, futureY, 1, Fade(GREEN, 0.3f));
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