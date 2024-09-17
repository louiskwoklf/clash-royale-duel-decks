#include <bits/stdc++.h>
using namespace std;

const int UNIQUENESS = 32;

const string CHOICES = "ultchamp.txt";
// const string CHOICES = "tourney.txt";

string cards[8];
string decks[30][8];
vector <pair <int, string> > duel_decks;

bool cmp(const std::string& a, const std::string& b) {
    // Check if both strings end with '1'
    bool a_ends_with_1 = (!a.empty() && a.back() == '1');
    bool b_ends_with_1 = (!b.empty() && b.back() == '1');

    // If a ends with '1' and b does not, a should come first
    if (a_ends_with_1 && !b_ends_with_1) {
        return true;
    }
    
    // If b ends with '1' and a does not, b should come first
    if (b_ends_with_1 && !a_ends_with_1) {
        return false;
    }

    // If both or neither end with '1', use regular lexicographical comparison
    return a < b;
}

int count_unique_cards(int index1, int index2, int index3, int index4) {
    int uniqueness = 0;
    set <string> unique_cards;
    for (int i = 0; i < 8; i++) {
        string card = decks[index1][i];
        if (card[card.length() - 1] == '1') {
            card.erase(card.length() - 4, 4);
        }
        unique_cards.insert(card);
    }
    for (int i = 0; i < 8; i++) {
        string card = decks[index2][i];
        if (card[card.length() - 1] == '1') {
            card.erase(card.length() - 4, 4);
        }
        unique_cards.insert(card);
    }
    for (int i = 0; i < 8; i++) {
        string card = decks[index3][i];
        if (card[card.length() - 1] == '1') {
            card.erase(card.length() - 4, 4);
        }
        unique_cards.insert(card);
    }
    for (int i = 0; i < 8; i++) {
        string card = decks[index4][i];
        if (card[card.length() - 1] == '1') {
            card.erase(card.length() - 4, 4);
        }
        unique_cards.insert(card);
    }
    return unique_cards.size();
}

string stringify_deck(int deck_index, int deck_number) {
    string return_string = "";
    return_string += (char)(deck_number + '0');
    return_string += ": ";
    for (int i = 0; i < 8; i++) {
        return_string += decks[deck_index][i] + (i == 7 ? "\n": ",");
    }
    return return_string;
}

int main() {
    ifstream infile(CHOICES);
    ofstream outfile("dueldecks.txt");
    string s;
    int deck_count = 0;
    while(getline(infile, s)) {
        string card = "";
        int card_count = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ',') {
                cards[card_count++] = card;
                card = "";
            }
            else {
                card += s[i];
            }
        }
        while (card[card.length() - 1] == ' ') {
            card.erase(card.length() - 1, 1);
        }
        cards[card_count++] = card;
        for (int i = 0; i < 8; i++) {
            decks[deck_count][i] = cards[i];
        }
        deck_count++;
    }

    for (int i = 0; i < deck_count; i++) {
        sort(decks[i], decks[i] + 8, cmp);
    }

    for (int i = 0; i < deck_count; i++) {
        for (int j = i + 1; j < deck_count; j++) {
            for (int k = j + 1; k < deck_count; k++) {
                for (int l = k + 1; l < deck_count; l++) {
                    int uniqueness = count_unique_cards(i, j, k, l);

                    string deck1 = stringify_deck(i, 1);
                    string deck2 = stringify_deck(j, 2);
                    string deck3 = stringify_deck(k, 3);
                    string deck4 = stringify_deck(l, 4);
        
                    string final_string = deck1 + deck2 + deck3 + deck4;
                    duel_decks.push_back(make_pair(uniqueness, final_string));
                }
            }
        }
    }

    sort(duel_decks.begin(), duel_decks.end());
    reverse(duel_decks.begin(), duel_decks.end());

    set <string> duel_decks_final;

    for (int i = 0; i < duel_decks.size(); i++) {
        if (duel_decks[i].first >= UNIQUENESS) {
            duel_decks_final.insert(duel_decks[i].second);
        }
    }

    cout << duel_decks_final.size() << endl;

    for (auto i = duel_decks_final.begin(); i != duel_decks_final.end(); i++) {
        outfile << *i << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}