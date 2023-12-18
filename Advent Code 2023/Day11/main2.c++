#include "../Allreference.h"


struct position{
    double x;
    double y;
};

vector<struct position*> ps;
vector< vector<string> > grid;
vector< vector<string> > temp;
int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while(getline(input, block)){
        vector<string> row;
        vector<string> exRow;
        bool isEmptyR = true;
        for (int i = 0; i < block.size(); i++){
            string str(1, block[i]);
            row.push_back(str);
            exRow.push_back("A");
            if(str == "#"){
                isEmptyR = false;
            }
        }
        temp.push_back(row);
        if(isEmptyR){
            temp.push_back(exRow);
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
                grid[j].push_back("A");
            }
        }
    }
    return 1;
}

void findPair(){
    //grid and temp
    //ps vectpr
    cout << grid.size() << endl;
    vector<double> previousRow (grid.size(), 0);
    vector<double> previousColumn (grid[0].size(), 0);
    for (int i = 1; i < grid.size(); i++){
        bool isExpanded = true;
        for (int j = 0; j < grid[0].size(); j++){
            if(grid[i][j] != "A"){
                isExpanded = 0;
            }
        }
        if(isExpanded){
            previousRow[i] = previousRow[i - 1] + 1;
        } else {
            previousRow[i] = previousRow[i - 1];
        }
    }

    for (int j = 1; j < grid[0].size(); j++){
        bool isExpanded = true;
        for (int i = 0; i < grid.size(); i++){
            if(grid[i][j] != "A"){
                isExpanded = false;
            }
        }
        if(isExpanded){
            previousColumn[j] = previousColumn[j - 1] + 1;
        } else {
            previousColumn[j] = previousColumn[j - 1];
        }
    }

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


    //totale
    double total = 0;
    for (int i = 0; i < ps.size() - 1; i++){
        for (int j = i + 1; j < ps.size(); j++){
            double x1 = ps[i]->x;
            double y1 = ps[i]->y;
            double x2 = ps[j]->x;
            double y2 = ps[j]->y;
            double preR = abs(previousRow[x2] - previousRow[x1]);
            double preC = abs(previousColumn[y2] - previousColumn[y1]);
            total += abs(x1 - x2) + abs(y1 - y2) + preR * 999998 + preC * 999998;
        }
    }
    cout << fixed << setprecision(2)<<total << endl;
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
    findPair();
    return 0;
}
