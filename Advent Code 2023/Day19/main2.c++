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
            //cout << rls[i]->cond[j]->destination << endl;
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
void findPath(const string& start, const string& goal, vector<string>& path, unordered_set<string>& visited) {
    path.push_back(start);
    visited.insert(start);

    if (start == goal) {
        string resPath = "";
        for (const auto& node : path) {
            resPath += node + " ";
        }
        resPath.pop_back();
        allDestinationsToA.push_back(resPath);
    } else {
        if (Map.find(start) != Map.end()) {
            for (const auto& rule : Map[start]) {
                for (const auto& condition : rule->cond) {
                    string nextNode = condition->destination;
                    if (visited.find(nextNode) == visited.end()) {
                        findPath(nextNode, goal, path, visited);
                    }
                }
            }
        }
    }

    visited.erase(start);
    path.pop_back();
}

void definedInterval(){
    long long total = 0;
    for(int i = 0; i < allDestinationsToA.size(); i++){
        int minX = 1; 
        int minM = 1;
        int minS = 1;
        int minA = 1;
        int maxX = 4000; 
        int maxM = 4000;
        int maxS = 4000; 
        int maxA = 4000;
        vector<string> temp;
        stringstream iss(allDestinationsToA[i]);
        string word;
        while(iss >> word){
            temp.push_back(word);
        }
        for(int j = 0; j <temp.size(); j++){
            for (const auto& pair : Map) {
                if(temp[j] == pair.first){
                    string next = temp[j + 1];
                    int index = 0;
                    for(int k = 0; k < pair.second.size(); k++){
                        for(int l = 0; l < pair.second[k]->cond.size(); l++){
                            if(pair.second[k]->cond[l]->destination == next){
                                index = l;
                                break;
                            }
                        }
                        //casi rifiutati
                        for(int l = 0; l < index; l++){
                            string op = pair.second[k]->cond[l]->operation;
                            string v = pair.second[k]->cond[l]->variable;
                            int value = pair.second[k]->cond[l]->secondValue;
                            if(v == "a"){
                                (op == "<")? minA = value: maxA = value;
                            } else if(v == "x"){
                                (op == "<")? minX = value: maxX = value;
                            } else if(v == "m"){
                                (op == "<")? minM = value: maxM = value;
                            } else if(v == "s"){
                                (op == "<")? minS = value: maxS = value;
                            } else {break;}
                        }

                        //caso che deve accadere
                        string op = pair.second[k]->cond[index]->operation;
                        string v = pair.second[k]->cond[index]->variable;
                        int value = pair.second[k]->cond[index]->secondValue;
                        if(op == ""){break;}
                        if(v == "a"){
                            (op == ">")? minA = value: maxA = value;
                        } else if(v == "x"){
                            (op == ">")? minX = value: maxX = value;
                        } else if(v == "m"){
                            (op == ">")? minM = value: maxM = value;
                        } else if(v == "s"){
                            (op == ">")? minS = value: maxS = value;
                        } else {break;}
                    }
                    break;
                }
            }
        }
        cout << endl;
        cout << " Max X: " <<maxX << " Min X: " << minX;
        cout << endl;
        cout << " Max M: " << maxM << " Min M: " << minM << endl;
        cout << " Max S: " << maxS << " Min S: " << minS << endl;
        cout << " Max A: " << maxA << " Min A: " << minA << endl;
        total += (maxX - minX) * (maxM - minM) * (maxS - minS) * (maxA - minA);
    }
    cout <<total;
}
//167409079868000
void part2(){
    vector<string> path;
    unordered_set<string> visited;
    string start = "in";
    string goal = "A";

    findPath(start, goal, path, visited);
    definedInterval();
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
        cout << pair.first << endl;
        for(int i = 0; i < pair.second.size(); i++){
            for(int j = 0; j < pair.second[i]->cond.size(); j++){
                cout << " " <<pair.second[i]->cond[j]->destination << endl;
                destinations.push_back(pair.second[i]->cond[j]->destination);
            }
        }
        ap.insert(make_pair(pair.first, destinations));
        cout << endl;
    }

    part2();
    cout << total << endl;
    return 0;
}