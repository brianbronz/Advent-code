#include "../Allreference.h"
#include "cardClass.c++"
#include "cardClass.h"


struct database{
    vector<struct CardValue *> cv;
};
struct database * db = new(database);

struct CardValue{
    int rank;
    vector<int> power;
    string Hands;
    string bid;
    int typeOfHand;
};


vector<int> givePower(string cards){
    int repeatCard = 0;
    vector<int> result;
    for (int i = 0; i < cards.size() - 1; i++){
        for (int j = i +1; j < cards.size(); j++){
            if (cards[i] == cards[j]){
                repeatCard++;
            }
        }
    }
    if (repeatCard == 0){
        //Nothing
        //Take the highest value
        return HighCard(cards);
    } else if (repeatCard == 1){
        //One pair
        //Take the highest value
        return Pair(cards);
    } else if(repeatCard == 2){
        //double Pair
        return DoublePair(cards);

    } else if(repeatCard == 3){
        //Three of a kind
        return ThreeOfAKind(cards);
    } else if(repeatCard == 4){
        //Full house
        return FullHouse(cards);
    } else if (repeatCard == 6){
        return Poker(cards);
    } else {
        //Five Hand
        return FiveOfAKind(cards);
    }
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        int posSpace = block.find(" ");
        string cards = block.substr(0, posSpace);
        string bid = block.substr(posSpace + 1);
        struct CardValue * c = new (CardValue);
        c->bid = bid;
        c->Hands = cards;
        c->rank = 0;
        vector<int> temp = givePower(cards);
        vector<int> p;
        for (int i = 0; i < temp.size() - 1; i++){
            p.push_back(temp[i]);
        }
        c->power = p;
        c->typeOfHand = temp[temp.size() - 1];
        db->cv.push_back(c);
        temp.clear();
        p.clear();
    }
    return 1;
}

void condition(){
    for (int i = 0; i < db->cv.size() - 1; i++){
        for (int j = i + 1; j < db->cv.size(); j++){
            if (db->cv[i]->typeOfHand > db->cv[j]->typeOfHand){
                swap(db->cv[i], db->cv[j]);
            } else if(db->cv[i]->typeOfHand == db->cv[j]->typeOfHand){
                for (int l = 0; l < db->cv[i]->power.size(); l++){
                    if (db->cv[i]->power[l] > db->cv[j]->power[l]){
                        swap(db->cv[i], db->cv[j]);
                        break;
                    }
                }
            }
        }
    }
}

void compare(){
    condition();
    for (int i = 0; i < db->cv.size(); i++){
        db->cv[i]->rank = i + 1; 
    }
}

void total(){
    int sums = 0;
    for (int i = 0; i < db->cv.size(); i++){
        sums += stoi(db->cv[i]->bid) * db->cv[i]->rank;
    }
    cout << sums << endl;
}

int main(int argc, char * argv[]){
    cout << argv[1] << endl; 
    addToMap();
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

    compare();
    total();
    db->cv.clear();
    delete db;
    return 0;
    /*
    249152041
    248836197
    */
}