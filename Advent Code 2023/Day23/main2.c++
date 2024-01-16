#include "../Allreference.h"

vector<string> grid;

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        grid.push_back(block);
    }
    return -1;
}

int dfs(int x, int y, int count){
    if(x == grid.size() - 1 && y == grid[0].size() - 2){return count;}
    int local = 0;
    grid[x][y] = '#';
    for(int i = 0; i < 4; i++){
        int newX = x;
        int newY = y;
        switch(i){
            case 0: newX--; break;
            case 1: newY++; break;
            case 2: newX++; break;
            case 3: newY--; break;
            default: break;
        }
        if(grid[newX][newY] != '#'){
            if(newX >= 0 && newY >= 0 && newX < grid.size() && newY < grid[0].size()){
                local = max(local, dfs(newX, newY, count + 1));
            }
        }
    }
    grid[x][y] = '.';
    return local;
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
    int maxSteps = dfs(0, 1, 1) - 1;
    cout << maxSteps << endl;
    return 0;
}