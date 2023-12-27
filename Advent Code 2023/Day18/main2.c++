#include "../Allreference.h"

//direzione
//grid
vector<pair<int, int> > grid;

long long areaValue(vector<pair<int, int> > grid){
	//Shoelace formula
	long long res = 0;
	long long previousX = grid.back().first;
	long long previousY = grid.back().second;
	for(int i = 0; i < grid.size(); i++){
		long long x = grid[i].first;
		long long y = grid[i].second;
		res += (previousX + x) * (previousY - y);
		previousX = x;
		previousY = y;
	}
	return abs(res / 2);
}

//esempio: 952408144115
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
	long long len = 0;
	long long x = 0;
	long long y = 0;
	long long boundCount =0;
	while(input >> actualDir >> len >> color){
        len = strtol(color.substr(2, 5).c_str(), NULL, 16);
		int index = color[7] - '0';
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