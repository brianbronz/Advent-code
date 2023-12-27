#include "../Allreference.h"

//direzione
//grid
vector<pair<int, int> > grid;

long long areaValue(vector<pair<int, int> > grid){
	//Shoelace formula
	long long res = 0;
	int previousX = grid.back().first;
	int previousY = grid.back().second;
	for(int i = 0; i < grid.size(); i++){
		int x = grid[i].first;
		int y = grid[i].second;
		res += (previousX + x) * (previousY - y);
		previousX = x;
		previousY = y;
	}
	return abs(res / 2);
}
int readFiles(istream & input, const char * argv){
	vector<int> dir_x;
	dir_x.push_back(1);
	dir_x.push_back(0);
	dir_x.push_back(-1);
	dir_x.push_back(0);
	vector<int> dir_y;
	dir_y.push_back(0);
	dir_y.push_back(1);
	dir_y.push_back(0);
	dir_y.push_back(-1);
	string directions = "RDLU";
	string actualDir = "";
	string color;
	int len = 0;
	int x = 0;
	int y = 0;
	int boundCount =0;
	while(input >> actualDir >> len >> color){
		int index = directions.find(actualDir);
		x += len * dir_x[index];
		y += len * dir_y[index];
		boundCount += len;
		pair<int, int> position = make_pair(x, y);
		grid.push_back(position);
	}
	long long area = areaValue(grid);
	long long interior = area - boundCount /2 + 1;
	cout << interior + boundCount << endl;
	return interior + boundCount;
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