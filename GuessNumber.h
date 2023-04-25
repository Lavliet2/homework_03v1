#ifndef GUESSNUMBER_H
#define GUESSNUMBER_H
#include <iostream>
#include <list>

using namespace std;

/// ##############################################################################################
/// @class HighScores
/// ##############################################################################################
class HighScores
{
public:
    HighScores();
    void clearScores();
    void sort();
    void writeScores();

    list<pair<int, string>> takeScores();
    list<pair<int, string>> getScores();
    void                    setScores(list<pair<int, string>> scores);
    void                    appendScores(int attemptCounter, string name);

private:
    list<pair<int, string>> scores;
};

struct Player
{
    string name;
    int attemptCounter { 0 };
    bool win { false };
};

/// ##############################################################################################
/// @class GuessNumber
/// ##############################################################################################
class GuessNumber
{
    enum MainMenu
    {
        Play = 1,
        level,
        Scores,
        Exit
    };
    enum MenuLevel {
        Easy = 1,
        Normal,
        Hard,
        PlayerLevel,
        Back,
    };
    enum MenuHighScore {
        PlayGame = 1,
        MainMenu,
        clear,
        ExitGame
    };


public:
    GuessNumber();
    ~GuessNumber();

    Player getPlayer();

    void run();
    void menu();
    void play();
    void menuLevel();
    void menuScors();


private:
    HighScores highScores;
    Player player;
    string retreat;
    int rangeValue;
};



#endif // GUESSNUMBER_H
