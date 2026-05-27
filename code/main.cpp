#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 20;   
const int HEIGHT = 20;  

int x, y;               
int fruitX, fruitY;     
int score;              
int tailX[100], tailY[100]; 
int nTail;              
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; 
eDirection dir;         
bool gameOver;          

void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    srand(time(0));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
}

void Draw() {
    system("cls");
    
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";
            
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            
            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
    cout << "Controls: WASD to move | X to quit" << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;  
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void Logic() {
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

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
           break;
        default:
            break;
    }
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
        gameOver = true;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++; 
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();  
        Input(); 
        Logic(); 
        Sleep(100); 
    }
    
    cout << endl << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    cout << "Press any key to exit..." << endl;
    _getch(); 
    return 0;
}
