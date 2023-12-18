#include "../Allreference.h"

void stepsNorth(vector<string> & lines){
    for(int i = 1; i < lines.size(); ++i){
        for (int j = i; j > 0; --j){
            if(j != 0){
                for(int k = 0; k < lines[j].size(); ++k){
                    if(lines[j][k] == 'O' && lines[j - 1][k] == '.'){
                        swap(lines[j][k], lines[j - 1][k]);
                    }
                }
            }
        }
    }
}

void stepsSouth(vector<string> & lines){
    for(int i = lines.size() - 2; i >= 0; i--){
        for (int j = i; j <= lines[i].size() - 2; j++){
            for(int k = 0; k < lines[j].size(); ++k){
                if(lines[j][k] == 'O' && lines[j + 1][k] == '.'){
                    swap(lines[j][k], lines[j + 1][k]);
                }
            }
        }
    }
}

void stepsEast(vector<string> & lines){
    for(int i = lines[0].size() - 2; i >= 0; i--){
        for (int j = i; j < lines[i].size() - 2; j++){
            for(int k = 0; k < lines.size(); ++k){
                if(lines[k][j] == 'O' && lines[k][j - 1] == '.'){
                    swap(lines[k][j], lines[k][j - 1]);
                }
            }
        }
    }
}

void stepsWest(vector<string> & lines){
    for(int i = 1; i < lines[0].size(); ++i){
        for (int j = i; j > 0; --j){
            for(int k = 0; k < lines.size(); ++k){
                if(lines[k][j] == 'O' && lines[k][j -1] == '.'){
                    swap(lines[k][j], lines[k][j -1]);
                }
            } 
        }
    }
}

void steps(vector<string> &lines, string cases){
    if(cases == "N"){
        stepsNorth(lines);
    } else if(cases == "S"){
        stepsSouth(lines);
    } else if(cases == "E"){
        stepsEast(lines);
    } else if(cases == "W"){
        stepsWest(lines);
    }
}

int Load(vector<string> & a){
    int totalLoad = 0;
    int maxSizeR = a.size();
    int maxSizeC = a[0].size();
    for(int i = 0; i < maxSizeR; i++){
        for(int j = 0; j < maxSizeC; j++){
            if(a[i][j] == 'O'){
                totalLoad += abs((int)maxSizeR - (int)i);
            }
        }
    }
    return totalLoad;
}

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> lines;
    while(getline(input, block)){
        lines.push_back(block);
    }
    vector<string> a = lines;
    vector<string> b = lines;
    steps(a, "N");
    int totalLoad = Load(a);
    cout << totalLoad << endl;

    for(int i = 0; i < 1000000000; i++){
        steps(b, "N");
        steps(b, "W");
        steps(b, "S");
        steps(b, "E");
        cout << i << endl;
    }
    int totalLoad2 = Load(b);
    cout << totalLoad2 << endl;
    return 1;
}

int main(int argc, char * argv[]){
     //cout << argv[1] << endl; 
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
