#include "../Allreference.h"

vector<int> Numbers;

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        bool first = true;
        string firstD = " ";
        string secondD = " ";
        int num = -1;
        for (int i = 0; i < block.length(); i++){
            if(isdigit(block[i])){
                if (first){
                    firstD = block[i];
                    first = false;
                } else {
                    secondD = block[i];
                }
            }
        }
        if (secondD == " "){
            num = stoi(firstD + firstD);
        } else {
            num = stoi(firstD + secondD);
        }
        Numbers.push_back(num);
    }
    return 1;
}

int main(int argc, char * argv[]){
    cout << argv[1] << endl;
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

    int sum = 0;
    for (int i = 0; i < Numbers.size(); i++){
        sum += Numbers[i];
    }
    cout << sum << endl;
    return 1;
}