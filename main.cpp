#include "raylib.h"
#include <cmath>
#include <vector>

using namespace std;

// --- PHYSICS CONSTANTS ---
float G = 100.0f;
float earthMass = 500.0f;
float moonMass = 30.0f; 

// --- EARTH ---
float earthX = 400.0f;
float earthY = 300.0f;
float earthRadius = 50.0f;

// --- SATELLITE ---
float satX = 400.0f;
float satY = 150.0f;
float orbitalVx = 18.0f; 
float orbitalVy = 0.0f;
bool isCrashed = false; 
float speedMultiplier = 1.0f; // Used for UP/DOWN keys

// --- MOON ---
float moonX = 200.0f;
float moonY = 300.0f;
float moonVx = 0.0f;
float moonVy = -15.8f; 

// --- TRAIL ---
vector<Vector2> trail;

int main() {
    InitWindow(800, 600, "MythicGraph's Satellite Simulation");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f; 

        // ==========================================
        // 1. CONTROLS
        // ==========================================
        
        // Click to teleport satellite (Instantly calculates a stable orbit)
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            satX = GetMouseX();
            satY = GetMouseY();
            isCrashed = false; 
            trail.clear();
            speedMultiplier = 1.0f; // Reset speed multiplier on click

            float angleToMouse = atan2(satY - earthY, satX - earthX);
            float distToMouse = sqrt((earthX - satX)*(earthX - satX) + (earthY - satY)*(earthY - satY));

            if (distToMouse > earthRadius) { // Prevent divide by zero if clicked inside Earth
                float orbitSpeed = sqrt((G * earthMass) / distToMouse);
                orbitalVx = orbitSpeed * -sin(angleToMouse);
                orbitalVy = orbitSpeed * cos(angleToMouse);
            }
        }

        // Speed up / Slow down
        if (!isCrashed) {
            if (IsKeyDown(KEY_UP)) {
                speedMultiplier += 0.05f; // Constantly increase speed while held
            }
            if (IsKeyDown(KEY_DOWN)) {
                speedMultiplier -= 0.05f; // Constantly decrease speed while held
            }
        }
        
        // Press '0' to stop entirely
        if (IsKeyPressed(KEY_ZERO)) {
            orbitalVx = 0.0f;
            orbitalVy = 0.0f;
        }

        // ==========================================
        // 2. FORCE CALCULATIONS
        // ==========================================
        if (!isCrashed) {
            // A. Earth pulls Satellite
            float dxE = earthX - satX;
            float dyE = earthY - satY;
            float distE = sqrt(dxE * dxE + dyE * dyE);
            float accX_E = 0, accY_E = 0;

            if (distE > 10.0f) {
                float forceE = (G * earthMass) / (distE * distE);
                accX_E = forceE * (dxE / distE);
                accY_E = forceE * (dyE / distE);
            }

            // B. Moon pulls Satellite
            float dxM = moonX - satX;
            float dyM = moonY - satY;
            float distM = sqrt(dxM * dxM + dyM * dyM);
            float accX_M = 0, accY_M = 0;

            if (distM > 10.0f) {
                float forceM = (G * moonMass) / (distM * distM);
                accX_M = forceM * (dxM / distM);
                accY_M = forceM * (dyM / distM);
            }

            // C. Earth pulls Moon
            float dxMoonE = earthX - moonX;
            float dyMoonE = earthY - moonY;
            float distMoonE = sqrt(dxMoonE * dxMoonE + dyMoonE * dyMoonE);
            float accMoonX = 0, accMoonY = 0;

            if (distMoonE > 10.0f) {
                float forceMoonE = (G * earthMass) / (distMoonE * distMoonE);
                accMoonX = forceMoonE * (dxMoonE / distMoonE);
                accMoonY = forceMoonE * (dyMoonE / distMoonE);
            }

            // ==========================================
            // 3. UPDATE VELOCITIES & POSITIONS
            // ==========================================
            
            // Apply gravity + speed multiplier to the satellite
            orbitalVx += ((accX_E + accX_M) * dt * speedMultiplier);
            orbitalVy += ((accY_E + accY_M) * dt * speedMultiplier);

            satX += orbitalVx * dt;
            satY += orbitalVy * dt;

            moonVx += accMoonX * dt;
            moonVy += accMoonY * dt;

            moonX += moonVx * dt;
            moonY += moonVy * dt;

            // ==========================================
            // 4. TRAIL & COLLISION
            // ==========================================
            
            trail.push_back({satX, satY});
            if (trail.size() > 300) {
                trail.erase(trail.begin());
            }

            // Collision detection
            if (distE <= (earthRadius + 5.0f) || distM <= (15.0f + 5.0f)) {
                isCrashed = true;
            }
        }

        // ==========================================
        // 5. DRAWING
        // ==========================================
        BeginDrawing();
        ClearBackground(BLACK);

        // Trail
        for (size_t i = 0; i < trail.size(); i++) {
            DrawCircleV(trail[i], 2, Fade(WHITE, 0.5f));
        }

        // Earth & Moon
        DrawCircle(earthX, earthY, earthRadius, BLUE);
        DrawCircle(moonX, moonY, 15, LIGHTGRAY);

        // Satellite
        if (isCrashed) {
            DrawCircle(satX, satY, 8, RED);
            DrawText("CRASHED!", 340, 280, 30, RED);
        } else {
            float satAngle = atan2(orbitalVy, orbitalVx) * RAD2DEG;
            DrawPoly({satX, satY}, 3, 10.0f, satAngle + 90.0f, WHITE);
        }

        // Telemetry Text
        float totalSpeed = sqrt(orbitalVx*orbitalVx + orbitalVy*orbitalVy);
        DrawText(TextFormat("Speed: %.1f | Multiplier: %.2fx", totalSpeed, speedMultiplier), 10, 10, 20, GREEN);
        DrawText("CLICK: Teleport & Orbit | UP/DOWN: Speed | 0: Stop", 10, 560, 20, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}