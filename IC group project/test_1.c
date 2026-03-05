#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
//hello world 

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int x, y;              // Snake head position
int foodX, foodY;      // Food position
int score;

int tailX[100], tailY[100];
int nTail;

enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum Direction dir;

// 1️⃣ Initialize Game
void Setup() {
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
}

// 2️⃣ Draw Game Board
void Draw() {

    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {

            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O");
            else if (i == foodY && j == foodX)
                printf("F");
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o");
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");

    printf("\nScore: %d\n", score);
}

// 3️⃣ Take Input
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = 1; break;
        }
    }
}

// 4️⃣ Update Logic
void Logic() {

    // Move Tail
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move Head
    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Wall Collision
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        gameOver = 1;

    // Self Collision
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    // Food Collision
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        nTail++;
    }
}

// 5️⃣ Main Function
int main() {

    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);   // Speed control
    }

    printf("Game Over! Final Score: %d\n", score);

    return 0;

}
