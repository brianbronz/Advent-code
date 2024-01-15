#include "../Allreference.h"

int numDifferent(string side1, string side2){
    int count = 0;
    for(int i = 0; i <side1.length(); i++){
        if(side1[i] != side2[i]){
            count++;
        }
    }
    return count;
}

int getScore(vector<string> &lines){
    //ottenere le colonne/righe perfette
    //#####.#
    for (int i = 1; i < lines.size(); i++){
        int tempMaxSize = min(i, (int)lines.size() - i);
        bool found = true;
        int damageCount = 0;
        for (int j = 0; j < tempMaxSize; j++){
            //part 1
            //if(lines[i + j] != lines[i - 1 - j]){
            //    found = false;
            //}
            damageCount += numDifferent(lines[i - 1 - j], lines[i + j]);
        }
        //part 1
        /*
        if(found){
            return i;
        }*/
        if(damageCount == 1){
            return i;
        }
    }
    return 0;
}

vector<string> rotate(vector<string> & lines){
    vector<string> res;
    for(int i = 0; i < lines[0].size(); i++){
        string s = "";
        for(int j = 0; j < lines.size(); j++){
            s += lines[lines.size() - 1 - j][i];
        }
        res.push_back(s);
    }
    return res;
}

int reflection(vector<string> &lines){
    int res = 0;
    res = getScore(lines) * 100;
    vector<string> stringRotated = rotate(lines);
    res += getScore(stringRotated);
    return res;
}

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> lines;
    int sums = 0;
    while(getline(input, block)){
        if(block.size() == 0){
            sums += reflection(lines);
            lines.clear();
        } else {
            lines.push_back(block);
        }
    }
    sums += reflection(lines);
    cout << sums << endl;
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