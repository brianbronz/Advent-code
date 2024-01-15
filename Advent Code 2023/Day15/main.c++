#include "../Allreference.h"

int hashAlgorithm(string str) {
    int result = 0;
    for (int i = 0; i < str.size(); i++) {
        result = result + static_cast<int>(str[i]);
        result = result * 17;
        result = result % 256;
    }
    return result;
}

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    vector<string> splitted;
    while(getline(input, block, ',')){
        splitted.push_back(block);
    };

    int total = 0;
    for (int i = 0; i < splitted.size(); i++) {
        total += hashAlgorithm(splitted[i]);
    }
    cout << total << endl;
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
