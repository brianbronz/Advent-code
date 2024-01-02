#include "../Allreference.h"

vector<string> grid;

struct initialPos{
    int x;
    int y;
};

struct initialPos * init = new(initialPos);


int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        grid.push_back(block);
    } 
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == 'S'){
                init->x = i;
                init->y = j;
                grid[i][j] = '0';
            }
        }
    }
    return -1;
}


bool check(int x, int y){
    return (x >= 0 && x < grid.size() && y >= 0 && y < grid.size() && grid[x][y] != '#');
}

void addToPS(vector<struct initialPos *> &ps, int x, int y){
    bool notFound = false; 
    for(int i = 0; i < ps.size(); i++){
        if(x == ps[i]->x && y == ps[i]->y){
            notFound = true;
            break;
        }
    }
    if(!notFound){
        struct initialPos * newPs = new(initialPos);
        newPs->x = x;
        newPs->y = y;
        ps.push_back(newPs);
    }
}
int total = 0;
void Steps(vector<struct initialPos *> &pos){
    vector<struct initialPos *> ps;
    for(int i = 0; i < pos.size(); i++){
        int initX = pos[i]->x;
        int initY = pos[i]->y;
        if(check(initX + 1, initY)){
            addToPS(ps, initX + 1, initY);
            grid[initX + 1][initY] = '.';
        } 
        if(check(initX - 1, initY)){
            addToPS(ps, initX - 1, initY);
            grid[initX - 1][initY] = '.';
        } 
        if(check(initX, initY + 1)){
            addToPS(ps, initX, initY + 1);
            grid[initX][initY + 1] = '.';
        } 
        if(check(initX, initY - 1)){
            addToPS(ps, initX, initY - 1);
            grid[initX][initY - 1] = '.';
        }
    }
    pos = ps;
    total = pos.size();
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
    vector<struct initialPos *> ps;
    ps.push_back(init);
    for(int i = 0; i < 64; i++){
        Steps(ps);
        cout << endl;
    }
    cout << ps.size()<< endl;
    return 0;
}