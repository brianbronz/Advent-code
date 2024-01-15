#include "../Allreference.h"

vector<vector<int> > input2;
map<string, pair<int, map<string, int> > > graph;
int rows, columns;
int result = INT_MAX;

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while (getline(input,  block)) {
        vector<int> row;
        for (int i = 0; i < block.size(); ++i) {
            row.push_back(block[i] - '0');
        }
        input2.push_back(row);
    return -1;
    }
}

void walk(const string& neighbor, int heat) {
    if (heat >= min(graph[neighbor].first, result)) return;
    if (neighbor.substr(neighbor.find(":")) == ":" + to_string(columns - 1) + to_string(rows - 1)) {
        result = heat;
        return;
    }
    graph[neighbor].first = heat;
    map<string, int>& neighbors = graph[neighbor].second;
    for (map<string, int>::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
        walk(it->first, heat + it->second);
    }
}

void part1(){
    rows = input2.size();
    columns = input2[0].size();
    
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            string vertical =  ":" + to_string(x)  + to_string(y) ;
            string horizontal = ":" + to_string(x) +  to_string(y) ;
            graph[":" + to_string(x)  + to_string(y)] = make_pair(INT_MAX, map<string, int>());
            graph[":" + to_string(x) +  to_string(y)] = make_pair(INT_MAX, map<string, int>());
            for (int i = 1; i <= 3; i++) {
                if (y + i >= 0 && y + i < rows)
                    graph[vertical].second[to_string(x) + to_string(y + i)] = accumulate(input2[y + i].begin(), input2[y + i].end(), 0);
                if (y - i >= 0 && y - i < rows)
                    graph[vertical].second[to_string(x) + to_string(y - i)] = accumulate(input2[y - i].begin(), input2[y - i].end(), 0);
                if (x + i >= 0 && x + i < columns)
                    graph[horizontal].second[to_string(x + i) + to_string(y)] = accumulate(input2[y].begin() + x + 1, input2[y].begin() + x + i + 1, 0);
                if (x - i >= 0 && x - i < columns)
                    graph[horizontal].second[to_string(x - i) + to_string(y)] = accumulate(input2[y].begin() + x - i, input2[y].begin() + x, 0);
            }
        }
    }
    
    map<string, int> startingNeighbors;

    map<string, int>& horizontalNeighbors = graph["00"].second;
    for (map<string, int>::iterator it = horizontalNeighbors.begin(); it != horizontalNeighbors.end(); ++it) {
        startingNeighbors[it->first] = it->second;
    }

    map<string, int>& verticalNeighbors = graph["00"].second;
    for (map<string, int>::iterator it = verticalNeighbors.begin(); it != verticalNeighbors.end(); ++it) {
        startingNeighbors[it->first] = it->second;
    }

    for (map<string, int>::iterator it = startingNeighbors.begin(); it != startingNeighbors.end(); ++it) {
        walk(it->first, it->second);
    }
  
    cout << result << endl;  
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

    part1();       
    return 0;
}