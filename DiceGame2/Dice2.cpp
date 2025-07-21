#include <bits/stdc++.h>
using namespace std;

struct Roll
{
    int die1, die2, total;
    time_t timestamp;

    Roll(int d1, int d2) : die1(d1), die2(d2), total(d1 + d2)
    {
        timestamp = time(nullptr);
    }
};

struct GameRound
{
    int roundNum;
    vector<pair<string, Roll>> rolls;
    string winner;
    bool tie;

    GameRound(int round) : roundNum(round), tie(false) {}
};

class Player
{
    string name;
    int wins;
    vector<Roll> history;

public:
    Player(string n) : name(n), wins(0) {}

    string getName() const { return name; }
    int getWins() const { return wins; }
    int getTotalGames() const { return history.size(); }

    void addRoll(const Roll &roll) { history.push_back(roll); }
    void incrementWins() { wins++; }

    double getAverage() const
    {
        if (history.empty())
            return 0.0;
        int sum = 0;
        for (const auto &roll : history)
            sum += roll.total;
        return (double)sum / history.size();
    }

    int getBestRoll() const
    {
        int best = 0;
        for (const auto &roll : history)
            best = max(best, roll.total);
        return best;
    }

    void showStats() const
    {
        cout << name << " - Wins: " << wins << ", Games: " << getTotalGames()
             << ", Avg: " << fixed << setprecision(1) << getAverage()
             << ", Best: " << getBestRoll() << endl;
    }
};

class DiceGame
{
    vector<Player> players;
    vector<GameRound> gameHistory;
    int currentRound;

public:
    DiceGame() : currentRound(0)
    {
        setupPlayers();
    }

    void setupPlayers()
    {
        cout << "Enter number of players: ";
        int n;
        cin >> n;
        cin.ignore();

        for (int i = 0; i < n; i++)
        {
            string name;
            cout << "Player " << (i + 1) << " name: ";
            getline(cin, name);
            if (name.empty())
                name = "Player" + to_string(i + 1);
            players.emplace_back(name);
        }
    }

    void playRound()
    {
        currentRound++;
        GameRound round(currentRound);

        cout << "\n--- Round " << currentRound << " ---" << endl;

        int highestScore = 0;
        vector<int> winners;

        for (int i = 0; i < players.size(); i++)
        {
            int d1 = (rand() % 6) + 1;
            int d2 = (rand() % 6) + 1;
            Roll roll(d1, d2);

            players[i].addRoll(roll);
            round.rolls.emplace_back(players[i].getName(), roll);

            cout << players[i].getName() << ": [" << d1 << "," << d2 << "] = " << roll.total << endl;

            if (roll.total > highestScore)
            {
                highestScore = roll.total;
                winners.clear();
                winners.push_back(i);
            }
            else if (roll.total == highestScore)
            {
                winners.push_back(i);
            }
        }

        if (winners.size() == 1)
        {
            players[winners[0]].incrementWins();
            round.winner = players[winners[0]].getName();
            cout << "Winner: " << round.winner << " with " << highestScore << "!" << endl;
        }
        else
        {
            round.tie = true;
            cout << "Tie between ";
            for (size_t i = 0; i < winners.size(); i++)
            {
                cout << players[winners[i]].getName();
                if (i < winners.size() - 1)
                    cout << ", ";
            }
            cout << " (all rolled " << highestScore << ")" << endl;
        }

        gameHistory.push_back(round);
    }

    void showStandings()
    {
        cout << "\n=== Current Standings ===" << endl;
        vector<pair<int, string>> standings;
        for (const auto &p : players)
        {
            standings.emplace_back(p.getWins(), p.getName());
        }
        sort(standings.rbegin(), standings.rend());

        for (size_t i = 0; i < standings.size(); i++)
        {
            cout << (i + 1) << ". " << standings[i].second
                 << " (" << standings[i].first << " wins)" << endl;
        }
    }

    void showStats()
    {
        cout << "\n=== Player Statistics ===" << endl;
        for (const auto &player : players)
        {
            player.showStats();
        }
    }

    void showHistory()
    {
        cout << "\n=== Recent Games ===" << endl;
        int start = max(0, (int)gameHistory.size() - 5);
        for (int i = start; i < gameHistory.size(); i++)
        {
            const auto &round = gameHistory[i];
            cout << "Round " << round.roundNum << ": ";
            if (round.tie)
            {
                cout << "TIE" << endl;
            }
            else
            {
                cout << "Winner - " << round.winner << endl;
            }
        }
        cout << "Total rounds played: " << gameHistory.size() << endl;
    }

    void exportData()
    {
        string filename = "game_data.txt";
        ofstream file(filename);

        file << "=== Dice Game Export ===" << endl;
        file << "Total Rounds: " << gameHistory.size() << endl
             << endl;

        for (const auto &round : gameHistory)
        {
            file << "Round " << round.roundNum << ":" << endl;
            for (const auto &roll : round.rolls)
            {
                file << "  " << roll.first << ": [" << roll.second.die1
                     << "," << roll.second.die2 << "] = " << roll.second.total << endl;
            }
            file << "  Result: " << (round.tie ? "TIE" : "Winner: " + round.winner) << endl
                 << endl;
        }

        file.close();
        cout << "Data exported to " << filename << endl;
    }

    void run()
    {
        srand(time(nullptr));
        int choice;

        do
        {
            cout << "\n=== DICE GAME MENU ===" << endl;
            cout << "1. Play Round" << endl;
            cout << "2. Show Standings" << endl;
            cout << "3. Show Statistics" << endl;
            cout << "4. Show History" << endl;
            cout << "5. Export Data" << endl;
            cout << "6. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                playRound();
                break;
            case 2:
                showStandings();
                break;
            case 3:
                showStats();
                break;
            case 4:
                showHistory();
                break;
            case 5:
                exportData();
                break;
            case 6:
                cout << "Thanks for playing!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
            }
        } while (choice != 6);
    }
};

int main()
{
    cout << "DOUBLE DICE GAME" << endl;
    cout << "Simple but efficient!" << endl;

    DiceGame game;
    game.run();

    return 0;
}
