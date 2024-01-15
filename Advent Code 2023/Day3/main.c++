#include "../Allreference.h"

struct Tile{
    string value;
    string type;
    int isInsert;
};

vector<vector<struct Tile *> > vT;
vector<string> numValue;

struct Tile * addToTile(char value, string type){
    struct Tile * newTile = new(Tile);
    newTile->type = type;
    string str(1, value);
    newTile->value = str;
    newTile->isInsert = false;
    return newTile;
}

string addToVect(string tempNum){
    if (tempNum != ""){
        numValue.push_back(tempNum);
    }
    tempNum = "";
    return tempNum;
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        string tempNum = "";
        struct Tile * tempTile = new(Tile);
        vector<struct Tile *> vectTile;
        for (int i = 0; i < block.size(); i++){
            if (isdigit(block[i])){
                tempTile = addToTile(block[i], "Num");
                tempNum += block[i];
                //a number
            } else if (block[i] == '.'){
                //.
                tempTile = addToTile(block[i], "Point");
                tempNum = addToVect(tempNum);
            } else {
                //rest
                tempTile = addToTile(block[i], "Rest");
                tempNum = addToVect(tempNum);
            }
            vectTile.push_back(tempTile);//a row with the column
        };
        vT.push_back(vectTile);
        vectTile.clear();
    }
    return 1;
}

bool check(string typeValue){
    return typeValue == "Rest";
}

bool checkAdjacentTile(int currentRow, int currentColumn){
    int maxRow = vT.size();//check
    int maxColumn = vT[0].size();
    //Cases
    // +1 +1
    bool tempResult = false;
    if(currentRow + 1 < maxRow && currentColumn + 1 < maxColumn){
         tempResult = check(vT[currentRow + 1][currentColumn + 1]->type);
    }
    // +1 -1
    if(currentRow + 1 < maxRow && currentColumn - 1 >= 0 && !tempResult){
        tempResult = check(vT[currentRow + 1][currentColumn - 1]->type);
    }
    // -1 +1
    if(currentRow - 1 >= 0 && currentColumn + 1 < maxColumn && !tempResult){
        tempResult = check(vT[currentRow - 1][currentColumn + 1]->type);
    }
    // -1 -1
    if(currentRow - 1 >= 0 && currentColumn - 1 >= 0 && !tempResult){
        tempResult = check(vT[currentRow - 1][currentColumn - 1]->type);
    }
    //-1 0
    if(currentRow - 1 >= 0 && !tempResult){
        tempResult = check(vT[currentRow - 1][currentColumn]->type);
    }
    //+1 0
    if(currentRow + 1 < maxRow && !tempResult){
        tempResult = check(vT[currentRow + 1][currentColumn]->type);
    }
    //0 +1
    if(currentColumn + 1 < maxColumn && !tempResult){
        tempResult = check(vT[currentRow][currentColumn + 1]->type);
    }
    //0 -1
    if(currentColumn - 1 >= 0 && !tempResult){
        tempResult = check(vT[currentRow][currentColumn - 1]->type);
    }
    return tempResult;
}

string TakeLeftDigit(int i, int j){
    string value = "";
    for (int p = j; p >= 0; p--){
        if (vT[i][p]->type == "Num" &&!vT[i][p]->isInsert){
            value += vT[i][p]->value;
            vT[i][p]->isInsert = true;
        } else if(vT[i][p]->type == "Rest" || vT[i][p]->type == "Point"){
            break;
        }
    }
    reverse(value.begin(), value.end());
    return value;
}

string TakeRightDigit(int i, int j){
    string value = "";
    for (int p = j; p < vT[i].size(); p++){
        if (vT[i][p]->type == "Num" && !vT[i][p]->isInsert){
            value += vT[i][p]->value;
            vT[i][p]->isInsert = true;
        } else if(vT[i][p]->type == "Rest" || vT[i][p]->type == "Point"){
            break;
        }
    }
    return value;
}

void checkMatrix(){
    vector<int> sums;
    int counter = 0;
    for (int i = 0; i < vT.size(); i++){
        int isNum = 0;
        bool isTake = false;
        for (int j = 0; j < vT[i].size(); j++){
            if (vT[i][j]->type == "Num"){
                isNum = 1;
                isTake = checkAdjacentTile(i, j);
            } else {
                isNum = 0;
            }
   
            if(isTake){
                string tempLeft = TakeLeftDigit(i, j);
                string tempRight = TakeRightDigit(i, j);
                string finalRes = tempLeft + tempRight;
                if (!finalRes.empty())
                    sums.push_back(stoi(finalRes));
            }   
        }
    }
    int sumValue = 0;
    for (int i = 0; i < sums.size(); i++){
        sumValue += sums[i];
    }
    cout << sumValue << endl;
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
    checkMatrix();
    return 0;
}