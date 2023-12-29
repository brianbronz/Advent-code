#include "../Allreference.h"
#include "cardClass.c++"
#include <algorithm>
enum class Type{HighCard, OnePair, TwoPairs, ThreeOfAKind, FullHouse, Poker, FiveOfaKind,};

struct Hand{
    string value;
    int bid;
    Type type = Type::HighCard;
};

vector<struct Hand *> listHand;
vector<char> strengths;

Type GetHandType(string hand){
    // Count the number of each card
    unordered_map<char, int> cardCounts;
    for (char card : hand){
        cardCounts[card]++;
    }

    // Then count the number of each count (ex. countCounts[2] == 2 means 2 pairs)
    unordered_map<int, int> countCounts;
    for (const auto& [card, count] : cardCounts){
        countCounts[count]++;
    }

    // Determine type based on counts of counts
    if (countCounts[5] == 1){
        return Type::FiveOfaKind;
    }
    else if (countCounts[4] == 1){
        return Type::Poker;
    } else if (countCounts[3] == 1 && countCounts[2] == 1) {
        return Type::FullHouse;
    } else if (countCounts[3] == 1){
        return Type::ThreeOfAKind;
    } else if (countCounts[2] == 2){
        return Type::TwoPairs;
    } else if (countCounts[2] == 1) {
        return Type::OnePair;
    } else {
        return Type::HighCard;
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
    if(hand->type == Type::FullHouse){
        res = FullHouse(hand->value);
    } else if(hand->type == Type::HighCard){
        res = HighCard(hand->value);
    } else if(hand->type == Type::OnePair){
        res = Pair(hand->value);
    } else if(hand->type == Type::Poker){
        res = Poker(hand->value);
    } else if(hand->type == Type::ThreeOfAKind){
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
            }
            if(listHand[i]->type > listHand[j]->type){
                swap(listHand[i], listHand[j]);
            }
        }
    }
    int64_t acc = 0;
    for (int i = 0; i < listHand.size(); ++i){
        cout << listHand[i]->value << endl;
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