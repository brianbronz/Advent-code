#include "../Allreference.h"

struct position{
    int x;
    int y;
};

struct position * init = new(position);
vector<string> grid;
int maxStep = 0;

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        grid.push_back(block);
    } 
    init->x = 0;
    init->y = 1;
    return -1;
}

bool check(unordered_set<struct position *> visited, struct position * ps) {
    for (unordered_set<struct position *>::iterator it = visited.begin(); it != visited.end(); ++it) {
        struct position *current = *it;
        if (current->x == ps->x && current->y == ps->y) {return true;}
    }
    return false;
}

void getLongestPath(struct position * start, int numSteps, 
    unordered_set<struct position *> visited,
    unordered_map<struct position *, int> &maxDistance){
    vector<struct position *> directions;
    struct position * E = new(position);
    directions.push_back(E);
    directions[0]->x = 1;
    directions[0]->y = 0;
    struct position * N = new(position);
    directions.push_back(N);
    directions[1]->x = 0;
    directions[1]->y = 1;
    struct position * W = new(position);
    directions.push_back(W);
    directions[2]->x = -1;
    directions[2]->y = 0;
    struct position * S = new(position);
    directions.push_back(S);
    directions[3]->x = 0;
    directions[3]->y = -1;
    visited.insert(start);
    if(numSteps < maxDistance[start]){
        return;
    }
    maxDistance[start] = numSteps;
    for (vector<struct position *>::iterator it = directions.begin(); it != directions.end(); ++it) {
        const struct position *direction = *it;
        struct position * newPs = new(position);
        newPs->x = start->x + direction->x;
        newPs->y = start->y + direction->y;
        if (newPs->x < 0 || newPs->y < 0 || newPs->x > grid.size() - 1 || newPs->y > grid.front().size() - 1 || check(visited, newPs)) {
            continue;
        }
        switch (grid[newPs->x][newPs->y]) {
            case '.':
                getLongestPath(newPs, numSteps + 1, visited, maxDistance);
                break;
            case 'v':
                newPs->x += directions[0]->x;
                newPs->y += directions[0]->y;
                if (!check(visited, newPs)) {getLongestPath(newPs, numSteps + 2, visited, maxDistance);}
                break;
            case '>':
                newPs->x += directions[1]->x;
                newPs->y += directions[1]->y;
                if (!check(visited, newPs)) {getLongestPath(newPs, numSteps + 2, visited, maxDistance);}
                break;
            case '^':
                newPs->x += directions[2]->x;
                newPs->y += directions[2]->y;
                if (!check(visited, newPs)) {getLongestPath(newPs, numSteps + 2, visited, maxDistance);}
                break;
            case '<':
                newPs->x += directions[3]->x;
                newPs->y += directions[3]->y;
                if (!check(visited, newPs)) {getLongestPath(newPs, numSteps + 2, visited, maxDistance);}
                break;
            }
        maxStep = max(maxStep, numSteps);
    }
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
    int numSteps = 0;
    unordered_set<struct position *> visited;
    unordered_map<struct position *, int> maxDistance;
    getLongestPath(init, numSteps, visited, maxDistance);
    cout << maxStep << endl;
    return 0;
}