#include <iostream>
#include <raylib.h>
#include <vector>

using namespace std;
    
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
const int BALL_SIZE = 15;
const int PADDLE_WIDTH = 25;
const int PADDLE_HEIGHT = 120;
const Color PADDLE_COLOR = WHITE;


float convertX(float u) {
    // -1..1 => 0..2 => 0..1 => 0..x
    return ((u + 1) / 2) * SCREEN_WIDTH;
}

float convertY(float u) {
    // -1..1 => 0..2 => 0..1 => 0..y
    return (1-((u + 1) / 2)) * SCREEN_HEIGHT;
}

class Ball {
public:
    float x, y;
    float speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y >= GetScreenHeight() - radius || y <= radius) {
            speed_y *= -1;
        }
        if (x >= GetScreenWidth() - radius || x <= radius) {
            speed_x *= -1;
        }
    }
};

class Player {
public:
    float x, y;
    int width, height;

    void Draw() {
        DrawRectangle(x, y-height/2, width, height, PADDLE_COLOR);
    }
};

int main () {
    cout << "Pong" << endl;

    Ball ball;
    ball.radius = BALL_SIZE;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.x = convertX(0);
    ball.y = convertY(0);

    Player p1, p2;
    p1.width = PADDLE_WIDTH, p2.width = PADDLE_WIDTH;
    p1.height = PADDLE_HEIGHT, p2.height = PADDLE_HEIGHT;
    p1.x = convertX(-0.85), p1.y = convertY(0);
    p2.x = convertX(0.85),  p2.y = convertY(0);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60); 

    while(!WindowShouldClose()) {

        BeginDrawing();

        // Update
        ball.Update();

        // Drawing
        ClearBackground(BLACK);
        DrawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT, SCREEN_WIDTH/2, 0, DARKGRAY);

        ball.Draw();
        p1.Draw();
        p2.Draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}