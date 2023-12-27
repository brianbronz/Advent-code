#include "../Allreference.h"

/**
 * Flip-flop modules (prefix %) are either on or off; 
 * they are initially off. If a flip-flop module receives a high pulse, 
 * it is ignored and nothing happens.
 *  However, if a flip-flop module receives a low pulse, 
 * it flips between on and off. If it was off, 
 * it turns on and sends a high pulse. If it was on, 
 * it turns off and sends a low pulse.
*/
/**
 * Conjunction modules (prefix &) remember the type of the most recent pulse received 
 * from each of their connected input modules; they initially default to remembering a low pulse for each input. 
 * When a pulse is received, the conjunction module first updates its memory for that input. 
 * Then, if it remembers high pulses for all inputs, it sends a low pulse; otherwise, it sends a high pulse.
*/
/**
 * There is a single broadcast module (named broadcaster). When it receives a pulse, it sends the same pulse to all of its destination modules.
*/
//initial pulse low pulse

struct modules{
    string name;
    string type;
    vector<string> dest;
    vector<struct mds*> pulseReceived;
    bool isActive;
    int sendPulse; //0 => low and 1 => high
};
struct mds{
    string name;
    int receivedPulse;
};

vector<struct modules *> md;
void addToDb(string block){
    vector<string> vLines;
    stringstream ss(block);
    string temp;
    while(getline(ss, temp, ' ')){
        vLines.push_back(temp);
    }
    struct modules * newMd = new(modules);
    if(vLines[0][0] == '&' ||  vLines[0][0] == '%'){
        newMd->type = vLines[0][0];
        newMd->name = vLines[0].substr(1);
        if(vLines[0][0] == '&'){
            newMd->isActive = false;
        } else {
            newMd->isActive = true;
        }
    } else {
        newMd->type = "";
        newMd->name = vLines[0];
    }
    for(int i = 2; i < vLines.size(); i++){
        newMd->dest.push_back(vLines[i].substr(0, 2));
    }
    md.push_back(newMd);
}

int readFiles(istream & input, const char * argv){
    int rules = 0;
    string block;
    while(getline(input, block)){
        addToDb(block);
    }

    return 1;
}

void changePulse(int j, int typePulse){
    if(md[j]->type == "%"){
        if(!typePulse){
            if(md[j]->isActive){
                md[j]->isActive = false;
                md[j]->sendPulse = 0;
            } else{
                md[j]->isActive = true;
                md[j]->sendPulse = 1;
            }
        }
    } else{
        struct mds* newMd = new(mds);
        newMd->name = md[j]->name;
        newMd->receivedPulse = typePulse;
        bool found = false;
        for(int i = 0; i < md[j]->pulseReceived.size(); i++){
            if(md[j]->pulseReceived[i]->name == md[j]->name){
                md[j]->pulseReceived[i]->receivedPulse = typePulse;
                found = true;
            }
        }
        if(!found){
            md[j]->pulseReceived.push_back(newMd);
        }
        bool allPulseHigh = 0;
        for(int i = 0; i < md[j]->pulseReceived.size(); i++){
            if(!md[j]->pulseReceived[i]->receivedPulse){
                md[j]->sendPulse = 1;
                allPulseHigh = 1;
            }
        }
        if(allPulseHigh){md[j]->sendPulse = 0;}
    }
}

void findModule(vector<string> tempDest, int typePulse){
    for(int i = 0; i < tempDest.size(); i++){
        for(int j = 0; j < md.size(); j++){
            if(tempDest[i] == md[j]->name){
                changePulse(j, typePulse);
                break;
            }
        }
    }
}

void sendPulse(){
    long long low = 0;
    long long high = 0;
    for(int i = 0; i < 1000; i++){
        string start = "broadcaster";
        int typePulse = 0;
        for(int j = 0; j < md.size(); j++){
            if(start == md[j]->name){
                vector<string> tempDest;
                for(int k = 0; md[j]->dest.size(); k++){
                    cout << md[j]->dest[k] << endl;
                    tempDest.push_back(md[j]->dest[k]);
                }
                findModule(tempDest, typePulse);
                if(md[j]->sendPulse){high++;} else {low++;}
                
            }
        }
    }
    cout << high * low << endl;
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

    sendPulse();
    return 0;
}