#include "GuessNumber.h"
#include <string>
#include <utility>
#include <fstream>
#include <limits>

GuessNumber::GuessNumber()
{
}

GuessNumber::~GuessNumber()
{
}
void GuessNumber::run()
{
    retreat = "###############################";
    cout << "Hi! Welcome to the Guess the number game" << endl;
    rangeValue = 100;
    menu();
}

void GuessNumber::menu()
{
    bool exitGame = false;
    do {
        int playerChoose;
        cout << "Main Menu" << endl;
        cout << "1 - Play game" << endl;
        cout << "2 - Choose level" << endl;
        cout << "3 - High scores table" << endl;
        cout << "4 - Exit" << endl;

        cin >> playerChoose;
        if ( cin.fail() ) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You entered an incorrect value. Please enter an integer.\n";
        }
        switch ( playerChoose ) {
        case MainMenu::Play:
        {
            play();
            menuScors();
            exitGame = true;
            break;
        }
        case MainMenu::level:
        {
            menuLevel();
            exitGame = true;
            break;
        }
        case MainMenu::Scores:
        {
            menuScors();
            exitGame = true;
            break;
        }
        case MainMenu::Exit:
        {
            exitGame = true;
            exit(0);
            break;
        }
        default:
            cout << "Enter the correct number 1 - 4" << endl;
            break;
        }

} while ( ! exitGame );

}

void GuessNumber::play()
{
    srand(time(nullptr));
    const int randomValue = rand() % rangeValue;

    int userValue { 0 };
    player.attemptCounter = 0;
    player.win = false;
//    highScores->getScores();

    cout << "Please enter your nickname " << endl;
    cin  >> player.name;

    cout << randomValue << endl;
    cout << player.name << ", enter a number in the range from 0 to " << rangeValue << endl;

        do {
            cin >> userValue;
            player.attemptCounter++;
            if ( cin.fail() ) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "You entered an incorrect value. Please enter an integer.\n";
            }
            else if ( userValue > rangeValue || userValue < 0 )
                cout << "please enter a number in the range from 0 to " << rangeValue << endl;
            else if ( userValue > randomValue )
                cout << "less than " << userValue << endl;
            else if (userValue < randomValue)
                cout << "greater than " << userValue << endl;
            else {
                cout << "Congratulations you win! the hidden number " << randomValue << endl;
                cout << player.name << ", your score: " << player.attemptCounter << endl;
                player.win = true;
            }
    } while ( ! player.win );

    if ( player.win ) {
        if ( highScores.getScores().empty() )
            highScores.appendScores(player.attemptCounter, player.name) ;
        else {
            bool newPlayer = true;
            list<pair<int, string>> tempScores = highScores.getScores();
            for ( auto &score : tempScores ) {
                if ( score.second == player.name ) {
                    newPlayer = false;
                    if (  score.first > player.attemptCounter ) {
                    score.first = player.attemptCounter;
                    break;
                    }
                }
            }
            if ( newPlayer ) highScores.appendScores( player.attemptCounter, player.name);
            else             highScores.setScores(tempScores);
        }
    }
    highScores.writeScores(highScores.getScores());
    menuScors();
}

void GuessNumber::menuLevel()
{
    bool exitGame = false;
    int playerChoose = 0;

    do {
        cout << "Menu select level" << endl;
        cout << "1 - Easy" << endl;
        cout << "2 - Normal" << endl;
        cout << "3 - Hard" << endl;
        cout << "4 - Choose your level" << endl;
        cout << "5 - Back" << endl;

        cin >> playerChoose;
        if ( cin.fail() ) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You entered an incorrect value. Please enter an integer.\n";
        }
        switch ( playerChoose )
        {
        case MenuLevel::Easy:
        {
            rangeValue = 10;
            play();
            exitGame = true;
            break;
        }
        case MenuLevel::Normal:
        {
            rangeValue = 50;
            play();
            exitGame = true;
            break;
        }
        case MenuLevel::Hard:
        {
            rangeValue = 100;
            play();
            exitGame = true;
            break;
        }
        case MenuLevel::PlayerLevel:
        {
            cout << "Choose your random number range from 0 to X" << endl;
            cin  >> rangeValue;
            play();
            exitGame = true;
            break;
        }
        case MenuLevel::Back:
        {
            menu();
            exitGame = true;
            break;
        }
        default:
            cout << "Enter the correct number 1 - 5" << endl;
            break;
        }
    } while ( ! exitGame );
}

Player GuessNumber::getPlayer()
{
    return player;
}

void GuessNumber::menuScors()
{
    bool exitGame = false;
    cout << retreat << endl;
    int playerChoose = 0;
    cout << "High scores table:" << endl;
    highScores.sort();

    for ( const auto &scor : highScores.getScores() )
        cout << scor.second << '\t' << scor.first << endl;

    cout << retreat << endl;
    do {
        cout << "select menu" << endl;
        cout << "1 - Play game" << endl;
        cout << "2 - Back to Main menu" << endl;
        cout << "3 - Clear scores" << endl;
        cout << "4 - Exit" << endl;

        cin >> playerChoose;
        if ( cin.fail() ) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You entered an incorrect value. Please enter an integer.\n";
        }
        switch ( playerChoose )
        {
        case MenuHighScore::PlayGame:
        {
            play();
            exitGame = true;
            break;
        }
        case MenuHighScore::MainMenu:
        {
            menu();
            exitGame = true;
            break;
        }
        case MenuHighScore::clear:
        {
            highScores.clearScores();
            menu();
            exitGame = true;
            break;
        }
        case MenuHighScore::ExitGame:
        {
            exit(0);
            break;
        }
        default:
            cout << "Enter the correct number 1 - 4" << endl;
            break;
        }
    } while ( ! exitGame );
}

HighScores::HighScores()
{
    scores = takeScores();
}

void HighScores::clearScores()
{
    scores.clear();
    writeScores(scores);
}

list<pair<int, string>> HighScores::takeScores()
{
    const string highScoresFileName = "high_scores.txt";

    std::fstream file(highScoresFileName, std::ios::in | std::ios::out);
    if (!file.is_open()) {
        cerr << "Failed to open file\n";
    }

    int highScore = 0;
    string username;
    std::list<std::pair<int, std::string>> namesAndScores;
    while (true) {
        file >> username;
        file >> highScore;
        file.ignore();
        if (file.fail()) {
            break;
        }
        namesAndScores.push_back({highScore, username});
    }
    file.close();
    return namesAndScores;
}

list<pair<int, string> > HighScores::getScores()
{
    return scores;
}

void HighScores::setScores(list<pair<int, string>> scores)
{
    this->scores = scores;
}

void HighScores::appendScores(int attemptCounter, string name)
{
    this->scores.push_back( {attemptCounter, name });
}

void HighScores::sort()
{
    scores.sort();
}

void HighScores::writeScores(list<pair<int, string> > scors)
{
//    scors.sort();
    const string highScoresFileName = "high_scores.txt";
    ofstream outFile{highScoresFileName, ios_base::out};
    if ( ! outFile.is_open() ) {
        cout << "Failed to open file for write: " << highScoresFileName << "!" << endl;
    }

    if ( outFile.is_open() ) {
        if ( scors.empty() )
            outFile.clear();
        else
            for ( const auto &score : scors)
                outFile << score.second << '\t' << score.first << endl;
    }
    outFile.close();

}
