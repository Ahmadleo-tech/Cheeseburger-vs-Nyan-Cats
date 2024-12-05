/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ANSI Color Codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

// Forward declarations
class GameObject;
class Cheeseburger;
class NyanCat;
class PowerUp;
class Game;

// ScoreManager class
class ScoreManager {
private:
    int scores[5];

public:
    ScoreManager();
    void readScores();
    void saveScore(int score);
    void writeScores();
    void displayScores();
};

// Base GameObject class
class GameObject {
protected:
    int x, y;
    string color;

public:
    GameObject(int x, int y, string color);
    virtual ~GameObject();
    virtual void move(string direction);
    virtual string getType() const = 0;

    int getX() const;
    int getY() const;
};

// Cheeseburger class
class Cheeseburger : public GameObject {
private:
    int lives;
    int score;

public:
    Cheeseburger(int x, int y);
    void move(string direction);
    void collide(GameObject* obj, int mode);
    string getType() const override;
    int getLives() const;
    int getScore() const;
};

// NyanCat class
class NyanCat : public GameObject {
public:
    NyanCat(int x, int y);
    void moveDown();
    string getType() const override;
};

// PowerUp class
class PowerUp : public GameObject {
private:
    string powerType;

public:
    PowerUp(int x, int y, string powerType);
    void moveDown();
    string getType() const override;
};

// Game class
class Game {
private:
    Cheeseburger* player;
    NyanCat* nyanCats[5];
    PowerUp* powerUps[4];
    bool isGameOver;
    bool isPaused;


public:
     Game();
    ~Game();
    void start(int mode);
    friend void menu(Game &g1);
};




