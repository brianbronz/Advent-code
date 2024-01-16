#include "../Allreference.h"

struct position{
    int x;
    int y;
};

vector<struct position*> ps;
vector<vector<string> > grid;
vector<vector<string> > temp;

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while(getline(input, block)){
        vector<string> row;
        bool isEmptyR = true;
        for (int i = 0; i < block.size(); i++){
            string str(1, block[i]);
            row.push_back(str);
            if(str == "#"){
                isEmptyR = false;
            }
        }
        temp.push_back(row);
        if(isEmptyR){
            temp.push_back(row);
        }
    }

    grid.resize(temp.size());
    for (int i = 0; i < temp[0].size(); i++){
        bool isEmptyC = true;
        for(int j = 0; j < temp.size(); j++){
            if(temp[j][i] == "#"){
                isEmptyC = false;
            }
            grid[j].push_back(temp[j][i]);
        }
        if(isEmptyC){
            for (int j = 0; j < temp.size(); j++){
                grid[j].push_back(".");
            }
        }
    }
    return 1;
}

void findPair(){
    //grid and temp
    //ps vector
    for(int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[0].size(); j++){
            if(grid[i][j] == "#"){
                struct position * newPs = new(position);
                newPs->x = i;
                newPs->y = j;
                ps.push_back(newPs);
            }
        }
    }

    int total = 0;
    for (int i = 0; i < ps.size() - 1; i++){
        int x1 = ps[i]->x;
        int y1 = ps[i]->y;
        for (int j = i + 1; j < ps.size(); j++){
            int x2 = ps[j]->x;
            int y2 = ps[j]->y;
            total += abs(x1 - x2) + abs(y1 - y2);
        }
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
    findPair();
    return 0;
}
