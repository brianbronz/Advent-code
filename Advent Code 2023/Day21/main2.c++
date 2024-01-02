#include "../Allreference.h"

vector<string> grid;

struct initialPos{
    int x;
    int y;
};

struct initialPos * init = new(initialPos);
//4035660185267009 is wrong

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
    int iSize = static_cast<int>(grid.size());
    int jSize = static_cast<int>(grid.front().size());

    for(int i = 0; i < pos.size(); i++){
        int initX = pos[i]->x;
        int initY = pos[i]->y;

        if(check(((((initX + 1 ) % iSize) + iSize) % iSize), ((initY % jSize) + jSize) % jSize)){
            addToPS(ps, ((((initX + 1 ) % iSize) + iSize) % iSize), ((initY % jSize) + jSize) % jSize);
            grid[((((initX + 1 ) % iSize) + iSize) % iSize)][((initY % jSize) + jSize) % jSize] = '.';
        } 
        if(check(((((initX - 1 ) % iSize) + iSize) % iSize), ((initY % jSize) + jSize) % jSize)){
            addToPS(ps, ((((initX - 1 ) % iSize) + iSize) % iSize), ((initY % jSize) + jSize) % jSize);
            grid[((((initX - 1 ) % iSize) + iSize) % iSize)][((initY % jSize) + jSize) % jSize] = '.';
        } 
        if(check((((initX % iSize) + iSize) % iSize), (((initY + 1) % jSize) + jSize) % jSize)){
            addToPS(ps, (((initX % iSize) + iSize) % iSize), (((initY + 1) % jSize) + jSize) % jSize);
            grid[(((initX % iSize) + iSize) % iSize)][(((initY + 1) % jSize) + jSize) % jSize] = '.';
        } 
        if(check((((initX % iSize) + iSize) % iSize), (((initY - 1) % jSize) + jSize) % jSize)){
            addToPS(ps, (((initX % iSize) + iSize) % iSize), (((initY - 1) % jSize) + jSize) % jSize);
            grid[(((initX % iSize) + iSize) % iSize)][(((initY - 1) % jSize) + jSize) % jSize] = '.';
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
    vector<int> params;
    vector<int> lens;
    lens.push_back(1);
    for(int i = 0; i < 26501365; i++){
        Steps(ps);
        lens.push_back(ps.size());
        if( i % grid.size() == 26501365 % grid.size()){
            int len = 0;
            for(int j = 0; j < lens.size() - 1; j++){
                if(j % 2 == i %2){
                    len += lens[j];
                }
            }
            params.push_back(len);
        }
        if(params.size() == 3){break;}
    }
    long long p1 = params[0];
    long long p2 = params[1] - params[0];
    long long p3 = params[2] - params[1];
    long long ip = 26501365 / static_cast<long long>(grid.size());

    cout << p1 + p2 * ip + (ip * (ip - 1) / 2) * (p3 - p2) << endl;
    return 0;
}