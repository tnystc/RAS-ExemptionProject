#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"
#include "actors.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// Global Variables Definition
const int screenWidth = 1080;
const int screenHeight = 720;
const float midX = screenWidth / 2;
const float midY = screenHeight / 2;

// Module Functions Declaration
void UpdateDrawFrame(List* CircleList, float deltaT, Camera2D *camera);
void DrawCircles(List *CircleList);
void DrawLines(List *CircleList);
void SetCamera(Camera2D *camera);
Color RandColor();

// Main Entry Point
int main()
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "suffering from metu");
    printf("Init Window Success\n");

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    SetTargetFPS(60); 

    //Create list and add dummy node
    List *CircleList = malloc(sizeof(List));
    CircleList->head = NULL;
    CircleList->tail = NULL;
    addCircle(CircleList, createCircle(1, (Vector2){0, 0}, 0, 0, BLACK));

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Drag and zoom functionality
        SetCamera(&camera);

        // Add a circle on 'A' key press
        if (IsKeyPressed(KEY_A)) {

            //assign random values (i might get user input but for now this is fine)
            float radius = GetRandomValue(10, 20);
            float lineLength = GetRandomValue(30, 60);
            float angularSpeed = GetRandomValue(10, 50) / 10.0f;
            float randomAngle = GetRandomValue(0, 2*PI);
            
            Vector2 parentPosition = CircleList->tail->position;

            CircleNode *newCircle = createCircle(radius, parentPosition, lineLength, angularSpeed, RandColor());
            addCircle(CircleList, newCircle);
        }

        // Remove a circle on 'D' key press
        if (IsKeyPressed(KEY_D)) {
            removeCircle(CircleList);
        }

    
        UpdateDrawFrame(CircleList, GetFrameTime(), &camera);
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}


// Module Functions Definition
void UpdateDrawFrame(List* CircleList, float deltaT, Camera2D *camera)
{
    // Update
    CircleNode *current = CircleList->head->next;
    Vector2 parentPosition = CircleList->head->position;

    while (current) {
        current->angle += current->angularSpeed * deltaT;
        current->position = (Vector2){parentPosition.x + current->lineLength*cos(current->angle), parentPosition.y + current->lineLength*sin(current->angle)};
        parentPosition = current->position;
        current = current->next;
    }


    // Draw
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(*camera);

            DrawLines(CircleList);
            DrawCircles(CircleList);

        EndMode2D();

        // Draw each control description
        DrawText("Left Mouse Button: Drag to move camera", 10, 20, 18, DARKGRAY);
        DrawText("Mouse Wheel: Zoom", 10, 40, 18, DARKGRAY);
        DrawText("A: Add Circle", 10, 60, 18, DARKGRAY);
        DrawText("D: Delete Circle", 10, 80, 18, DARKGRAY);
        DrawText("ESC: Quit", 10, 100, 18, DARKGRAY);

    EndDrawing();
    
}

void DrawCircles(List *CircleList) {

    CircleNode *current = CircleList->head;

    while (current) {
        float currentX = midX + current->position.x;
        float currentY = midY + current->position.y;

        DrawCircle(currentX, currentY, current->radius, current->color);
        DrawCircle(currentX, currentY, 2, BLACK);

        current = current->next;
    }
}

void DrawLines(List *CircleList) {
    CircleNode *current = CircleList->head;
    float prevX = midX + current->position.x;
    float prevY = midY + current->position.y;

    while (current) {
        float currentX = midX + current->position.x;
        float currentY = midY + current->position.y;

        if (current != CircleList->head) {
            DrawLine(prevX, prevY, currentX, currentY, BLACK);
        }

        prevX = currentX;
        prevY = currentY;

        current = current->next;
    }
}

void SetCamera(Camera2D *camera)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera->zoom);
        camera->target = Vector2Add(camera->target, delta);
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Get the world point that is under the mouse
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *camera);

        // Set the offset to where the mouse is
        camera->offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point 
        // under the cursor to the screen space point under the cursor at any zoom
        camera->target = mouseWorldPos;

        // Zoom increment
        float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
        if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
        camera->zoom = Clamp(camera->zoom*scaleFactor, 0.125f, 64.0f);
    }
}

Color RandColor()
{
    int i = rand() % 6;
    switch (i)
    {
    case 0:
        return RED;
    case 1:
        return GREEN;
    case 2:
        return BLUE;
    case 3:
        return YELLOW;
    case 4:
        return ORANGE;
    case 5:
        return PURPLE;
    default:
        return BLACK;
    }
}
