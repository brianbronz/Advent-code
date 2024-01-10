#include "../Allreference.h"

const string normal_sequence = "AKQJT98765432";
const string jokers_sequence = "AKQT98765432J";

char findMostFrequentChar(const string& hcards) {
    map<char, int> charCount;
    for (char c : hcards) {
        if (c != 'J') {
            charCount[c]++;
        }
    }

    char mostFrequentChar = '\0';
    int maxCount = 0;

    for (const auto& pair : charCount) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostFrequentChar = pair.first;
        }
    }

    return mostFrequentChar;
}

string substituteJokers(const string& hcards) {
    string substituted = hcards;
    char mostFrequent = findMostFrequentChar(hcards);

    for (char& c : substituted) {
        if (c == 'J') {
            c = mostFrequent;
        }
    }

    return substituted;
}

double calculateEntropy(const string& hcards) {
    map<char, double> frequencies;
    for (char c : hcards) {
        frequencies[c]++;
    }
    
    double entropy = 0.0;
    for (const auto& pair : frequencies) {
        double probability = pair.second / hcards.length();
        entropy -= probability * log2(probability);
    }
    
    return entropy;
}

double calculateEntropyWithJokers(const string& hcards) {
    string replaced = substituteJokers(hcards);
    string original = hcards;

    double entropySubstituted = calculateEntropy(replaced);
    double entropyOriginal = calculateEntropy(original);

    return (entropySubstituted < entropyOriginal) ? entropySubstituted : entropyOriginal;
}

bool compareV(pair<string, int>& h1, pair<string, int>& h2){
    double entropy1 = calculateEntropyWithJokers(h1.first);
        double entropy2 = calculateEntropyWithJokers(h2.first);
        if (entropy1 != entropy2) {
            return entropy1 < entropy2;
        } else {
            return h1.first < h2.first;
        }
}

int main() {
    ifstream file("input.txt");
    vector<pair<string, int> > hands;

    string line;
    while (getline(file, line)) {
        size_t spacePos = line.find(' ');
        string hand = line.substr(0, spacePos);
        int bid = stoi(line.substr(spacePos + 1));
        hands.emplace_back(hand, bid);
    }

    sort(hands.begin(), hands.end(), compareV);

    int partTwoAnswer = 0;
    for (size_t i = 0; i < hands.size(); ++i) {
        partTwoAnswer += (hands.size() - i) * hands[i].second;
    }

    cout << "part two answer: " << partTwoAnswer << endl;
    return 0;
}
