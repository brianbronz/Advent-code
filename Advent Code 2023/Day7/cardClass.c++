#include "../Allreference.h"
map<string, int> cardValues;
void addToMap(){
    cardValues.insert(make_pair("2", 2));
    cardValues.insert(make_pair("3", 3));
    cardValues.insert(make_pair("4", 4));
    cardValues.insert(make_pair("5", 5));
    cardValues.insert(make_pair("6", 6));
    cardValues.insert(make_pair("7", 7));
    cardValues.insert(make_pair("8", 8));
    cardValues.insert(make_pair("9", 9));
    cardValues.insert(make_pair("T", 10));
    cardValues.insert(make_pair("J", 11));
    cardValues.insert(make_pair("Q", 12));
    cardValues.insert(make_pair("K", 13));
    cardValues.insert(make_pair("A", 14));
}

string HighCard(string cards){
    addToMap();
    vector<int> res;
    for (int i = 0; i < cards.size(); i++){
        string temp(1, cards[i]);
        int value = cardValues[temp];
        res.push_back(value);
    }
    sort(res.begin(), res.end(), greater<int>());
    string finalRes;
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}

string Pair(string cards){
    addToMap();
    int identicNumb = 0;
    vector<int> res;
    for (int i = 0; i < cards.size() - 1; i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        for (int j = i + 1; j < cards.size(); j++){
            string temp(1, cards[j]);
            int value2 = cardValues[temp];
            if (value == value2 && identicNumb != value2){
                identicNumb = value;
                break;
            }
        }
    }
    res.push_back(identicNumb);
    res.push_back(identicNumb);
    string tempRes;
    for (int i = 0; i < cards.size(); i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        if (value != identicNumb){
            tempRes.push_back(value);
        }
    }
    sort(tempRes.begin(), tempRes.end(), greater<int>());
    for (int i = 0; i < tempRes.size(); i++){
        res.push_back(tempRes[i]);
    }
    string finalRes;
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}

string DoublePair(string cards){
    addToMap();
    vector<int> pairInfo;
    vector<int> res;
    for (int i = 0; i < cards.size() - 1; i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        for (int j = i + 1; j < cards.size(); j++){
            string temp(1, cards[j]);
            int value2 = cardValues[temp];
            if (value == value2){
                pairInfo.push_back(value);
                break;
            }
        }
    }
    //insert the double pair
    sort(pairInfo.begin(), pairInfo.end(), greater<int>());
    for (int i = 0; i < pairInfo.size(); i++){
        res.push_back(pairInfo[i]);
        res.push_back(pairInfo[i]);
    }
    //insert the last number
    for (int i = 0; i < cards.size(); i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        for (int j = 0; j < pairInfo.size(); j++){
            if(res[0] != value && res[2] != value){
                res.push_back(value);
                break;
            }
        }
    }
    string finalRes;
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}

string ThreeOfAKind(string cards){
    addToMap();
    vector<int> res;
    int stopLoop = 0;
    for (int i = 0; i < cards.size() - 1; i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        for (int j = i + 1; j < cards.size(); j++){
            string temp(1, cards[j]);
            int value2 = cardValues[temp];
            if (value == value2){
                stopLoop = 1;
                res.push_back(value);
                res.push_back(value);
                res.push_back(value);
                break;
            }
        }
        if (stopLoop){break;}
    }
    vector<int> temp;
    for (int i = 0; i < cards.size(); i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        if (value != res[0]){
            temp.push_back(value);
        }
    }
    if (temp[0] < temp[1]){
        res.push_back(temp[1]);
        res.push_back(temp[0]);
    } else {
        res.push_back(temp[0]);
        res.push_back(temp[1]);
    }
    string finalRes = "";
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}


string FullHouse(string cards){
    addToMap();
    vector<int> res;
    vector<int> info;
    //22333 || 33223
    int third = 0;
    for(int i = 0; i < cards.size() - 1; i++){
        string tempValue(1, cards[i]);
        int value = cardValues[tempValue];
        for (int j = i + 1; j < cards.size(); j++){
            string tempValue2(1, cards[j]);
            if (value == cardValues[tempValue2]){
                if(info.size() == 0){
                    info.push_back(value);//=>push 3
                } else{
                    if (info[0] != value){
                        info.push_back(value);
                    } else {
                        third = value;
                    }
                }
            }
        }
    }
    //nel info => 3, 2
    //third = 3
    res.push_back(third);
    res.push_back(third);
    res.push_back(third);
    if(info[0] == third){
        res.push_back(info[1]);
        res.push_back(info[1]);
    } else {
        res.push_back(info[0]);
        res.push_back(info[0]);
    }
    string finalRes;
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}

string Poker(string cards){
    addToMap();
    vector<int> res;
    int stopLoop = 0;
    for (int i = 0; i < cards.size() - 1; i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        for (int j = i + 1; j < cards.size(); j++){
            string temp(1, cards[j]);
            int value2 = cardValues[temp];
            if (value == value2){
                res.push_back(value);
                stopLoop = 1;
                break;
            }
        }
        if (stopLoop){break;}
    }
    res.push_back(res[0]);
    res.push_back(res[0]);
    res.push_back(res[0]);
    for(int i = 0; i < cards.size(); i++){
        string temp1(1, cards[i]);
        int value = cardValues[temp1];
        if(res[0] != value){
            res.push_back(value);
        }
    }
    string finalRes;
    for(int i = 0; i < res.size(); i++){
        finalRes += to_string(res[i]);
    }
    return finalRes;
}
