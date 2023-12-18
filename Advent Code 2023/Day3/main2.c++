#include "../Allreference.h"


struct Tile{
    string value;
    string type;
    int isInsert;
    int id;
};

struct NumId{
    string value;
    int id;
};

vector < vector<struct Tile *> > vT;
vector <struct NumId *> numValue;


struct Tile * addToTile(char value, string type, int id){
    struct Tile * newTile = new(Tile);
    newTile->type = type;
    string str(1, value);
    newTile->value = str;
    newTile->isInsert = false;
    newTile->id = id;
    return newTile;
}

string addToVect(string tempNum, int id){
    if (tempNum != ""){
        struct NumId * a = new(NumId);
        a->id = id;
        a->value = tempNum;
        numValue.push_back(a);
    }
    tempNum = "";
    return tempNum;
}

int readFiles(istream & input, const char * argv){
    string block;
    int counterStar = 0;
    while(getline(input, block)){
        string tempNum = "";
        struct Tile * tempTile = new(Tile);
        vector<struct Tile *> vectTile;
        for (int i = 0; i < block.size(); i++){
            if (isdigit(block[i])){
                tempTile = addToTile(block[i], "Num", -1);
                tempNum += block[i];
                //a number
            } else if (block[i] == '.'){
                //.
                tempTile = addToTile(block[i], "Point", -1);
                tempNum = addToVect(tempNum, -1);
            } else if(block[i] == '*'){
                //Star
                tempTile = addToTile(block[i], "Star", counterStar);
                counterStar++;
                tempNum = addToVect(tempNum, -1);
            } else {
                //rest
                tempTile = addToTile(block[i], "Rest", -1);
                tempNum = addToVect(tempNum, -1);
            }
            vectTile.push_back(tempTile);//una riga con tutte le colonne
        };
        vT.push_back(vectTile);
        vectTile.clear();
    }
    return 1;
}

vector<int> check(string typeValue, int row, int column){
    vector<int> result;
    int compare = (typeValue == "Star");
    result.push_back(compare);
    result.push_back(row);
    result.push_back(column);
    return result;
}

vector<int> checkAdjacentTile(int currentRow, int currentColumn){
    int maxRow = vT.size();//check
    int maxColumn = vT[0].size();
    //Cases
    // +1 +1
     vector<int> tempResult;
     tempResult.push_back(0);
    if(currentRow + 1 < maxRow && currentColumn + 1 < maxColumn){
         tempResult = check(vT[currentRow + 1][currentColumn + 1]->type, currentRow + 1, currentColumn + 1);
    }
    // +1 -1
    if(currentRow + 1 < maxRow && currentColumn - 1 >= 0 && !tempResult[0]){
        tempResult = check(vT[currentRow + 1][currentColumn - 1]->type, currentRow + 1, currentColumn - 1);
    }
    // -1 +1
    if(currentRow - 1 >= 0 && currentColumn + 1 < maxColumn && !tempResult[0]){
        tempResult = check(vT[currentRow - 1][currentColumn + 1]->type, currentRow - 1, currentColumn + 1);
    }
    // -1 -1
    if(currentRow - 1 >= 0 && currentColumn - 1 >= 0 && !tempResult[0]){
        tempResult = check(vT[currentRow - 1][currentColumn - 1]->type, currentRow - 1, currentColumn - 1);
    }
    //-1 0
    if(currentRow - 1 >= 0 && !tempResult[0]){
        tempResult = check(vT[currentRow - 1][currentColumn]->type, currentRow - 1, currentColumn);
    }
    //+1 0
    if(currentRow + 1 < maxRow && !tempResult[0]){
        tempResult = check(vT[currentRow + 1][currentColumn]->type, currentRow + 1, currentColumn);
    }
    //0 +1
    if(currentColumn + 1 < maxColumn && !tempResult[0]){
        tempResult = check(vT[currentRow][currentColumn + 1]->type, currentRow, currentColumn + 1);
    }
    //0 -1
    if(currentColumn - 1 >= 0 && !tempResult[0]){
        tempResult = check(vT[currentRow][currentColumn - 1]->type, currentRow, currentColumn - 1);
    }
    return tempResult;
}

string TakeLeftDigit(int i, int j){
    string value = "";
    for (int p = j; p >= 0; p--){
        if (vT[i][p]->type == "Num" &&!vT[i][p]->isInsert){
            value += vT[i][p]->value;
            vT[i][p]->isInsert = true;
        } else if(vT[i][p]->type == "Rest" || vT[i][p]->type == "Point" || vT[i][p]->type == "Star"){
            //tempLeft += vT[i][p]->value;
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
        } else if(vT[i][p]->type == "Rest" || vT[i][p]->type == "Point" || vT[i][p]->type == "Star"){
            break;
        }
    }
    return value;
}
void checkMatrix(){
    vector<struct NumId *> sums;
    int counter = 0;
    for (int i = 0; i < vT.size(); i++){
        int isNum = 0;
        vector<int> isTake;
        isTake.push_back(0);
        for (int j = 0; j < vT[i].size(); j++){
            if (vT[i][j]->type == "Num"){
                isNum = 1;
                isTake = checkAdjacentTile(i, j);
            } else {
                isNum = 0;
            }
   
            if(isTake[0]){
                string tempLeft = TakeLeftDigit(i, j);
                string tempRight = TakeRightDigit(i, j);
                string finalRes = tempLeft + tempRight;
                //isTake => boolean, row of star and column of star
                if (!finalRes.empty()){
                    cout << finalRes << " ";
                    struct NumId * newElement = new(NumId);
                    newElement->id = vT[isTake[1]][isTake[2]]->id;
                    cout << newElement->id << endl;
                    newElement->value = finalRes;
                    sums.push_back(newElement);
                }
            }
        isTake.clear();   
        }
    }
    int sumValue = 0;
    for (int i = 0; i < sums.size() - 1; i++){
        for (int j = i + 1; j < sums.size(); j++){
            if(sums[i]->id == sums[j]->id){
                sumValue += stoi(sums[i]->value) * stoi(sums[j]->value);
            }
        }
    }
    cout << sumValue << endl;
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
    checkMatrix();
    return 0;
}