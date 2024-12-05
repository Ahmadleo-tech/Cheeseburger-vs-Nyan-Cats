///////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _kbhit and _getch on Windows
#include "G.h"
using namespace std;

// ANSI Color Codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

int main() {
    int choice;
    Game g1;

    do {
        system("cls");
        menu(g1);
        cout << " \n " << GREEN << "Enter Choice: " << RESET;
        cin >> choice;

        try {
            if (choice <= 0) {
                throw "Choice Cannot be Smaller or Equal To Zero!";
            }
            else {
                switch (choice) {
                case 1: {
                    string n = " ";
                    int m = 0;
                    cout << YELLOW << "Enter Player Name: " << RESET;
                    cin >> n;
                    cout << YELLOW << "Enter Mode of Game (0 for Nyan Cat (Easy), 1 for Nyan Cat (Medium), 2 for Nyan Cat (Hard)): " << RESET;
                    cin >> m;
                    g1.start(m);
                    break; // Return to menu after the game ends
                }
                case 2: {
                    cout << CYAN << "Here Are The Instructions:" << RESET << endl;
                    cout << YELLOW << "=== How to Play Cheeseburger & Nyan Cat ===\n\n" << RESET;
                    cout << GREEN << "Objective: " << RESET << "Collect power-ups, avoid obstacles, and score as many points as possible.\n\n";
                    cout << GREEN << "Controls:\n" << RESET;
                    cout << " - Use arrow keys to move the Cheeseburger (Up : w, Down : s, Left : a, Right : d , Pause : p).\n";
                    cout << " - Press 'P' to pause or resume the game.\n";
                    cout << " - Press 'Esc' to exit the game.\n\n";
                    cout << GREEN << "Gameplay Tips:\n" << RESET;
                    cout << " - Power-Ups: Collect Shield, Speed Boost, or Score Multiplier for advantages.\n";
                    cout << " - Avoid Obstacles: Dodge incoming Nyan Cats to save your lives.\n";
                    cout << " - Levels: Progress to higher levels by scoring points; each level increases difficulty.\n";
                    cout << " - Lives: You start with 3 lives. Colliding with a Nyan Cat reduces your life count.\n\n";
                    cout << GREEN << "End of Game:\n" << RESET;
                    cout << " - Game ends when you lose all lives.\n";
                    cout << " - Check your final score and level reached on the Game Over screen.\n";
                    cout << " - Play again to beat your high score!\n";
                    system("pause");
                    break;
                }
                case 3: {
                    ScoreManager scoreManager;
                    scoreManager.readScores();
                    scoreManager.displayScores();
                    system("pause");
                    break;
                }
                case 4: {
                    cout << MAGENTA << "===================================================" << RESET << endl;
                    cout << BLUE << "   OOP project by AHMAD  & NAEEM UL REHMAN" << RESET << endl;
                    cout << MAGENTA << "===================================================" << RESET << endl;
                    system("pause");
                    break;
                }
                case 5: {
                    cout << RED << "Exiting . . . !" << RESET << endl;
                    system("pause");
                    break;
                }
                default: {
                    cout << RED << "Invalid Input!" << RESET << endl;
                    system("pause");
                    break;
                }
                }
            }
        }
        catch (const char* e) {
            cout << RED << "Exception: " << e << RESET << endl;
            system("pause");
        }
    } while (choice != 5);

    return 0;
}
