#include <iostream>
#include <raylib.h>

using namespace std;

int main () {
    cout << "Pong" << endl;
    
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 800;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");

    CloseWindow();

    return 0;
}