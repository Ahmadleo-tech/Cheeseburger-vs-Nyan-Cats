/////////////////////////////////////////////////////////////////////////////////////////////////////
#include "G.h"
#include <fstream>
#include <thread>
#include<iostream>
#include <chrono>
#include <conio.h>
using namespace std;

// ============================= ScoreManager Class Methods =============================
ScoreManager::ScoreManager() {
    for (int i = 0; i < 5; i++) {
        scores[i] = 0;
    }
}

void ScoreManager::readScores() {
    ifstream file("scores.txt");
    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            file >> scores[i];
        }
        file.close();
    }
}

void ScoreManager::saveScore(int score) {
    readScores();
    for (int i = 0; i < 5; i++) {
        if (score > scores[i]) {
            for (int j = 4; j > i; j--) {
                scores[j] = scores[j - 1];
            }
            scores[i] = score;
            break;
        }
    }
    writeScores();
}

void ScoreManager::writeScores() {
    ofstream file("scores.txt");
    if (file.is_open()) {
        for (int i = 0; i < 5; i++) {
            file << scores[i] << endl;
        }
        file.close();
    }
}

void ScoreManager::displayScores() {
    cout << BLUE << "========================================" << RESET << endl;
    cout << GREEN << "Top 5 Scores" << RESET << endl;
    for (int i = 0; i < 5; i++) {
        cout << YELLOW << "Rank " << (i + 1) << ": " << scores[i] << RESET << endl;
    }
    cout << BLUE << "========================================" << RESET << endl;
}

// ============================= GameObject Class Methods =============================
GameObject::GameObject(int x, int y, string color) : x(x), y(y), color(color) {}

GameObject::~GameObject() {}

void GameObject::move(string direction) {
    if (direction == "left" && x > 0)
        x--;
    else if (direction == "right" && x < 9)
        x++;
    else if (direction == "up" && y > 0)
        y--;
    else if (direction == "down" && y < 9)
        y++;
}

int GameObject::getX() const { return x; }
int GameObject::getY() const { return y; }

// ============================= Cheeseburger Class Methods =============================
Cheeseburger::Cheeseburger(int x, int y) : GameObject(x, y, YELLOW), lives(3), score(0) {}

void Cheeseburger::move(string direction) {
    GameObject::move(direction);
}
void Cheeseburger::collide(GameObject* obj, int mode) {
    string objType = obj->getType();

    if (objType == "N" || objType == "S" || objType == "M") {
        lives -= (mode + 1);
        if (lives < 0) lives = 0;
        cout << RED << "Collision! Lives remaining: " << lives << RESET << endl;
    }
    else if (objType == "P" || objType == "B" || objType == "p") {
        if (objType == "P") {
            score += 15;
            lives += 1;
        }
        else if (objType == "B") {
            score += 50;
        }
        else if (objType == "p") {
            score += 10;
        }
        cout << GREEN << "Power-Up Collected! Score: " << score << " | Lives: " << lives << RESET << endl;
    }
    else {
        cout << YELLOW << "Unknown object encountered! No effect." << RESET << endl;
    }
}



string Cheeseburger::getType() const { return "Cheeseburger"; }
int Cheeseburger::getLives() const { return lives; }
int Cheeseburger::getScore() const { return score; }

// ============================= NyanCat Class Methods =============================
NyanCat::NyanCat(int x, int y) : GameObject(x, y, MAGENTA) {}


void NyanCat::moveDown() {
    y++;
    if (y >= 10) {
        y = 0;               // Reset y to 0
        x = rand() % 10;     // Generate a random x value between 0 and 9
    }
}

string NyanCat::getType() const {
    return "N";
}


// ============================= PowerUp Class Methods =============================
PowerUp::PowerUp(int x, int y, string powerType) : GameObject(x, y, BLUE), powerType(powerType) {}


void PowerUp::moveDown() {
    y++;
    if (y >= 10) {
        y = 0;               // Reset y to 0
        x = rand() % 10;     // Generate a random x value between 0 and 9
    }
}

string PowerUp::getType() const {
    return powerType;
}



// ============================= Game Class Methods =============================
Game::Game() : isGameOver(false) {
    player = new Cheeseburger(5, 9);
    srand(time(0));

    for (int i = 0; i < 5; i++) {
        nyanCats[i] = new NyanCat(rand() % 10, rand() % 10);
    }

    for (int i = 0; i < 4; i++) {
        int randType = rand() % 3; // Generates a number between 0 and 2
        string powerType = (randType == 0) ? "P" : (randType == 1 ? "B" : "p");
        powerUps[i] = new PowerUp(rand() % 10, rand() % 10, powerType);

        // Debugging output to check the generated power-up type
        cout << "Power-Up " << i << ": " << powerType << endl;
    }

}

Game::~Game() {
    delete player;
    for (int i = 0; i < 5; i++)
        delete nyanCats[i];
    for (int i = 0; i < 4; i++) delete powerUps[i];
}

void Game::start(int mode) {
    // Main game logic
    cout << "Welcome to Cheeseburger & NyanCat Game at Level " << mode + 1 << "!\n";
    int speed = 0;
    while (!isGameOver) {
        system("cls");
        // Clear screen
        //cout << "\033[2J\033[1;1H";

        // Create the grid
        char grid[10][10];
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                grid[i][j] = '.';

        // Place Cheeseburger on the grid
        grid[player->getY()][player->getX()] = 'C';

        // Move NyanCats and place them on the grid
        for (int i = 0; i < 5; i++) {
            nyanCats[i]->moveDown();
            if (mode == 0) {
                grid[nyanCats[i]->getY()][nyanCats[i]->getX()] = 'N';
            }
            else if (mode == 1) {
                grid[nyanCats[i]->getY()][nyanCats[i]->getX()] = 'S';
            }
            else if (mode == 2) {
                grid[nyanCats[i]->getY()][nyanCats[i]->getX()] = 'M';
            }
            else {
                grid[nyanCats[i]->getY()][nyanCats[i]->getX()] = '*';
            }
        }

        // Move PowerUps and place them on the grid

        for (int i = 0; i < 4; i++) {
            powerUps[i]->moveDown();
            string powerType = powerUps[i]->getType();
            if (powerType == "P") {
                grid[powerUps[i]->getY()][powerUps[i]->getX()] = 'P'; // Power-Up Type 1
            }
            else if (powerType == "B") {
                grid[powerUps[i]->getY()][powerUps[i]->getX()] = 'B'; // Power-Up Type 2
            }
            else if (powerType == "p") {
                grid[powerUps[i]->getY()][powerUps[i]->getX()] = 'p'; // Power-Up Type 3
            }

        }

        // Render the grid
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (grid[i][j] == 'C')
                    cout << YELLOW << grid[i][j] << RESET << " ";

                else if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'M')
                    cout << MAGENTA << grid[i][j] << RESET << " ";
                else if (grid[i][j] == 'P')
                    cout << BLUE << grid[i][j] << RESET << " ";
                else if (grid[i][j] == 'p')
                    cout << GREEN << grid[i][j] << RESET << " ";
                else if (grid[i][j] == 'B')
                    cout << CYAN << grid[i][j] << RESET << " ";
                else cout << grid[i][j] << " ";
            }
            cout << endl;
        }

        // Display lives and score
        cout << GREEN << "Lives: " << player->getLives() << " | Score: " << player->getScore() << RESET << endl;

        // Check for collisions with NyanCats
        for (int i = 0; i < 5; i++) {
            if (player->getX() == nyanCats[i]->getX() && player->getY() == nyanCats[i]->getY()) {
                player->collide(nyanCats[i], mode);
            }
        }

        // Check for collisions with PowerUps
        for (int i = 0; i < 4; i++) {
            if (player->getX() == powerUps[i]->getX() && player->getY() == powerUps[i]->getY()) {
                player->collide(powerUps[i], mode);
            }
        }

        // End game if lives are zero
        if (player->getLives() <= 0) {

            isGameOver = true;
            cout << RED << "Game Over! Final Score: " << player->getScore() << RESET << endl;

            ScoreManager scoreManager;
            scoreManager.saveScore(player->getScore());
            system("pause");
            //break;
        }

        cout << "Enter Key (left : a, right : d, up : w, down  : s , stop : z & pause(To Pause Game)): ";
        bool isPaused = false;
        // Handle player movement asynchronously
        if (_kbhit()) { // Check if a key is pressed
            char key = _getch(); // Get the key pressed
            string direction;
            switch (key) {
           /* case 'w':

                direction = "up";
                break;*/
            case 'a':
                direction = "left";
                break;
            /*case 's':
                direction = "down";
                break;*/
            case 'd':
                direction = "right";
                break;
            case 'z':
                direction = "stop";
                break;
            case 'p':
                if (system("Pause")) {
                    cout << GREEN << "Game Paused , Press 'r' or 'R' to Resume Game !" << RESET << endl;
                }

                break;
            case 'q':
                cout << RED << "Quitting the game..." << RESET << endl;
                isGameOver = true;
            default:

                continue; // Ignore other keys
            }
            if (!isPaused) { // Only allow movement if the game is not paused
              //  player->move(direction);
            }
        }


        if (mode == 0) {
            // Delay for smooth movement
            speed = 300;
            this_thread::sleep_for(chrono::milliseconds(speed));
        }

        else if (mode == 1) {
            speed = 600;
            this_thread::sleep_for(chrono::milliseconds(speed));
        }
        else if (mode == 2) {
            //speed = 900;
            speed = 12000;
            this_thread::sleep_for(chrono::milliseconds(speed));
        }
        else {
            speed = 12000;
            this_thread::sleep_for(chrono::milliseconds(speed));
        }
    }


}
void menu(Game& g) {
    system("cls");
    cout << CYAN << "==================== MENU ====================" << RESET << endl;
    cout << GREEN << "1. Play Game" << RESET << endl;
    cout << YELLOW << "2. Help" << RESET << endl;
    cout << BLUE << "3. Highest Score" << RESET << endl;
    cout << MAGENTA << "4. About Us" << RESET << endl;
    cout << RED << "5. Exit" << RESET << endl;
    cout << CYAN << "=============================================" << RESET << endl;
}