#include "../Allreference.h"

struct node{
    int x;
    int y;
};

vector<struct node*> visited;
bool isVisited(int initX, int initY){
    for(int i = 0; i < visited.size(); i++){
        if(visited[i]->x == initX && visited[i]->y == initY){
            return true;
        }
    }
    return false;
}
struct node * initAnewStruct(int initX, int initY){
    struct node * newN = new(node);
    newN->x = initX;
    newN->y = initY;
    return newN;
}
//Colonne e righe invertite
void nextMoves(int initX, int initY, string direction, vector<string> & splitted){
    cout << initX << " " << initY << " " << splitted[initX][initY] << " " << direction <<endl;
    if(direction == "E"){
        if(initX + 1 < splitted[0].size()){
            if(!isVisited(initX + 1, initY)){
                struct node * newNode = initAnewStruct(initX + 1, initY);
                visited.push_back(newNode);
            }
            initX++; 
            if(splitted[initX][initY] == '/'){
                nextMoves(initX, initY, "N", splitted);
            } else if(splitted[initX][initY] == '\\' ){
                nextMoves(initX, initY, "S", splitted);
            } else if(splitted[initX][initY] == '|'){
                nextMoves(initX, initY, "S", splitted);
                nextMoves(initX, initY, "N", splitted);
            } else if(splitted[initX][initY] == '-' || splitted[initX][initY] == '.'){
                nextMoves(initX, initY, "E", splitted);
            }
        } else{
            return;
        }
    } else if(direction == "N"){
        if(initY - 1 >= 0){
            if(!isVisited(initX, initY - 1)){
                struct node * newNode = initAnewStruct(initX, initY - 1);
                visited.push_back(newNode);
            }
            initY--; 
            if(splitted[initX][initY] == '/'){
                nextMoves(initX, initY, "E", splitted);
            } else if(splitted[initX][initY] == '\\'){
                nextMoves(initX, initY, "W", splitted);
            } else if(splitted[initX][initY] == '|' || splitted[initX][initY] == '.'){
                nextMoves(initX, initY, "N", splitted);
            } else if(splitted[initX][initY] == '-'){
                nextMoves(initX, initY, "E", splitted);
                nextMoves(initX, initY, "W", splitted);
            }
        } else{
            return;
        }
    } else if(direction == "W"){
        if(initX - 1 >= 0){
            if(!isVisited(initX - 1, initY)){
                struct node * newNode = initAnewStruct(initX - 1, initY);
                visited.push_back(newNode);
            }
            initX--; 
            if(splitted[initX][initY] == '/'){
                nextMoves(initX, initY, "S", splitted);
            } else if(splitted[initX][initY] == '\\'){
                nextMoves(initX, initY, "N", splitted);
            } else if(splitted[initX][initY] == '|'){
                nextMoves(initX, initY, "S", splitted);
                nextMoves(initX, initY, "N", splitted);
            } else if(splitted[initX][initY] == '-' || splitted[initX][initY] == '.'){
                nextMoves(initX, initY, "W", splitted);
            }
        } else{
            return;
        }
    } else if(direction == "S"){
        if(initY + 1 < splitted.size()){
            if(!isVisited(initX, initY + 1)){
                struct node * newNode = initAnewStruct(initX, initY + 1);
                visited.push_back(newNode);
            }
            initY++; 
            if(splitted[initX][initY] == '/'){
                nextMoves(initX, initY, "W", splitted);
            } else if(splitted[initX][initY] == '\\'){
                nextMoves(initX, initY, "E", splitted);
            } else if(splitted[initX][initY] == '|' || splitted[initX][initY] == '.'){
                nextMoves(initX, initY, "S", splitted);
            } else if(splitted[initX][initY] == '-'){
                nextMoves(initX, initY, "E", splitted);
                nextMoves(initX, initY, "W", splitted);
            }
        } else{
            return;
        }
    } else {
        return;
    }
}
void part1(vector<string> & splitted){
    string initialDirection = "E";
    int initX = 0;
    int initY = 0;
    nextMoves(initX, initY, initialDirection, splitted);
    cout << visited.size() << endl;
}
int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> splitted;
    while(getline(input, block)){
        splitted.push_back(block);
    };
    vector<string> a;
    for (int i = 0; i < splitted.size(); i++){
        string temp;
        for (int j = 0; j < splitted[i].size(); j++){
            temp += splitted[j][i];
        }
        a.push_back(temp);
    }
    part1(splitted);
    
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
