#include "../Allreference.h"

vector<string> grid;

struct initialPos{
    int x;
    int y;
};

struct initialPos * init = new(initialPos);

int readFiles(istream & input, const char * argv){
    string block;
    int numRow = 0;
    while(getline(input, block)){
        grid.push_back(block);
        for(int i = 0; i < block.size(); i++){
            if(block[i] == 'S'){
                init->x = numRow;
                init->y = i;
                grid[numRow][i] = '.';
            }
        }
        numRow++;
    } 

    return -1;
}

void updatePos(unordered_set<struct initialPos *> &pos){
    unordered_set<struct initialPos *> p;
    for(auto &ps : pos){
        int initX = ps->x;
        int initY = ps->y;
        cout << initX << " " << initY << endl;
        //cout << grid[initX][initY] << endl;
        struct initialPos * currentPs = new(initialPos);
        currentPs->y = initY;
        if(initX > 0 && grid[initX - 1][initY] != '#'){
            currentPs->x = initX - 1;
            p.insert(currentPs);
        }
        
        if(initX < grid.size() - 1 && grid[initX + 1][initY] != '#'){
            currentPs->x = initX + 1;
            p.insert(currentPs);
        }

        currentPs->x = initX;
        if(initY > 0 && grid[initX][initY - 1] != '#'){
            currentPs->y = initY - 1;
            p.insert(currentPs);
        }

        if(initY < grid[0].size() - 1 && grid[initX][initY + 1] != '#'){
            currentPs->y = initY + 1;
            p.insert(currentPs);
        }
    }
    pos = p;
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
    unordered_set<struct initialPos *> ps;
    ps.insert(init);
    int steps = 64;
    while(steps > 0){
        updatePos(ps);
        steps--;
    }
    cout << ps.size() << endl;
    return 0;
}