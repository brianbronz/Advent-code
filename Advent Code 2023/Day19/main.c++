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

struct Parts{
    int x;
    int m;
    int a;
    int s;
};

vector<struct Rules*> rls;
long long total = 0;

void isValid(struct Parts * part){
    string initial = "in";
    for (int i = 0; i < rls.size(); i++){
        if(initial.compare(rls[i]->name) == 0){
            /*
            The first rule that matches the part being 
            considered is applied immediately, 
            and the part moves on to the destination described by the rule.
            */
            bool isMatches = false;
            string dest = "";
            for(int j = 0; j < rls[i]->cond.size(); j++){
                string tempVariable = rls[i]->cond[j]->variable;
                dest = rls[i]->cond[j]->destination;
                string op = rls[i]->cond[j]->operation;
                int valueToCmp = rls[i]->cond[j]->secondValue;
                if(tempVariable == "a"){
                    (op == "<")? isMatches = (part->a < valueToCmp): isMatches = (part->a > valueToCmp);
                } else if(tempVariable == "x"){
                    (op == "<")? isMatches = (part->x < valueToCmp): isMatches = (part->x > valueToCmp);
                } else if(tempVariable == "m"){
                    (op == "<")? isMatches = (part->m < valueToCmp): isMatches = (part->m > valueToCmp);
                } else if(tempVariable == "s"){
                    (op == "<")? isMatches = (part->s < valueToCmp): isMatches = (part->s > valueToCmp);
                } else {break;}
                if(isMatches){
                    initial = dest;
                    break;
                }
            }
            if(!isMatches){
                initial = rls[i]->cond[rls[i]->cond.size() - 1]->destination;
            }
            i = -1;
        }
        if(initial == "A" || initial =="R"){break;}
    }
    if (initial == "A"){
        total += part->a + part->m + part->s + part->x;
    }
}

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
}

void addParts(string block){
    int openBrackets = block.find("{");
    int closedbrackets = block.find("}");
    string allConditions = block.substr(openBrackets + 1, closedbrackets - 1 - openBrackets);
    vector<string> vLines;
    stringstream ss(allConditions);
    string temp;
    while(getline(ss, temp, ',')){
        vLines.push_back(temp);
    }
    struct Parts* newParts = new(Parts);
    for(int i = 0; i < vLines.size(); i++){
        int value = stoi(vLines[i].substr(2));
        switch(i){
            case 0: newParts->x = value; break;
            case 1: newParts->m = value; break;
            case 2: newParts->a = value; break;
            case 3: newParts->s = value; break;
            default:
                break;
        };
    }
    //{x=787,m=2655,a=1222,s=2876}
    //Check if it is accepted the part
    //part 1
    isValid(newParts);
    //part 2
}

int readFiles(istream & input, const char * argv){
    int rules = 0;
    string block;
    while(getline(input, block)){

        if(block.empty()){
            rules = 1;
            continue;
        }

        if(!rules){
            addRules(block);
        } else{
            addParts(block);
        }
    }

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
    cout << total << endl;
    return 0;
}