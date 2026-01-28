#include "methods.h"
#include "structs.h"

#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

int score;

Level l1;
Level l2;
Level l3;

int main()
{
    // level 1 design
    {
        Pig p1;
        Wall w1;
        p1.Length = 90;
        p1.Height = 20;
        w1.Position = 90;
        w1.Height = 5;
        l1.pigs.push_back(p1);
        l1.walls.push_back(w1);
    }

    // level 2 design
    {
        Pig p1;
        Pig p2;
        Wall w1;
        Wall w2;
        p1.Length = 70;
        p1.Height = 20;
        p2.Length = 95;
        p2.Height = 15;
        w1.Position = 70;
        w1.Height = 5;
        w2.Position = 95;
        w2.Height = 10;
        l2.pigs.push_back(p1);
        l2.pigs.push_back(p2);
        l2.walls.push_back(w1);
        l2.walls.push_back(w2);
    }

    // level 3 design
    {
        Pig p1;
        Pig p2;
        Pig p3;
        Wall w1;
        Wall w2;
        p1.Length = 50;
        p1.Height = 18;
        p2.Length = 75;
        p2.Height = 25;
        p3.Length = 90;
        p3.Height = 22;
        w1.Position = 50;
        w1.Height = 7;
        w2.Position = 90;
        w2.Height = 3;
        l3.pigs.push_back(p1);
        l3.pigs.push_back(p2);
        l3.pigs.push_back(p3);
        l3.walls.push_back(w1);
        l3.walls.push_back(w2);
    }

    system("mkdir saves");
    string user = "";
    bool isRunning = true;
    bool authorize;
    int menuChoice;
    int selectLevel;
    while (isRunning)
    {
        authorize = !user.empty();
        score = l1.stars + l2.stars + l3.stars;
        system("color 7");
        system("cls");
        cout << "===========================================" << endl;
        cout << "               CONSOLE GAME" << endl;
        cout << "===========================================" << endl;
        if (authorize)
        {
            cout << "User: " << user << endl;
        }
        cout << "Level 1 .......... Stars: " << l1.stars << "/3" << endl;
        cout << "Level 2 .......... Stars: " << l2.stars << "/3" << endl;
        cout << "Level 3 .......... Stars: " << l3.stars << "/3" << endl;
        cout << "Total Score: " << score << endl;
        cout << endl;
        if (!l1.isFinished)
        {
            cout << "1) Start" << endl;
        }
        else if (l3.isFinished)
        {
            cout << "1) Select Level" << endl;
        }
        else
        {
            cout << "1) Continue" << endl;
        }
        cout << "2) Save Progress" << endl;
        cout << "3) Reset Progress" << endl;
        if (!authorize)
        {
            cout << "4) Log in" << endl;
        }
        else
        {
            cout << "4) Log out" << endl;
        }
        cout << "5) How to Play" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter your choice: ";

        cin >> menuChoice;
        switch (menuChoice)
        {
        case 1: // Start Game
            if (!l1.isFinished)
            {
                StartLevel(l1);
                RestartLevel(l1);
            }
            else if (l1.isFinished && !l2.isFinished)
            {
                StartLevel(l2);
                RestartLevel(l2);
            }
            else if (l1.isFinished && l2.isFinished && !l3.isFinished)
            {
                StartLevel(l3);
                RestartLevel(l3);
            }
            else
            {
                system("cls");
                cout << "=== SELECT LEVEL ===" << endl;
                cout << " 1) Level 1" << endl;
                cout << " 2) Level 2" << endl;
                cout << " 3) Level 3" << endl;
                cout << " 0) Go Back" << endl;
                cout << "Enter your choice: ";
                cin >> selectLevel;

                switch (selectLevel)
                {
                case 1:
                    StartLevel(l1);
                    break;

                case 2:
                    StartLevel(l2);
                    break;

                case 3:
                    StartLevel(l3);
                    break;

                default:
                    break;
                }
            }

            break;

        case 2: // Save Progress
        {
            string message;
            if (authorize)
            {
                fstream file("saves/" + user + ".txt", ios::out);
                file << l1.stars << endl;
                file << l2.stars << endl;
                file << l3.stars << endl;
                message = "Your progress has been saved!";
            }
            else
            {
                message = "You need to log in first!";
            }

            ShowMessage(message);
            break;
        }

        case 3: // Reset Progress
            system("cls");
            l1.isFinished = false;
            l2.isFinished = false;
            l3.isFinished = false;
            RestartLevel(l1);
            RestartLevel(l2);
            RestartLevel(l3);
            l1.stars = 0;
            l2.stars = 0;
            l3.stars = 0;
            score = 0;
            ShowMessage("Your progress has been successfully reset!");
            break;

        case 4: // Sign in
        {
            string message;
            if (!authorize)
            {
                system("cls");
                string userName;
                cout << "Enter username: ";
                cin >> userName;
                fstream file("saves/" + userName + ".txt", ios::in);
                string s1, s2, s3;
                getline(file, s1);
                getline(file, s2);
                getline(file, s3);
                if (!s1.empty() && !s2.empty() && !s3.empty())
                {
                    message = "Welcome back " + userName + "!";
                    l1.stars = stoi(s1);
                    l2.stars = stoi(s2);
                    l3.stars = stoi(s3);
                    l1.isFinished = (stoi(s1) > 0) ? 1 : 0;
                    l2.isFinished = (stoi(s2) > 0) ? 1 : 0;
                    l3.isFinished = (stoi(s3) > 0) ? 1 : 0;
                }
                else
                {
                    message = "Welcome " + userName + "!";
                }
                user = userName;
            }
            else
            {
                message = "See you " + user + "!";
                user = "";
                l1.stars = 0;
                l2.stars = 0;
                l3.stars = 0;
                l1.isFinished = false;
                l2.isFinished = false;
                l3.isFinished = false;
            }
            ShowMessage(message);
            break;
        }

        case 5: // Show Help
            system("cls");
            cout << "How to Play:" << endl;
            cout << "1. Enter the game." << endl;
            cout << "2. You are given 3 seconds to have a quick scan over the map." << endl;
            cout << "3. Inputs are Power and Angle." << endl;
            cout << "4. After you entered the inputs hit Enter." << endl;
            cout << "5. If you hit the pig, NICE! and if you did not, don't be worry you have 5 chances." << endl;
            cout << "Note: This is just a game, ENJOY IT!" << endl;
            cout << endl;
            system("pause");
            break;

        case 0: // Exit
            isRunning = false;
            system("cls");
            cout << "Thanks for playing!" << endl;
            Sleep(3000);

            break;

        default:
            break;
        }
    }

    return 0;
}