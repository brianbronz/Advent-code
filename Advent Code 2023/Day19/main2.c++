#include "../Allreference.h"
struct Rules{
    string name;
    vector<struct Condition*> cond;
};

struct Condition{
    string variable;
    string operation;
    int secondValue;
    string destination;
};
unordered_map<string, vector<struct Rules *> > Map;
unordered_map <string, vector<string> >ap;
vector<struct Rules*> rls;
long long total = 0;
string init = "in";

void addRules(string block){
    int openBrackets = block.find("{");
    string name = block.substr(0, openBrackets);
    int closedbrackets = block.find("}");
    string allConditions = block.substr(openBrackets + 1, closedbrackets - 1 - openBrackets);
    //Rules
    struct Rules * newRules = new(Rules);
    //Condition
    vector<string> vLines;
    stringstream ss(allConditions);
    string temp;
    while(getline(ss, temp, ',')){
        vLines.push_back(temp);
    }
    for (int i = 0; i < vLines.size() - 1; i++){
        string temp1 = vLines[i];
        //variable
        string variableName = "";
        variableName += temp1[0];
        //operator
        string operation = "";
        operation += temp1[1];
        //valuecondition + destination
        vector<string> twoValue;
        stringstream ss1(temp1.substr(2));
        string temp2;
        while(getline(ss1, temp2, ':')){
            twoValue.push_back(temp2);
        };
        struct Condition * lastC = new (Condition);
        lastC->destination = twoValue[1];
        lastC->operation = operation;
        lastC->secondValue = stoi(twoValue[0]);
        lastC->variable = variableName;
        newRules->cond.push_back(lastC);
    }
    struct Condition * lastC = new (Condition);
    lastC->destination = vLines[vLines.size() - 1];
    lastC->operation = "";
    lastC->secondValue = -1;
    lastC->variable = "";
    newRules->cond.push_back(lastC);
    newRules->name = name;
    rls.push_back(newRules);
    for(int i = 0; i < rls.size(); i++){
        for(int j = 0; j<rls[i]->cond.size(); j++){
            cout << rls[i]->cond[j]->destination << endl;
        }
    }
    Map.insert(make_pair(name,rls));
    rls.clear();
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        cout << block << endl;
        if(block.empty()){
            break;
        }
        addRules(block);
    }

    return 1;
}

vector<string> allDestinationsToA;
void findPath(const std::string& current, const std::string& destination, std::vector<std::string>& path, std::unordered_set<std::string>& visited) {
    if (current == destination) {
        string pathRes = "";
        for (const auto& node : path) {
            pathRes += node + " ";
        }
        allDestinationsToA.push_back(pathRes + destination);
        return;
    }

    if (visited.find(current) != visited.end()) {
        return;
    }

    visited.insert(current);
    path.push_back(current);

    if (ap.find(current) != ap.end()) {
        for (const auto& dest : ap[current]) {
            findPath(dest, destination, path, visited);
        }
    }

    path.pop_back();
    visited.erase(current);
}

void part2(){
    string init = "in";
    std::vector<std::string> path;
    std::unordered_set<std::string> visited;
    std::string start = "in";
    std::string goal = "A";

    findPath(start, goal, path, visited);
    auto last = std::unique(allDestinationsToA.begin(), allDestinationsToA.end());
    allDestinationsToA.erase(last, allDestinationsToA.end());
    for(int i = 0; i < allDestinationsToA.size(); i++){
        cout << allDestinationsToA[i] << endl;
    }
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

    vector<string> destinations;
    unordered_map<string, vector<string> > mapToUse;
    for (const auto& pair : Map) {
        for(int i = 0; i < pair.second.size(); i++){
            for(int j = 0; j < pair.second[i]->cond.size(); j++){
                destinations.push_back(pair.second[i]->cond[j]->destination);
            }
        }
        ap.insert(make_pair(pair.first, destinations));
    }
    part2();
    cout << total << endl;
    return 0;
}