#include <raylib.h>
#include <iostream>
#include "simulation.hpp"

int main () {
    
    Color BACKGROUND = {29, 29, 29, 255};
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1070;
    const int CELL_SIZE = 20;
    int FPS = 12;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of Life");
    SetTargetFPS(FPS);
    Simulation simulation{WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE};

    //  Simulation Loop

    while(WindowShouldClose() == false)
    {
        //  1. Event Handling
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouseposition = GetMousePosition();
            int row = mouseposition.y / CELL_SIZE;
            int column = mouseposition.x / CELL_SIZE;
            simulation.ToggleCell(row, column);
        }

        if(IsKeyPressed(KEY_ENTER))
        {
            simulation.Start();
            SetWindowTitle("Game of Life is running...");
        }
        else if(IsKeyPressed(KEY_SPACE))
        {
            simulation.Stop();
            SetWindowTitle("Game of Life has stopped...");
        }
        else if(IsKeyPressed(KEY_UP))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if(IsKeyPressed(KEY_DOWN))
        {
            if(FPS > 5)
            {
                FPS -= 2;
                SetTargetFPS(FPS);
            }
        }
        else if(IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }

        //  2. Updating State
        simulation.Update();

        //  3. Drawing
        BeginDrawing();
        ClearBackground(BACKGROUND);
        simulation.Draw();
        EndDrawing();
    }

    CloseWindow();
}