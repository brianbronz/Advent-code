#include "../Allreference.h"

int possibility = 0;

vector<string> removeSpace(string block){
    string s;
    stringstream ss(block);
    vector<string> result;
    while(getline(ss, s, ' ')){
        result.push_back(s);
    }
    return result;
}

int combinations(int init, int groupPos, string text, vector<int> &position){
    if(groupPos >= position.size()){
        for (int i = init; i < text.size(); i++){
            if(text[i] == '#'){return 0;}
        }
        return 1;
    }

    if(init >= text.size()){return 0;}

    int res = 0;
    if(text[init] == '.' || text[init] == '?'){
        res += combinations(init + 1, groupPos, text, position);
    }

    if(init + position[groupPos] <= text.size()){
        bool possibleCombination = true;
        for(int i = init; i < init + position[groupPos]; i++){
            if(text[i] == '.'){
                possibleCombination = false;
                break;
            }
        }

        if(possibleCombination){
            if((init + position[groupPos] < text.size() && text[init + position[groupPos]] != '#') ||
                init + position[groupPos] == text.size()){
                    res += combinations(init + position[groupPos] + 1, groupPos + 1, text, position);
            }
        }
    }
    return res;
}

void defineValue(string part1, string part2){
    vector<int> position;
    int previous = 0;
    for (int i = 0; i < part2.size(); i++){
        if(part2[i] == ','){
            position.push_back(stoi(part2.substr(previous, i)));
            previous = i + 1;
        }
    }
    position.push_back(stoi(part2.substr(previous)));
    /**
     * part2 exercise 12
     * 
     */
    string temp = part1;
    string unknown = "?";
    vector<int> tempV = position;
    for(int i = 0; i < 4; i++){
        part1 += "?" + temp; 
        for (int j = 0; j < tempV.size(); j++){
            position.push_back(tempV[j]);
        }
    }
    possibility += combinations(0, 0, part1, position);
}

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while(getline(input, block)){
        vector<string> notSpace = removeSpace(block);
        string part1 = notSpace[0];
        string part2 = notSpace[1];
        defineValue(part1, part2);
    }
    cout << possibility;
    return 1;
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
    return 0;
}