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

    void Update(pair<int, int>& score) {
        x += speed_x;
        y += speed_y;

        if (y >= GetScreenHeight() - radius || y <= radius) {
            speed_y *= -1;
        }
        if (x >= GetScreenWidth() - radius || x <= radius) {
            speed_x *= -1;
        }

        if (x >= GetScreenWidth() - radius) {
            score.first++;
            Reset();
        }
        if (x <= radius) {
            score.second++;
            Reset();
        }
    }

    void Reset() {
        x = convertX(0);
        y = convertY(0);

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Player {
public:
    float x, y;
    float width, height;
    int speed;
    KeyboardKey up_key, down_key;

    void Draw() {
        DrawRectangle(x, y, width, height, PADDLE_COLOR);
    }

    void Update() {
        if (IsKeyDown(up_key)) {
            y -= speed;
        }
        if (IsKeyDown(down_key)) {
            y += speed;
        }

        BoundsCheck();
    }

protected:
    void BoundsCheck() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
};

class CpuPlayer: public Player {
public:
    void Update(float ball_y) {
        if (y + height/2 > ball_y) {
            y -= speed;
        }
        if (y + height/2 <= ball_y) {
            y += speed;
        }

        BoundsCheck();
    }
};

Ball ball;
Player p1;
CpuPlayer p2;

int main () {
    cout << "Pong" << endl;

    ball.radius = BALL_SIZE;
    ball.speed_x = 7;
    ball.speed_y = 7;
    ball.x = convertX(0);
    ball.y = convertY(0);

    p1.width = PADDLE_WIDTH, p2.width = PADDLE_WIDTH;
    p1.height = PADDLE_HEIGHT, p2.height = PADDLE_HEIGHT;
    p1.x = convertX(-0.85), p1.y = convertY(0);
    p2.x = convertX(0.85),  p2.y = convertY(0);
    p1.speed = 6, p2.speed = 6;
    p1.up_key = KEY_UP, p1.down_key = KEY_DOWN;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60); 
    
    pair<int, int> score{0, 0};

    while(!WindowShouldClose()) {

        BeginDrawing();

        // Update
        ball.Update(score);
        p1.Update();
        p2.Update(ball.y);

        // Collision check
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p1.x, p1.y, p1.width, p1.height}))
        {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{p2.x, p2.y, p2.width, p2.height}))
        {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(BLACK);
        DrawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT, SCREEN_WIDTH/2, 0, DARKGRAY);
        DrawRectangle(0, 0, 20, SCREEN_HEIGHT, DARKGRAY);
        DrawRectangle(SCREEN_WIDTH-20, 0, 20, SCREEN_HEIGHT, DARKGRAY);
        DrawText(TextFormat("%i", score.first), convertX(-0.25), convertY(0.90), 80, GRAY);
        DrawText(TextFormat("%i", score.second), convertX(0.25) - 40, convertY(0.90), 80, GRAY);

        ball.Draw();
        p1.Draw();
        p2.Draw();


        EndDrawing();
    }

    CloseWindow();

    return 0;
}