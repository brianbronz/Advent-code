#include "../Allreference.h"

vector<string> lines;
vector<vector<int> > hs;

int readFiles(istream & input, const char * argv){
    string block;
    //get all lines
    while(getline(input, block)){
        lines.push_back(block);
    }
    //remove space
    for(int i = 0; i < lines.size(); i++){
        vector<string> numbers;
        stringstream ss(lines[i]);
        string temp;
        while(getline(ss, temp, ' ')){
            numbers.push_back(temp);
        }
        vector<int> h;
        for(int j = 0; j < numbers.size(); j++){
            h.push_back(stoi(numbers[j]));
        }
        hs.push_back(h);
    }
    return 1;
}

bool check(vector<int> diff){
    for (int i = 0; i < diff.size(); i++){
        if(diff[i] != 0){return true;}
    }
    return false;
}

void differences(){
    vector<vector<int> > diffs;
    vector<int> diff;
    vector<int> sums;
    vector<int> sums2;
    for(int q = 0; q < hs.size(); q++){
        diffs.clear();
        diff.clear();
        diffs.push_back(hs[q]);
        
        while(diff.empty() || check(diff)){
            diff.clear();
            for(int i = 0; i < diffs[diffs.size() - 1].size() - 1; i++)
                diff.push_back(diffs[diffs.size() - 1][i + 1] - diffs[diffs.size() - 1][i]);
            diffs.push_back(diff);
        }
        //Part 1
        int sumValue = 0;
        for(int d = 0; d < diffs.size(); d++)
            sumValue += diffs[d][diffs[d].size() - 1];
        sums.push_back(sumValue);

        //Part 2
        int eValue = 0;
        for(int i = diffs.size() - 1; i > -1; i--)
            eValue = diffs[i][0] - eValue;
        sums2.push_back(eValue);
    }

    long total = 0;
    for(int s = 0; s < sums.size(); s++)
        total += sums[s];

    long total2 = 0;
    for(int s = 0; s < sums2.size(); s++)
        total2 += sums2[s];
    cout << total << endl;
    cout << total2 << endl;
}

int main(int argc, char * argv[]){
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
    differences();
}
