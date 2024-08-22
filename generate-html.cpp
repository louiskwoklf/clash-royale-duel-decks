#include <bits/stdc++.h>
using namespace std;

// const string OUTPUT = "basic.html";
// const string OUTPUT = "ultchamp.html";
const string OUTPUT = "tourney.html";

string formatCardName(const string& cardName) {
    string formattedName = cardName;
    transform(formattedName.begin(), formattedName.end(), formattedName.begin(), ::tolower);
    replace(formattedName.begin(), formattedName.end(), ' ', '-');
    return formattedName;
}

string generateDeckHtml(const vector<string>& deck) {
    ostringstream html;
    html << "        <div class=\"deck\">\n";
    for (const auto& card : deck) {
        string formattedCardName = formatCardName(card);
        if (!formattedCardName.empty()) {
            html << "            <div class=\"card\">\n"
                 << "                <img src=\"https://cdns3.royaleapi.com/cdn-cgi/image/w=150,h=180,format=auto/static/img/cards/v3-2d286f92/"
                 << formattedCardName << ".png\" alt=\"" << card << "\" />\n"
                //  << "                <p>" << card << "</p>\n"
                 << "            </div>\n";
        } else {
            html << "            <div class=\"card\"></div>\n";
        }
    }
    html << "        </div>\n";
    return html.str();
}

int main() {
    ifstream infile("dueldecks.txt");
    if (!infile.is_open()) {
        cerr << "Error opening file for reading" << endl;
        return 1;
    }

    ofstream htmlOutput(OUTPUT);
    if (!htmlOutput.is_open()) {
        cerr << "Error opening file for writing" << endl;
        return 1;
    }

    string line;
    int deckCount = 0;

    string bannerTitle = "";
    if (OUTPUT == "basic.html") bannerTitle = "Basic Decks";
    else if (OUTPUT == "ultchamp.html") bannerTitle = "Ultimate Champion Decks";
    else if (OUTPUT == "tourney.html") bannerTitle = "Global Tournament Decks";

    htmlOutput << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n"
               << "    <meta charset=\"UTF-8\">\n"
               << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
               << "    <title>Clash Royale Decks</title>\n"
               << "    <link rel=\"stylesheet\" href=\"dueldecks.css\">\n"
               << "</head>\n<body>\n"
               << "    <div class=\"banner\">\n"
               << "        " << bannerTitle + "\n"
               << "    </div>\n";

    while (getline(infile, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string token;
        vector<string> deck;

        getline(iss, token, ':');

        while (getline(iss, token, ',')) {
            token.erase(0, token.find_first_not_of(' '));
            deck.push_back(token);
        }

        if (deckCount % 4 == 0) {
            if (deckCount > 0) {
                htmlOutput << "    </div>\n";
            }
            htmlOutput << "    <div class=\"deck-container\">\n";
        }

        htmlOutput << generateDeckHtml(deck);

        deckCount++;
    }

    if (deckCount > 0) {
        htmlOutput << "    </div>\n";
    }

    htmlOutput << "</body>\n</html>";

    infile.close();
    htmlOutput.close();

    return 0;
}