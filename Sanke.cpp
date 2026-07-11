#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
using namespace std;

//Declaring all the variables and functions which will be used in the game

const int widht = 30;
const int HEIGHT = 20;

enum Direction { STOP, LEFT, RIGHT, UP, DOWN };

bool gameOver;
Direction dir;

int headX, headY;
int tailX[100], tailY[100];
int tailLen;

int fruitX, fruitY;
int score;

void Setup() {
    gameOver = false;
    dir = STOP;
    headX = widht / 2;
    headY = HEIGHT / 2;
    score = 0;
    tailLen = 0;
    srand((unsigned)time(0));
    fruitX = rand() % widht;
    fruitY = rand() % HEIGHT;
}

void Draw() {
    system("cls");

    for (int i = 0; i < widht + 2; i++) cout << "|";
    cout << "\n";

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < widht; x++) {
            if (x == 0) cout << "|";

            if (x == headX && y == headY)
                cout << "O";
            else if (x == fruitX && y == fruitY)
                cout << "#";
            else {
                bool printTail = false;
                for (int k = 0; k < tailLen; k++) {
                    if (tailX[k] == x && tailY[k] == y) {
                        cout << "o";
                        printTail = true;
                        break;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (x == widht - 1) cout << "|";
        }
        cout << "\n";
    }

    for (int i = 0; i < widht + 2; i++) cout << "|";
    cout << "\n";
    cout << "Score: " << score << "\n";
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT;  break;
            case 'd': if (dir != LEFT)  dir = RIGHT; break;
            case 'w': if (dir != DOWN)  dir = UP;    break;
            case 's': if (dir != UP)    dir = DOWN;  break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailLen; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:  headX--; break;
        case RIGHT: headX++; break;
        case UP:    headY--; break;
        case DOWN:  headY++; break;
        default: break;
    }

    if (headX >= widht || headX < 0 || headY >= HEIGHT || headY < 0)
        gameOver = true;

    for (int i = 0; i < tailLen; i++) {
        if (tailX[i] == headX && tailY[i] == headY)
            gameOver = true;
    }

    if (headX == fruitX && headY == fruitY) {
        score += 10;
        tailLen++;
        fruitX = rand() % widht;
        fruitY = rand() % HEIGHT;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(80);
    }
    cout << "\nGame  Over! Final Score: " << score << "\n";
    return 0;
}