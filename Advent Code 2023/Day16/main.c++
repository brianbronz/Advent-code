#include "../Allreference.h"

enum Direction{North, South, East, West};
Direction initialDirection = East;
int initX = 0;
int initY = 0;

bool check(int cx, int cy, vector<string> splitted, int y, int x, Direction cd, Direction d, bool start){
    return (cx < 0 || cy < 0 || cy >= splitted.size() || cx >= splitted.size() 
            || (cx == x && cy == y && cd == d && !start));
}

void visit(int x, int y, Direction dir, vector<string> splitted, vector<vector<int> > &visited){
    int currentX = x;
    int currentY = y;
    Direction currentDirection = dir;
    bool started = true;
    while (true){
        if (check(currentX, currentY, splitted, y, x, currentDirection, dir, started)){
            return;
        }
        bool visitedBefore = visited[currentY][currentX] == 1;
        visited[currentY][currentX] = 1;
        char terrain = splitted[currentY][currentX];
        Direction nextDirection = currentDirection;

        if (terrain == '\\') {
            if (currentDirection == North) {nextDirection = West;} 
            else if (currentDirection == East) {nextDirection = South;} 
            else if (currentDirection == West) {nextDirection = North;} 
            else if (currentDirection == South) {nextDirection = East;}
        } else if (terrain == '/') {
            if (currentDirection == North) {nextDirection = East;} 
            else if (currentDirection == East) {nextDirection = North;} 
            else if (currentDirection == West) {nextDirection = South;} 
            else if (currentDirection == South) {nextDirection = West;}
        } else if (terrain == '|') {
            if (currentDirection == West || currentDirection == East) {
                if (!visitedBefore) {
                    visit(currentX, currentY - 1, North, splitted, visited);
                    visit(currentX, currentY + 1, South, splitted, visited);
                }
                return;
            } else {nextDirection = currentDirection;}
        } else if (terrain == '-') {
            if (currentDirection == South || currentDirection==North) {
                if (!visitedBefore) {
                    visit(currentX - 1, currentY, West, splitted, visited);
                    visit(currentX + 1, currentY, East, splitted, visited);
                }
                return;
            } else {nextDirection = currentDirection;}
        }
        if (nextDirection == West) {currentX = currentX - 1;} 
        else if (nextDirection == East) {currentX = currentX + 1;}

        if (nextDirection == North) {currentY = currentY - 1;} 
        else if (nextDirection == South) {currentY = currentY + 1;}
        currentDirection = nextDirection;
    }
}
int nextMoves(int x, int y, Direction direction, vector<string> splitted){
    static vector< vector<int> > visitedNode(splitted.size(), vector<int>(splitted.size(), 0));
    for (auto it = visitedNode.begin(); it != visitedNode.end(); ++it) {
        for (auto innerIt = it->begin(); innerIt != it->end(); ++innerIt) {
            *innerIt = 0;
        }
    }
    visit(x, y, direction, splitted, visitedNode);
    long totalSum = 0;
    for (const auto &row : visitedNode) {
        for (int i = 0; i < row.size(); i++){
            totalSum += row[i];
        }
    }
    return totalSum;

}
void part1(vector<string> & splitted){
    cout << nextMoves(initX, initY, initialDirection, splitted) << endl;
}

void part2(vector<string> splitted){
    vector<int> results;
    for (int i = 0; i < splitted.size(); i++){
        results.push_back(nextMoves(i, 0, South, splitted));
        results.push_back(nextMoves(i, splitted.size() - 1, North, splitted));
        results.push_back(nextMoves(0, i, East, splitted));
        results.push_back(nextMoves(splitted.size() - 1, i, West, splitted));
    }
    int maxResult = 0;
    for(int i = 0; i < results.size(); i++){
        if(results[i] > maxResult){maxResult = results[i];}
    }
    cout << maxResult << endl;;
}
int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> splitted;
    while(getline(input, block)){
        splitted.push_back(block);
    };

    part1(splitted);
    part2(splitted);
    return -1;
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

