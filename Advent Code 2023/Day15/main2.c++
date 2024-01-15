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
    
    vector<vector<pair<string, int> > > boxes(256);
    for(int i = 0; i < splitted.size(); i++){
        if (splitted[i].find('-') != string::npos) {
            string temp = splitted[i].substr(0, splitted[i].size() - 1);
            for(vector<vector<pair<string, int> > >::iterator box_it = boxes.begin(); box_it != boxes.end(); ++box_it) {
                vector<pair<string, int> > &box = *box_it;
                for (vector<pair<string, int> >::iterator it = box.begin(); it != box.end(); ) {
                     (it->first == temp)? it = box.erase(it): ++it; 
                }
            }
        } else {
           string label = splitted[i].substr(0, splitted[i].find('='));
           int level = stoi(splitted[i].substr(splitted[i].find('=') + 1));
           vector<pair<string, int> > & target = boxes[hashAlgorithm(label)];
           bool replaced = false;
           for(int i = 0; i < target.size(); i++){
               if (target[i].first == label){
                  target[i].second = level;
                  replaced = true;
                  break;
               }
           }
           if (!replaced){
               target.push_back(make_pair(label, level));
           }
        }

    }

    int output = 0;
    for (int i = 0; i < boxes.size(); i++) {
       for (int j = 0; j < boxes[i].size(); j++) {
           output += (i+1) * (j+1) * boxes[i][j].second;
       }
    }
    cout << output << endl;
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