#include "../Allreference.h"

#include <queue>
#include <tuple>
#include <set>

struct State{
    int heatLoss;
    int x;
    int y;
    int directionR;
    int directionC;
    int steps;

    bool operator>(struct State* other){return heatLoss > other->heatLoss;};
};

struct MyTuple{
    int a;
    int b;
    int c;
    int d;
    int e;
};

bool check(set< struct MyTuple*> ab, struct MyTuple* bb){
    for(set<struct MyTuple*>::iterator it = ab.begin(); it != ab.end(); ++it){
        if(bb->a == (*it)->a && bb->b == (*it)->b && bb->c == (*it)->c && bb->d == (*it)->d && bb->e == (*it)->e){
            return true;
        }
    }
    return false;
}

int minHeatLoss(vector< vector<int> > & grid){
    int total = 100000000;
    int numRows = grid.size();
    int numColumns = grid[0].size();
    set< struct MyTuple *> visited;
    vector<pair <int, int> > pairDirection;
    pairDirection.push_back(make_pair(0, 1));
    pairDirection.push_back(make_pair(1, 0));
    pairDirection.push_back(make_pair(0, -1));
    pairDirection.push_back(make_pair(-1, 0));
    priority_queue<struct State* ,  vector<struct State*>, greater<struct State*> > priorityQ;
    struct State * initial = new(State);
    initial->heatLoss = 0; 
    initial->directionC = 0; 
    initial->directionR = 0; 
    initial->x = 0; 
    initial->y = 0; 
    initial->steps = 0;
    priorityQ.push(initial);
    ofstream f("output.txt");
    while(!priorityQ.empty()){
        //Take the first element
        struct State* currentState = priorityQ.top();
        priorityQ.pop();

        int currentHL = currentState->heatLoss;
        int currentDC = currentState->directionC;
        int currentDR = currentState->directionR;
        int currentX = currentState->x;
        int currentY = currentState->y;
        int currentS = currentState->steps;
        f << currentX << " " << currentY << " " << currentHL <<endl;
        if(currentX == numRows - 1 && currentY == numColumns - 1){
            total = currentHL;
            break;
        }
        struct MyTuple * newTuple = new(MyTuple);
        newTuple->a = currentX;
        newTuple->b = currentY;
        newTuple->c = currentDR;
        newTuple->d = currentDC;
        newTuple->e = currentS;
        //check how to do
        if(check(visited, newTuple)){
            continue;
        }

        visited.insert(newTuple);
        if(currentS < 3 && (currentDR != 0 || currentDC != 0)){
            int actualR = currentX + currentDR;
            int actualC = currentY + currentDC;
            if(actualR >= 0 && actualR < numRows && actualC >= 0 && actualC < numColumns){ 
                struct State* addNewState = new(State);
                addNewState->steps = currentS + 1;
                addNewState->heatLoss = currentHL + grid[actualR][actualC];
                addNewState->x = actualR;
                addNewState->y = actualC;
                addNewState->directionC = currentDC;
                addNewState->directionR = currentDR;
                priorityQ.push(addNewState);
            }

        }

        for(pair <int, int> direction: pairDirection){
            int nDirectionR = direction.first;
            int nDirectionC = direction.second;
            if((nDirectionR != currentDR || nDirectionC != currentDC) && 
               (nDirectionR != -currentDR || nDirectionC != -currentDC)){
                int actualR = currentX + nDirectionR;
                int actualC = currentY + nDirectionC;
                if(actualR >= 0 && actualR < numRows && actualC >= 0 && actualC < numColumns){
                    int addHL = grid[actualR][actualC];
                    struct State* addNewState = new(State);
                    addNewState->steps = 1;
                    addNewState->heatLoss = currentHL + addHL;
                    addNewState->x = actualR;
                    addNewState->y = actualC;
                    addNewState->directionC = nDirectionC;
                    addNewState->directionR = nDirectionR;
                    priorityQ.push(addNewState);
                }
            }
        }
    }
    cout << total << endl;
    f.close();
    return -1;
}

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector< vector<int> > grid;
    while(getline(input, block)){
        vector<int> row;
        for(int i = 0; i < block.size(); i++){
            int value = int(block[i] - '0');
            row.push_back(value);
        }
        grid.push_back(row);
    };

    int total = minHeatLoss(grid);
    return 1;
}
int main(int argc, char * argv[]) {
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