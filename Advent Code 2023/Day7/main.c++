#include "../Allreference.h"
#include "cardClass.c++"

enum Type{
    HighCardT, 
    OnePairT, 
    TwoPairsT, 
    ThreeOfAKindT, 
    FullHouseT, 
    PokerT, 
    FiveOfaKindT,
};

struct Hand{
    string value;
    int bid;
    Type type = HighCardT;
};

vector<struct Hand *> listHand;
vector<char> strengths;

Type GetHandType(string hand){
    // Count the number of each card
    unordered_map<char, int> cardCounts;
    for (int i = 0; i < hand.size(); ++i) {
        cardCounts[hand[i]]++;
    }

    // Then count the number of each count (ex. countCounts[2] == 2 means 2 pairs)
    unordered_map<int, int> countCounts;
    for (const auto& [card, count] : cardCounts){
        countCounts[count]++;
    }

    // Determine type based on counts of counts
    if (countCounts[5] == 1){
        return FiveOfaKindT;
    } else if (countCounts[4] == 1){
        return PokerT;
    } else if (countCounts[3] == 1 && countCounts[2] == 1) {
        return FullHouseT;
    } else if (countCounts[3] == 1){
        return ThreeOfAKindT;
    } else if (countCounts[2] == 2){
        return TwoPairsT;
    } else if (countCounts[2] == 1) {
        return OnePairT;
    } else {
        return HighCardT;
    }
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        stringstream ss(block);
        vector<string> content;
        string temp;
        while(ss >> temp){
            content.push_back(temp);
        }
        struct Hand* newHand = new(Hand);
        newHand->bid = stoi(content[1]);
        newHand->value = content[0];
        newHand->type = GetHandType(content[0]);
        listHand.push_back(newHand);
    }
    return -1;
}

int check(char value, vector<char> power){
    for(int i = 0; i < power.size(); i++){
        if(value == power[i]){return i;}
    }
    return 0;
}

string orderTheHand(struct Hand * hand){
    string res;
    if(hand->type == FullHouseT){
        res = FullHouse(hand->value);
    } else if(hand->type == HighCardT){
        res = HighCard(hand->value);
    } else if(hand->type == OnePairT){
        res = Pair(hand->value);
    } else if(hand->type == PokerT){
        res = Poker(hand->value);
    } else if(hand->type == ThreeOfAKindT){
        res = ThreeOfAKind(hand->value);
    } else {
        res = DoublePair(hand->value);
    }
    return res;
}

void part1(){
    // Sort hands by increasing rank
    strengths.push_back('2');
    strengths.push_back('3');
    strengths.push_back('4');
    strengths.push_back('5');
    strengths.push_back('6');
    strengths.push_back('7');
    strengths.push_back('8');
    strengths.push_back('9');
    strengths.push_back('T');
    strengths.push_back('J');
    strengths.push_back('Q');
    strengths.push_back('K');
    strengths.push_back('A');
    for(int i = 0; i < listHand.size(); i++){
        string temp = orderTheHand(listHand[i]);
        listHand[i]->value = temp;
    }
    for (int i = 0; i < listHand.size() - 1; i++){
        for (int j = i + 1; j < listHand.size(); j++){
            if(listHand[i]->type == listHand[j]->type){
                //method for the swap
                int currentK = 0;
                int currentL = 0;
                string first = "";
                string second = "";
                while(true){
                    if(listHand[i]->value[currentK] == '1'){
                            first = listHand[i]->value[currentK];
                            first += listHand[i]->value[currentK + 1];
                            currentK += 2;
                    } else {
                        first = listHand[i]->value[currentK];
                        currentK++;
                    }
                    if(listHand[j]->value[currentL] == '1'){
                            second = listHand[j]->value[currentL];
                            second += listHand[j]->value[currentL + 1];
                            currentL +=  2;
                    } else {
                        second = listHand[j]->value[currentL];
                        currentL++;
                    }
                    if(stoi(first) > stoi(second)){
                        swap(listHand[i], listHand[j]);
                        break;
                    }
                    if(stoi(first) < stoi(second)){break;}
                }

            }
            if(listHand[i]->type > listHand[j]->type){
                swap(listHand[i], listHand[j]);
            }
        }
    }
    int64_t acc = 0;
    for (int i = 0; i < listHand.size(); ++i){
        acc += listHand[i]->bid * (i + 1);
    }
    cout << acc;
}

int main(int argc, char * argv[]){
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
    part1();
    return 0;
}