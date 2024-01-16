#include "../Allreference.h"

const string jokers_sequence = "AKQT98765432J";
vector<pair<string, int> > hands;

char findMostFrequentChar(const string& hcards) {
    map<char, int> charCount;
    for (int i = 0; i < hcards.size(); ++i) {
        char c = hcards[i];
        if (c != 'J') {
            charCount[c]++;
        }
    }

    char mostFrequentChar = '\0';
    int maxCount = 0;

    for (map<char, int>::const_iterator it = charCount.begin(); it != charCount.end(); ++it) {
        const pair<const char, int>& pair = *it;
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
    for (int i = 0; i < substituted.size(); ++i){
        char& c = substituted[i];
        if (c == 'J') {
            c = mostFrequent;
        }
    }

    return substituted;
}

double calculateEntropy(const string& hcards) {
    map<char, double> frequencies;
    for (int i = 0; i < hcards.size(); ++i) {
        char c = hcards[i];
        frequencies[c]++;
    }
    
    double entropy = 0.0;
    for (map<char, double>::const_iterator it = frequencies.begin(); it != frequencies.end(); ++it) {
        // Calculate the probability of the current character in the 'hcards' string
        double probability = it->second / hcards.length();
        // Update the entropy using the calculated probability
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

int readFiles(istream & input, const char * argv){
    string line;
    while (getline(input, line)) {
        size_t spacePos = line.find(' ');
        string hand = line.substr(0, spacePos);
        int bid = stoi(line.substr(spacePos + 1));
        hands.emplace_back(hand, bid);
    }
    return -1;
}

int main(int argc, char * argv[]) {
    if (argc > 1){
        for (int i = 1; i < argc; i++){
            ifstream f(argv[i]);
            if(!f || !readFiles(f, argv[i])){
                return EXIT_FAILURE;
            }
        }
    } else {
        if(!readFiles(cin, "{stdin}"))
            return EXIT_FAILURE;
    } 

    sort(hands.begin(), hands.end(), compareV);
    int partTwoAnswer = 0;
    for (size_t i = 0; i < hands.size(); ++i) {
        partTwoAnswer += (hands.size() - i) * hands[i].second;
    }

    cout << "part two answer: " << partTwoAnswer << endl;
    return 0;
}
