# Satellite Simulation Project

This project measures and shows the movement of an artificial satellite. Its orbital movement displays its stats (its velocity and its acceleration) from the Earth.

![Alt text](C:\Users\MythicGraphArchives\OneDrive\Desktop\Satallite Raylib\MythicGraphsSatellite\sat1.png)

-----------------------------------------------
## Update1

So far so, the project can simulate real world physics, the orbit around the Earth depending on its velocity you choose in the source code and displays the vector direction the satellite is moving in.

Features planned to add:
1. Control the initial starting position of the satellite.

2. Moon's natural gravitational force and its affect on the satellite

## BIG UPDATE 2
Several updates have been added and now you can "control the initial starting position of the satellite" and "moon's natural gravitational force now affects the orbit of the satellite".

### Bugs Fixed:
1. Math and Physics bug which casued expanding orbit slowly driving the satellite in a spiral and crashing with the moon.
2. The broken moon gravity causing a sudden movement in the position of moon.
3. Mass was being divided by distance before multiplying with G.
4. A "ghost radius" which caused the satellite to crash when close to the moon.
5. In order to increase velocity, you needed to both click the mouse and press up and down simultaneously.
6. Escape velocity by clicking up 3 times would increase V by 500% causing the satellite to escape the orbit.

### Added Featues
1. Real Newtonian Gravity instead of a forced orbit.
2. Natural Satellite's addition (The Moon) which affects the artificial satellite.
3. Click to orbit feature. Now just click on the screen to teleport the satellite!
4. Speed Control (UP and DOWN) to increase velocity
5. Pressing 0 kills velocity causing freefall motion.
6. Directional Triangle repersents satellite instead of a circle.
7. Velocity vector shows the direction of the satellite (n̂) 
8. Crash Detection. DONT crash the satellite Please!

---------------------------------------------------
## Update 3
-yet to add "control the moon feature"

