#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct Player {
    char sign;
    int wins;
    int draws;
    int losses;
    int points;
};

unordered_map<string, Player> load_players() {
    unordered_map<string, Player> players;
    ifstream file("players.txt");
    string line;
    while (getline(file, line)) {
        string player_id;
        char sign;
        file >> player_id >> sign;
        players[player_id] = {sign, 0, 0, 0, 0};
    }
    return players;
}

void load_results(unordered_map<string, Player>& players) {
    ifstream file("tictactoe.txt");
    string line;
    while (getline(file, line)) {
        char winner_id = line[0];
        char loser_id = line[1];
        if (winner_id != '.') {
            players[string(1, winner_id)].wins++;
            players[string(1, winner_id)].points += 3;
        } else if (loser_id != '.') {
            players[string(1, loser_id)].losses++;
        } else {
            for (auto& pair : players) {
                if (pair.first != string(1, winner_id) && pair.first != string(1, loser_id)) {
                    pair.second.draws++;
                    pair.second.points++;
                }
            }
        }
    }
}

void show_table(const unordered_map<string, Player>& players) {
    cout << "ID\tSIGN\tWINS\tDRAWS\tLOSSES\tPOINTS" << endl;
    vector<pair<string, Player>> sorted_players(players.begin(), players.end());
    sort(sorted_players.begin(), sorted_players.end(), [](const pair<string, Player>& a, const pair<string, Player>& b) {
        return a.second.points > b.second.points;
    });
    for (const auto& pair : sorted_players) {
        const Player& player = pair.second;
        cout << pair.first << "\t" << player.sign << "\t" << player.wins << "\t" << player.draws << "\t" << player.losses << "\t" << player.points << endl;
    }
}

void show_results() {
    ifstream file("tictactoe.txt");
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

void show_player_stats(const unordered_map<string, Player>& players) {
    string player_id;
    cout << "Enter player id: ";
    cin >> player_id;
    if (players.find(player_id) != players.end()) {
        const Player& player = players.at(player_id);
        cout << player_id << " " << player.sign << " " << player.wins << " " << player.draws << " " << player.losses << " " << player.points << endl;
    } else {
        cout << "Not found" << endl;
    }
}

int main() {
    unordered_map<string, Player> players = load_players();
    load_results(players);
    
    int option;
    do {
        cout << "1 - Show table\n2 - Show results\n3 - Show player stats\n4 - Exit\nChoose option: ";
        cin >> option;
        switch (option) {
            case 1:
                show_table(players);
                break;
            case 2:
                show_results();
                break;
            case 3:
                show_player_stats(players);
                break;
            case 4:
                cout << "EXIT" << endl;
                break;
            default:
                cout << "Invalid" << endl;
        }
    } while (option != 4);
    
    return 0;
}
