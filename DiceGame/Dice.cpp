
#include <bits/stdc++.h>
using namespace std;

class Player
{
    string name;
    int wins;

public:
    Player(string name)
    {
        this->name = name;
        this->wins = 0;
    }

    string getName()
    {
        return this->name;
    }

    int getWins()
    {
        return this->wins;
    }

    void incrementWins()
    {
        this->wins++;
    }
};

class Dice
{
public:
    int roll()
    {
        int v = (rand() % 6) + 1;
        return v;
    }
};

class DiceGame
{
    vector<Player> list;

public:
    DiceGame()
    {
        cout << "How many players are there ?" << endl;
        int n;
        cin >> n;
        cin.ignore();
        for (int i = 0; i < n; i++)
        {
            string name;
            cout << "Please tell the name of the player " << (i + 1) << endl;
            getline(cin, name);
            Player p(name);
            list.push_back(p);
        }
    }

    void playGame()
    {
        Dice d;
        int highestVal = 0;
        int indexOfPlayer = -1;
        for (int i = 0; i < list.size(); i++)
        {
            int output = d.roll();
            if (output > highestVal)
            {
                highestVal = output;
                indexOfPlayer = i;
            }
            else if (output == highestVal)
            {
                indexOfPlayer = -1;
            }
        }

        if (indexOfPlayer != -1)
        {
            list[indexOfPlayer].incrementWins();
        }
    }

    void showGameResult()
    {
        if (list.size() == 0)
        {
            cout << "No players in the game." << endl;
            return;
        }
        for (int i = 0; i < list.size(); i++)
        {
            cout << "Player " << (i + 1) << " " << list[i].getName() << " score is " << list[i].getWins() << endl;
        }
    }
};

int main()
{
    cout << "Hey Welcome! to the Dice console Game !!! " << endl;
    DiceGame dc;

    while (1)
    {
        cout << "*** Game Menu ***" << endl;
        cout << "1. Start the Game" << endl;
        cout << "2. Show the results" << endl;
        cout << "3. Exit" << endl;

        int ch;
        cin >> ch;

        switch (ch)
        {
        case 1:
            dc.playGame();
            break;
        case 2:
            dc.showGameResult();
            break;
        case 3:
            return 0;

        default:
            cout << "Not a valid input!!!" << endl;
            break;
        }
    }

    return 0;
}