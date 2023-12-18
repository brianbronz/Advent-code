#include "../Allreference.h"

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> splitted;
    while(getline(input, block, ',')){
        splitted.push_back(block);
    };
    unordered_map<string, int> Map;

    for (int i = 0; i < splitted.size(); i++) {
        if (splitted[i].find('=') != string::npos) {
            vector<string> splitByEquals;
            stringstream ss(splitted[i]);
            string substring;
            while(getline(ss, substring, '=')){
                splitByEquals.push_back(substring);
            }
            Map[splitByEquals[0]] = stoi(splitByEquals[1]);
        } else {
            vector<string> splitByMinus;
            stringstream ss(splitted[i]);
            string substring;
            while(getline(ss, substring, '-')){
                splitByMinus.push_back(substring);
            }
            Map.erase(splitByMinus[0]);
        }
    }

    int total2 = 0;

     for (int i = 0; i < Map.bucket_count(); i++) {
        int bSize = Map.bucket_size(i);
        for (unordered_map<string, int>::local_iterator it = Map.begin(i); it != Map.end(i); ++it) {
            total2 += (i + 1) * bSize * it->second;
            bSize--;
        }
    }
    
    cout << total2;
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