#include "../Allreference.h"

map<string, int> names;
vector<pair<int, int> > pairs;
vector<vector<int> > edges;
bool check(string name){
    for(map<string, int>::iterator it = names.begin(); it != names.end(); ++it){
        if(it->first == name){return true;}
    }
    return false;
}

int getIndex(string name){
    if(check(name)){return names[name];}
    int index = names.size();
    names[name] = index;
    return index;
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        vector<string> acronyms;
        stringstream ss(block);
        string temp;
        while(ss >> temp){
            acronyms.push_back(temp);
        }
        acronyms[0] = acronyms[0].substr(0, acronyms[0].size() - 1);
        int index_ = getIndex(acronyms[0]);
        for(int i = 1; i < acronyms.size(); i++){
            int toAdd = getIndex(acronyms[i]);
            pairs.push_back(make_pair(index_, toAdd));
        }
    } 
    edges.resize(names.size(), vector<int>(names.size(), 0));
    for (int i = 0; i < pairs.size(); i++){
        edges[pairs[i].first][pairs[i].second] = 1;
        edges[pairs[i].second][pairs[i].first] = 1;
    }
    return -1;
}

int maxElementIndex(vector<int> w){
    int maxValue = 0;
    int index1 = 0;
    for(int i = 0; i < w.size() ; i++){
        if(w[i] > maxValue){
            maxValue = w[i];
            index1 = i;
        }
    }
    return index1;
}
pair<int, vector<int> > minCut(){
    vector<int> init;
    pair<int, vector<int> > best = make_pair(INT_MAX, init);
    int n = edges.size();
    vector<vector <int> > initial;
    initial.resize(n);
    for(int i = 0; i < n; i++){
        initial[i].push_back(i);
    }
    for (int i = 1; i < n; i++){
        vector<int> weight = edges[0];
        int s = 0;
        int t = 0;
        for(int j = 0; j < n - i; j++){
            weight[t] = INT_MIN;
            s = t;
            t = maxElementIndex(weight);
            for(int k = 0; k < n; k++){
                weight[k] += edges[t][k];
            }
        }
        pair<int, vector<int> > compare = make_pair(weight[t] - edges[t][t], initial[t]);
        best = min(best, compare);
        initial[s].insert(initial[s].end(), initial[t].begin(), initial[t].end());
        for (int i = 0; i < n; i++){
            edges[s][i] += edges[t][i];
            edges[i][s] = edges[s][i];
        }  
        edges[0][t] = INT_MIN;
    }
    return best;
}

void part1(){
    long long solution = 0;
    pair<int, vector<int> > ret = minCut();
    cout << ret.second.size() * (names.size() - ret.second.size()) << endl;;
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
    part1();
    return 0;
}