#include "../Allreference.h"

vector<int> points;

void checkResult(vector<string> myNum, vector<string> NumToCheck){
    int counter = 0;
    for (int i = 0; i < myNum.size(); i++){
        for (int j = 0;j < NumToCheck.size(); j++){
            if (NumToCheck[j] == myNum[i]){
                counter++;
            }
        }
    }
    points.push_back(counter);
}

vector<string> initVect(string value){
    vector<string> a;
    string tempNum = "";
    for (int i = 0; i < value.size(); i++){
            if (isspace(value[i])){
                if (tempNum != ""){
                    a.push_back(tempNum);
                }
                tempNum = "";
            } else {
                tempNum += value[i];
            }
    }
    if (tempNum != ""){
        a.push_back(tempNum);
    }
    return a;
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        //take the info to divide the string in three parts
        int posDoublePoint = block.find(":");
        int posVerticalSign = block.find("|");

        //take number of winning
        string scratchCardWin = block.substr(posDoublePoint + 1, posVerticalSign - posDoublePoint);

        //Take my Number
        string scratchMyCard = block.substr(posVerticalSign + 2);
        vector<string> scratchWin = initVect(scratchCardWin);
        vector<string> myScratchcards = initVect(scratchMyCard);
        
        checkResult(myScratchcards, scratchWin);
        myScratchcards.clear();
        scratchWin.clear();
    }
}

void totalPoints(){
    int total = 0;
    for (int i = 0; i < points.size(); i++){
       /*  if (points[i] > 0){
            total += pow(2, points[i] - 1); =>part one
        } */
    }

    vector<int> numSc;
    for (int i = 0; i < points.size(); i++){
        numSc.push_back(1);
    }

    for (int i = 0; i < numSc.size(); i++){
        if (points[i] > 0){
            int temp = points[i];
            for (int j = i + 1; j < numSc.size() && temp > 0; j++){
                (numSc[i] == 1)?
                    numSc[j]++: numSc[j] += numSc[i];
                temp--;
            }
        }
    }

    for (int i = 0; i < numSc.size(); i++){
        total += numSc[i];
    }
    cout << total << endl;
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
    totalPoints();
    return 0;
}