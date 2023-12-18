#include "../Allreference.h"
#include <cfloat>

//Vedere un modo per migliorarlo
void removeSpace(string block, vector<string>& add){
    string tempNum = "";
    int pos = block.find(":") + 1;
    for (int i = pos; i < block.size(); i++){
        if (isspace(block[i])){
            if (tempNum != "")
                add.push_back(tempNum);
                tempNum = "";
        } else {
            if (block[i] != ' '){
                tempNum += block[i];
            }
        }
    }
    if (tempNum != ""){
        add.push_back(tempNum);
    }
}


int readFiles(istream & input, const char * argv){
     string block;
     vector<string> myData;
     vector<string> toBeat;
    while(getline(input, block)){
        if (block.find("Time:") != string::npos){
            removeSpace(block, myData);

        } else {
            removeSpace(block, toBeat);
        }
    }

    //pressed + 1 speed e - 1 time
    string minDistanceStr = "";
    for (int i = 0; i < toBeat.size(); i++){
        minDistanceStr += toBeat[i];
    }

    string maxTimeStr = "";
    for (int i = 0; i < myData.size(); i++){
        maxTimeStr += myData[i];
    }
    float maxTime = stof(maxTimeStr);
    float minDistance = stof(minDistanceStr);
    float counter = 0;
    //maxTime => tempo a disposizione
    //Posso premere il bottone dai 14 ai 71516 ms
    float initVelocity = 0;
    // 51 699 878
    //377117112241505
    //30 000 000 - 40 000 000
    //34123437
    //34 123 438
    int total = -1;
    for (int t = 1; t <= maxTime; ++t) {
        if (t * (maxTime - t) > minDistance) {
            total++;
        }
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



