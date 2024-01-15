#include "../Allreference.h"

struct database{
    vector<struct Step *> cv;
};

struct database * db = new(database);

struct Step{
    string nameC;
    string left;
    string right;
};

string direction = "";

void addToDb(string block){
    int posEquals = block.find("=");
    struct Step* newStep = new(Step);
    string name = block.substr(0, posEquals - 1);
    int posOpen = block.find("(");
    string L = block.substr(posOpen + 1, 3);
    int posClose = block.find(")");
    string R = block.substr(posClose - 3, 3);
    newStep->nameC = name;
    newStep->left = L;
    newStep->right = R;
    db->cv.push_back(newStep);
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        if (block.find("=") != string::npos){
            addToDb(block);
        } else {
            if (block.size() != 0){
                direction = block;
            } 
        }
    }
    return 1;
}

bool isEndWithZ(vector<string> vStr){
    for (int i = 0; i < vStr.size(); i++){
        if(vStr[i][2] != 'Z'){
            return false;
        }
    }
    return true;
}

int countStep(string c){
    int count = 0;
    while (c[2] != 'Z'){
        for (int i = 0; i < direction.size(); i++){
            string temp = "";
            for (int j = 0; j < db->cv.size(); j++){
                if(db->cv[j]->nameC == c){
                    if(direction[i] == 'L'){
                        temp = db->cv[j]->left;
                        count++;
                    } else {
                        temp = db->cv[j]->right;
                        count++;
                    }
                }
                
            }
            c = temp;
        }
    }
    return count;
}

int64_t mcd(int64_t a, int64_t b){
    while(b != 0){
        int64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int64_t mcm(int64_t a, int64_t b){
    return (a * b) / mcd(a, b);
}

void totalStep(){
    string current = "AAA";
    int count = 0;
    int numOfEndA =0;

    /* Exercise 1
    while (current != "ZZZ"){
        for (int i = 0; i < direction.size(); i++){
            string temp = "";
            for (int j = 0; j < db->cv.size(); j++){
                if(db->cv[j]->nameC == current){
                    if(direction[i] == 'L'){
                        temp = db->cv[j]->left;
                        count++;
                    } else {
                        temp = db->cv[j]->right;
                        count++;
                    }
                }
                
            }
            current = temp;
        }
    }*/
    vector<int> indexEndA;
    vector<string> initialStart;
    for (int i = 0; i < db->cv.size(); i++){
        if(db->cv[i]->nameC[2] == 'A'){
            initialStart.push_back(db->cv[i]->nameC);
        }
    }

    vector<int64_t> numStep;
    for(int i = 0; i < initialStart.size(); i++){
        int64_t value = countStep(initialStart[i]);
        numStep.push_back(value);
    }

    int64_t result = numStep[0];
    for (int i = 1; i < numStep.size(); i++){
        result = mcm(result, numStep[i]);
    }
    cout << result << endl;
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

    totalStep();
    db->cv.clear();
    delete db;
    return 0;
}