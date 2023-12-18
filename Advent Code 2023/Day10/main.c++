#include "../Allreference.h"

//=> coordinate
//=> mappa di caratteri + la direzione
//=> valid pipe:
/**
 * | => NS
 * L => NE
 * - => EW
 * J => NW
 * 7 => SW
 * F => SE
 */
// . not valid
// S => starting position
struct position{
    int x;
    int y;
    string direction;//NS
    char symbol;
};
int direction = 0;
int initPositionX = 0;
int initPositionY = 0;
vector<string> lines;
vector<struct position *> ps;
int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while(getline(input, block)){
        lines.push_back(block);
    }

    for (int i = 0; i < lines.size(); i++){
        for (int j = 0; j < lines[i].size(); j++){
            if (lines[i][j] == 'S'){
                initPositionX = i;//what is the initial row
                initPositionY = j;//what is the initial column
            }
        }
    }
    return 1;
}

void addNewposition(int x, int y, vector<struct position*> &a){
    struct position * newPs = new(position);
    newPs->x = x;
    newPs->y = y;
    a.push_back(newPs);
}
int nextMoves(int direction, vector<struct position *> &a){
    //current position => initial is initPositionX and initPositionY
    int distance = 0;
    int cPositionX = initPositionX;
    int cPositionY = initPositionY;
    while(direction != 0){
        if(direction == 1 && cPositionY - 1 >= 0){
            //West
            //isValid => i.e. if the symbol is L or - or F
            if(lines[cPositionX][cPositionY - 1] == 'L'){
                addNewposition(cPositionX, cPositionY-1, a);
                direction = 2;
            } else if(lines[cPositionX][cPositionY - 1] == '-'){
                direction = 1;
            } else if(lines[cPositionX][cPositionY - 1] == 'F'){
                addNewposition(cPositionX, cPositionY-1, a);
                direction = 4;
            } else if(lines[cPositionX][cPositionY - 1] == '.'){
                direction = 0;
                break;
            } else {
                cPositionX = initPositionX;
                cPositionY = initPositionY;
                distance++;
                break;
            }
            distance++;
            cPositionY--;
        } else if(direction == 2 && cPositionX - 1 >= 0){
            //North
            //isValid => i.e. if the symbol is | or 7 or F
            if(lines[cPositionX - 1][cPositionY] == '|'){
                direction = 2;
            } else if(lines[cPositionX - 1][cPositionY] == '7'){
                addNewposition(cPositionX - 1, cPositionY, a);
                direction = 1;
            } else if(lines[cPositionX - 1][cPositionY]== 'F'){
                addNewposition(cPositionX - 1, cPositionY, a);
                direction = 3;
            } else if(lines[cPositionX - 1][cPositionY]== '.'){
                direction = 0;
                break;
            } else {
                cPositionX = initPositionX;
                cPositionY = initPositionY;
                distance++;
                break;
            }
            distance++;
            cPositionX--;
        } else if(direction == 3 && cPositionY + 1 < lines[0].size()){
            //isValid => i.e. if the symbol is J or - or 7
            if(lines[cPositionX][cPositionY + 1] == 'J'){
                addNewposition(cPositionX, cPositionY+1, a);
                direction = 2;
            } else if(lines[cPositionX][cPositionY + 1] == '-'){
                direction = 3;
            } else if(lines[cPositionX][cPositionY + 1] == '7'){
                addNewposition(cPositionX, cPositionY+1, a);
                direction = 4;
            } else if(lines[cPositionX][cPositionY + 1] == '.'){
                direction = 0;
                break;
            } else {
                cPositionX = initPositionX;
                cPositionY = initPositionY;
                distance++;
                break;
            }
            distance++;
            cPositionY++;
        } else if(direction == 4 && cPositionX + 1 < lines.size()){
            //isValid => i.e. if the symbol is L or | or J
            if(lines[cPositionX + 1][cPositionY] == '|'){
                direction = 4;
            } else if(lines[cPositionX + 1][cPositionY] == 'L'){
                addNewposition(cPositionX + 1, cPositionY, a);
                direction = 3;
            } else if(lines[cPositionX + 1][cPositionY] == 'J'){
                addNewposition(cPositionX + 1, cPositionY, a);
                direction = 1;
            } else if(lines[cPositionX + 1][cPositionY]== '.'){
                direction = 0;
                break;
            } else {
                cPositionX = initPositionX;
                cPositionY = initPositionY;
                distance++;
                break;
            }
            distance++;
            cPositionX++;
        } else {
            break;
        }
        
        if(lines[cPositionX][cPositionY] == 'S'){break;}
    }
    
    if(cPositionX == initPositionX && cPositionY == initPositionY){
        distance = floor(distance / 2);
    }
    cout << distance << endl;
    return distance;
};

int interiorPoints(int area, int boundary_points) {
    return area + 1 - (boundary_points);
}

int area(vector<struct position*> &points) {
    int areaVal =0;
    vector<struct position* > current, next;
    current = points;
    next = points;
    int firstX = current[0]->x;
    int firstY = current[0]->y;
    ofstream o("test1.txt");
    for (int i = 1; i < points.size() - 1; i+= 1) {
        int x1 = current[i - 1]->x;
        int y2 = next[i]->y;
        int x2 = next[i]->x;
        int y1 = current[i - 1]->y;
        int currEval = (x1 * y2) - (x2 * y1);
        areaVal += currEval;
        o << x1 << " " << y2 << " " << x2 << " " << y1 << endl;
    }

    int x2 = current[points.size() - 1]->x;
    int y2 = current[points.size() - 1]->y;

    int currEval = (x2 * firstY) - (firstX * y2);
    areaVal += currEval;

    return areaVal / 2;
}

void path(){
    vector<struct position *> psW;
    int westDirection = nextMoves(1, psW);
    vector<struct position *> psS;
    int southDirection = nextMoves(4, psS);
    vector<struct position *> psN;
    int northDirection = nextMoves(2, psN);
    vector<struct position *> psE;
    int EastDirection = nextMoves(3, psE);
    double max1 = max(westDirection, southDirection);
    double max2 = max(northDirection, EastDirection);
    double res = max(max1, max2);
    vector<struct position*> temp1;
    vector<struct position*> temp2;
    vector<struct position*> final1;
    if(southDirection > westDirection){temp1 = psS;} else {temp1 = psW;}
    if(northDirection > EastDirection){temp2 = psN;} else {temp2 = psE;}
    if(temp1.size() > temp2.size()){final1 = temp1;} else{final1 = temp2;}
    //final1 tutti i punti
    //cout << res << endl;
    int shape_area = area(final1);
    if (shape_area < 0) {
        shape_area = shape_area * -1;
    }
    int innerTiles = interiorPoints(shape_area, res);
    cout << innerTiles << endl;
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
    path();
}