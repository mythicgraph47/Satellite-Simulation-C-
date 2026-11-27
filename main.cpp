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

float G = 100.0f;
float earthMass = 500.0f;
float earthX = 400.0f;
float earthY = 300.0f;

float satX = 400.0f;
float satY = 150.0f;
float velocityX = 18.0f;
float velocityY = 0.0f;
float accelerationX = 0.0f;
float accelerationY = 0.0f;


float moonX = 100.0f;
float moonY = 300.0f;
float moonMass = 20.0f;
float moonRadius = 20.0f;
float moonVelocityX = 0.0f;
float moonVelocityY = -12.7f;

//Trail
vector<Vector2> trail;


int main() {

    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    bool isCrashed = false;

    while(!WindowShouldClose()) {

        //time
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;

    //mouse click teleport
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        satX = GetMouseX();
        satY = GetMouseY();
        isCrashed = false;
        trail.clear();

        float angleToMouse = atan2(satY - earthY, satX - earthX);
        float distanceToMouse = sqrt((earthX - satX)* (earthX - satX) + (earthY - satY)* (earthY - satY));

        if (distanceToMouse > 50.0f) {
            float orbitSpeed = sqrt((G* earthMass) / distanceToMouse);
            velocityX = orbitSpeed* -sin(angleToMouse);
            velocityY = orbitSpeed* cos(angleToMouse);
        }
    }
        //speedup the satellite
        if (!isCrashed) {
            if (IsKeyDown(KEY_UP)) {
                velocityX *= 1.01f;
                velocityY *= 1.01f;
            }

            if (IsKeyDown(KEY_DOWN)) {
                velocityX *= 0.99f;
                velocityY *= 0.99f;
            }
        }

        //0 stop reset
        if (IsKeyPressed(KEY_ZERO)) {
            velocityX = 0.0f;
            velocityY = 0.0f;
            isCrashed = false;
        }
    
    

        BeginDrawing();
        ClearBackground(BLACK);

        // angle += orbitalSP;
        // float satX = 400 + cos(angle) * radius;
        // float satY = 300 + sin(angle) * radius;

        //earths pull on satellite
        float distanceX = earthX - satX;
        float distanceY = earthY - satY;
        float distance = sqrt(distanceX* distanceX + distanceY* distanceY);

        float force = (G* earthMass) / (distance * distance);

        accelerationX = force * (distanceX / distance);
        accelerationY = force * (distanceY / distance);

        
        //Crash Collision

        // if (distance <= 60) {
        //     velocityX = 0;
        //     velocityY = 0;
        // }

        //Moon
        float moonDistanceX = moonX - satX;
        float moonDistanceY = moonY - satY;
        float moonDistance = sqrt(moonDistanceX* moonDistanceX + moonDistanceY* moonDistanceY);

        if (moonDistance > 10.0f) {
            float moonForce = (G* moonMass) / (moonDistance* moonDistance);

            accelerationX += moonForce* (moonDistanceX / moonDistance);
            accelerationY += moonForce* (moonDistanceY / moonDistance);
        }

        if (distance <= 60.0f || moonDistance <= 30.0f) {
            isCrashed = true;
        }

        //Moon Mechanics
        float moonAroundEarthX = earthX - moonX;
        float moonAroundEarthY = earthY - moonY;
        float moonToEarthDist = sqrt(moonAroundEarthX* moonAroundEarthX + moonAroundEarthY* moonAroundEarthY);

        //Earths pull on moon
        float moonForce = (G* earthMass) / (moonToEarthDist* moonToEarthDist);
        moonVelocityX += moonForce* (moonAroundEarthX / moonToEarthDist);
        moonVelocityY += moonForce* (moonAroundEarthY / moonToEarthDist);

        if (!isCrashed) {
            velocityX += accelerationX* dt;
            velocityY += accelerationY* dt;

            satX += velocityX* dt;
            satY += velocityY* dt;
        }

        moonX += moonVelocityX;
        moonY += moonVelocityY;


        //Vector jas a direction
        DrawLine(satX, satY, satX + velocityX* 20, satY + velocityY* 20, RED);

        //kinetic energy
        float kineticEnergy = 0.5f* (velocityX* velocityX + velocityY* velocityY);
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

        DrawText("Click: Teleport | UP/DOWN: Speed | 0: Stop", 10, 560, 20, LIGHTGRAY);



        //Earth
        DrawCircle(400, 300, 50, BLUE);

        //Satellite
        // DrawCircle(satX, satY, 10, WHITE);
        if (isCrashed) {
            DrawCircle(satX, satY, 10, RED);
        } else {
            float satAngle = atan2(velocityY, velocityX) * RAD2DEG;
            DrawPoly({satX, satY}, 3, 10.0f, satAngle + 90.0f, WHITE);
        }

        //Moon
        DrawCircle(moonX, moonY, moonRadius, WHITE);
        
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
    return 0;
    
}


