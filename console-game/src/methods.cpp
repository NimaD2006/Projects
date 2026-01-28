#include "methods.h"
#include "constants.h"

#include <iostream>
#include <string>
#include <cmath>
#include <Windows.h>
using namespace std;

void gotoxy(short int x, short int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x, y};
    SetConsoleCursorPosition(h, c);
}

// Loads the given level and its entities
void LoadLevel(Level level)
{
    // Show entities
    system("cls");
    gotoxy(5, 25);
    cout << BowSymbol;
    // Loads walls
    for (Wall wall : level.walls)
    {
        for (size_t i = 25; i > 25 - wall.Height; i--)
        {
            gotoxy(wall.Position, i);
            cout << WallSymbol;
        }
    }
    // Loads alive pigs
    for (Pig pig : level.pigs)
    {
        if (pig.isAlive)
        {
            gotoxy(pig.Length, pig.Height);
            cout << PigSymbol;
        }
    }
}

// Starts the given level
void StartLevel(Level &level)
{
    // Declared static for better efficiency
    static int power;
    static float angle;
    static float x, y;
    static bool obstacleHit = false;
    static bool hit;
    bool win = false;
    int globalCounter;
    for (int i = 0; i <= 4; i++) // Checks the rule "ONLY 5 CHANCES"
    {
        if (i != 4)
        {
            globalCounter = i - 1;
        }
        else
        {
            globalCounter = i;
        }
        // Checks if the level is finished or not. (If any pig is remained or not)
        level.isFinished = true;
        hit = false;
        for (Pig &pig : level.pigs)
        {
            if (pig.isAlive)
            {
                level.isFinished = false;
                break;
            }
        }

        if (!level.isFinished)
        {
            // Initializes each Throw
            x = 6;
            y = 24;
            obstacleHit = false;
            LoadLevel(level);
            gotoxy(x, y);
            cout << BirdSymbol;
            Sleep(3000); // How much time is given before each throw
            system("cls");
            { // Reading input values for each parameter. (Power & Angle)
                cout << "Chances left: " << 5 - i << endl;
                cout << endl;
                cout << "Enter Power: ";
                cin >> power;
                cout << "Enter Angle: ";
                cin >> angle;
                angle = (float)PI * angle / 180.0;
            }
            for (int j = 0; j < 16; j++) // Checks number of moves
            {
                if (!obstacleHit & !hit)
                {
                    Sleep(250);
                    LoadLevel(level);
                    gotoxy(x, y);
                    cout << BirdSymbol;
                    for (Pig &pig : level.pigs)
                    {
                        // Checks if the bird hit any pig
                        if (x < pig.Length + 3 && x > pig.Length - 3 && ((int)y == pig.Height || (int)y == pig.Height - 1 || (int)y == pig.Height + 1) && pig.isAlive)
                        {
                            pig.isAlive = false;
                            hit = true;
                            system("cls");
                            system("color 6");
                            Sleep(500);
                            gotoxy(55, 14);
                            cout << "DIRECT";
                            Sleep(500);
                            gotoxy(61, 15);
                            cout << "HIT!";
                            Sleep(700);
                            system("cls");
                            win = true;
                            for (Pig p : level.pigs)
                            {
                                if (p.isAlive)
                                {
                                    win = false;
                                }
                            }
                            break;
                        }
                        for (Wall wall : level.walls)
                        {
                            for (size_t k = 25; k > 25 - wall.Height; k--)
                            {
                                if (x < wall.Position + 3 && x > wall.Position - 3 && ((int)y < 25 && (int)y > 25 - wall.Height))
                                {
                                    obstacleHit = true;
                                    break;
                                }
                            }
                        }
                    }
                    system("color 7");
                    // Computes new coordinations
                    ComputeXY(x, y, j, power, angle);
                    // Checks if the bird has leaved the grid or not
                    if (x > 100 || y > 25)
                    {
                        break;
                    }
                    if (obstacleHit)
                    {
                        system("cls");
                        cout << "You hit an obstacle!";
                        Sleep(2000);
                        break;
                    }
                }
            }
            continue;
        }
        break;
    }
    if (!level.isFinished && !win)
    {
        // Looser Scripts
        system("cls");
        system("color 4");
        cout << "YOU LOST!" << endl;
        RestartLevel(level);
        system("pause");
    }
    else
    {
        // Winner Scripts
        string message;
        level.isFinished = true;
        system("cls");
        cout << "YOU WON!" << endl;
        if (globalCounter <= 2)
        {
            level.stars = 3;
            message = "Perfect!";
        }
        else if (globalCounter == 3)
        {
            level.stars = 2;
            message = "Good";
        }
        else if (globalCounter == 4)
        {
            level.stars = 1;
            message = "Not Bad";
        }
        for (int i = 0; i < level.stars; i++)
        {
            Sleep(500);
            cout << "* ";
            if (i > 1)
            {
                system("color 6");
            }
        }
        cout << endl;
        cout << message;
        cout << endl;
        system("pause");
    }
}

void RestartLevel(Level &level)
{
    for (Pig &pig : level.pigs)
    {
        pig.isAlive = true;
    }
}

void ComputeXY(float &x, float &y, int step, int power, float angle)
{
    if (step <= 5)
    {
        x = x + (float)(power * cos(angle) * 0.2);
        y = y - (float)(power * sin(angle) * 0.2);
    }
    else
    {
        x = x + (float)(power * cos(angle) * 0.2);
        y = y + (float)(power * sin(angle) * 0.2);
    }
}

void ShowMessage(string message)
{
    system("cls");
    system("color 6");
    cout << message;
    Sleep(3000);
    system("cls");
    system("color 7");
}