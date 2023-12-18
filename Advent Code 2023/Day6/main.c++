#include "../Allreference.h"

void removeSpace(string block, vector<int>& add){
    string tempNum = "";
    int pos = block.find(":") + 1;
    for (int i = pos; i < block.size(); i++){
        if (isspace(block[i])){
            if (tempNum != "")
                add.push_back(stoi(tempNum));
                tempNum = "";
        } else {
            if (block[i] != ' '){
                tempNum += block[i];
            }
        }
    }
    if (tempNum != ""){
        add.push_back(stoi(tempNum));
    }
}


int readFiles(istream & input, const char * argv){
     string block;
     vector<int> myData;
     vector<int> toBeat;
    while(getline(input, block)){
        if (block.find("Time:") != string::npos){
            removeSpace(block, myData);

        } else {
            removeSpace(block, toBeat);
        }
    }

    //pressed + 1 speed e - 1 time
    vector<int> possibility;
    for (int i = 0; i < myData.size(); i++){
        int initVelocity = 0;
        int count = 0;
        int maxTime = myData[i];
        int minDistance = toBeat[i];
        for (int j = 0; j < maxTime; j++){
            if (initVelocity * (maxTime - j) > minDistance){
                count++;
            }
            initVelocity++;
        }
        possibility.push_back(count);
    }
    int total = 1;
    for (int i = 0; i < possibility.size(); i++){
        total = total * possibility[i];
    }
    cout << total << endl;
}

int main(int argc, char * argv[]){
    cout << argv[1] << endl; 
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