#include "../Allreference.h"

vector<int> Numbers;

string checkValue(string temp){
    if(temp.find("one") != string::npos){
        return "1";
    } else if(temp.find("two") != string::npos){
        return "2";
    } else if(temp.find("three") != string::npos){
        return "3";
    } else if(temp.find("four") != string::npos){
        return "4";
    } else if(temp.find("five") != string::npos){
        return "5";
    } else if(temp.find("six") != string::npos ){
        return "6";
    } else if(temp.find("seven") != string::npos){
        return "7";
    } else if(temp.find("eight")!= string::npos){
        return "8";
    } else if(temp.find("nine")!= string::npos){
        return "9";
    }
    return "-1";
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        bool first = true;
        string firstD = " ";
        string secondD = " ";
        int num = -1;
        for (int i = 0; i < block.length(); i++){
            //case number
            if(isdigit(block[i])){
                if (first){
                    firstD = block[i];
                    first = false;
                } else {
                    secondD = block[i];
                }
            } else {
                //case string
                string temp = "";
                int difference = 0;
                for (int j = i; j < block.length(); j++){
                    if (isdigit(block[j])){
                        difference = j;
                        break;
                    } else {
                        temp += block[j];
                        if (checkValue(temp) != "-1"){
                            if (first){
                                firstD = checkValue(temp);
                                first = false;
                            } else {
                                secondD = checkValue(temp);
                            }
                            temp = "";
                        }
                    }
                }
                if (difference != 0){
                    i = difference - 1;
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
        cout << Numbers[i] << endl;
    }
    cout << sum << endl;
    return 1;
}