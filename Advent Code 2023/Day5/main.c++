#include "../Allreference.h"

#define int_64 
struct seedsMap{
    long long Source;
    long long Target;
    long long size;
};

vector<long long> needSeeds;

vector<struct seedsMap*> STSM;
vector<struct seedsMap*> STFM;
vector<struct seedsMap*> FTWM;
vector<struct seedsMap*> WTLM;
vector<struct seedsMap*> LTTM;
vector<struct seedsMap*> TTTM;
vector<struct seedsMap*> HTLM;

void addToNeedsVect(string block){
    long long posDoublePoint = block.find(":") + 2;
     //take number of winning
    string NumSeeds = block.substr(posDoublePoint);
    string tempNum = "";
    cout << NumSeeds.size() << endl;
    for (long long i = 0; i < NumSeeds.size(); i++){
        if (isspace(NumSeeds[i])){
            if (tempNum != ""){
                needSeeds.push_back(stof(tempNum));
            }
            tempNum = "";
        } else {
            tempNum += NumSeeds[i];
        }
        cout << i << endl;
    }
    if (tempNum != ""){
        needSeeds.push_back(stof(tempNum));
    }
}

long long getFirstNumber(string str){
    istringstream iss(str);
    long long firstNumber;
    iss >> firstNumber;
    return firstNumber;
}

bool compareFirstNumber(string a, string b){
    return getFirstNumber(a) < getFirstNumber(b);
}

void parseAndAddValues(vector<string> tempSeeds,vector<long long>& src, vector<long long>& dest, vector<long long>& range ){
    vector<string> Threevalue;
    for (long long i = 1; i < tempSeeds.size(); i++){
        string tempNum = "";
        for (long long j = 0; j <tempSeeds[i].size(); j++){
            if (isspace(tempSeeds[i][j])){
                if (tempNum != "")
                    Threevalue.push_back(tempNum);
                    tempNum = "";
            } else {
                tempNum += tempSeeds[i][j];
            }
        }
        if (tempNum != ""){
            Threevalue.push_back(tempNum);
        }
        src.push_back(stof(Threevalue[0]));
        dest.push_back(stof(Threevalue[1]));
        range.push_back(stof(Threevalue[2]));
        cout << src[i] << " " << dest[i] << " " << range[i] << endl;
        Threevalue.clear();
    }
}

long long getMax(vector<long long> src, vector<long long> dest, vector<long long> range){
    long long rValue = 0;
    long long maxValue = 0;
    long long numSeed = 0;
    for (long long i = 0; i < src.size(); i++){
        maxValue = max(src[i], dest[i]);
        rValue = range[i];
        if (numSeed < maxValue + rValue){
            numSeed = maxValue + rValue;
        }
    }
    return numSeed;
}

void addToVect(string seed, vector<string> tempSeeds){
    for(long long i = 1; i < tempSeeds.size(); i++){
        string temp = "";
        vector<string> rs;
        for(long long j = 0; j < tempSeeds[i].size(); j++){
            if(tempSeeds[i][j] == ' '){
                rs.push_back(temp);
                temp = "";
            } else {
                temp += tempSeeds[i][j];
            }
        }
        rs.push_back(temp);
        struct seedsMap* newMap = new(seedsMap);
        newMap->size = stof(rs[2]);
        newMap->Target = stof(rs[1]);
        newMap->Source = stof(rs[0]);
        //cout << newMap->Source << " "<< newMap->Target << " " << newMap->size << endl;
        if(seed == "seed-to-soil"){
            STSM.push_back(newMap);
        } else if(seed == "soil-to-fertilizer"){
            STFM.push_back(newMap);
        } else if(seed == "fertilizer-to-water"){
            FTWM.push_back(newMap);
        } else if(seed == "water-to-light"){
            WTLM.push_back(newMap);
        } else if(seed == "light-to-temperature"){
            LTTM.push_back(newMap);
        } else if(seed == "temperature-to-humidity"){
            TTTM.push_back(newMap);
        } else if(seed == "humidity-to-location"){
            HTLM.push_back(newMap);
        }
        rs.clear();
    }
}

void addToDatabase(vector<string> tempSeeds){
        if(tempSeeds[0].find("seed-to-soil") != string::npos){
            addToVect("seed-to-soil", tempSeeds);
        } else if(tempSeeds[0].find("soil-to-fertilizer") != string::npos){
            addToVect("soil-to-fertilizer", tempSeeds);
        } else if(tempSeeds[0].find("fertilizer-to-water") != string::npos){
            addToVect("fertilizer-to-water", tempSeeds);
        } else if(tempSeeds[0].find("water-to-light") != string::npos){
            addToVect("water-to-light", tempSeeds);
        } else if(tempSeeds[0].find("light-to-temperature") != string::npos){
            addToVect("light-to-temperature", tempSeeds);
        } else if(tempSeeds[0].find("temperature-to-humidity") != string::npos){
            addToVect("temperature-to-humidity", tempSeeds);
        } else if(tempSeeds[0].find("humidity-to-location") != string::npos){
            addToVect("humidity-to-location", tempSeeds);
        }
    }


long long readFiles(istream & input, const char * argv){
     string block;
     vector<string> tempSeeds;

    while(getline(input, block)){
        //cout << block << endl;
        if (block.find("seeds:") != string::npos){
            addToNeedsVect(block);
        } else if(block.size() != 0){
            tempSeeds.push_back(block);
        }
        if (block == "" && tempSeeds.size() != 0){
            addToDatabase(tempSeeds);
            tempSeeds.clear();
        }
    }
}

bool InRange(long long Start, long long size, long long Num)
	{
	return (Num >= Start && Num <= (Start + size -1));
	}

void getLocation(){
    
    //cout << minValue << endl;
    long long Lowest = INT_MAX;
    long long lls = 0;
    long long insanity = 0;
    for (long long i = 0; i < needSeeds.size(); i += 1){
        long long temp = 0;
        bool found = false;
        cout << needSeeds[i] << endl;
        //To soil
        for(long long j = 0; j < STSM.size(); j++){
            if(needSeeds[i] >= STSM[j]->Source && needSeeds[i] < STSM[j]->Source + STSM[j]->size && !found){
                temp = needSeeds[i] + STSM[j]->Target - STSM[j]->Source;
                found = true;
            }
        }
        if (!found){
            temp = needSeeds[i];
        }
        found = false;
        cout << temp << endl;
        long long temp2 = temp;
        //to fertilizer
        for(long long j = 0; j < STFM.size(); j++){
            if(temp2 >= STFM[j]->Source && temp2 < STFM[j]->Source + STFM[j]->size && !found){
                temp2 = temp + STFM[j]->Target - STFM[j]->Source;
                found = true;
            }
        }
        if (found){temp = temp2;}
        found = false;
        //to water
        cout << temp << endl;
        for(long long j = 0; j < FTWM.size(); j++){
            if(temp2 >= FTWM[j]->Source && temp2 < FTWM[j]->Source + FTWM[j]->size && !found){
                temp2 = temp - FTWM[j]->Source + FTWM[j]->Target;
                found = true;
            }
        }
        if (found){temp = temp2;}
        found = false;
        cout << temp << endl;
        // to light
        for(long long j = 0; j < WTLM.size(); j++){
            if(temp2 >= WTLM[j]->Source && temp2 < WTLM[j]->Source + WTLM[j]->size && !found){
                temp2 = temp - WTLM[j]->Source + WTLM[j]->Target;
                found = true;
            }
        }
        if (found){temp = temp2;}
        found = false;
        cout << temp << endl;
        //to temperature
        for(long long j = 0; j < LTTM.size(); j++){
            if(temp2 >= LTTM[j]->Source && temp2 < LTTM[j]->Source + LTTM[j]->size && !found){
                long long diff = abs(LTTM[j]->Target - temp2);
                temp2 = temp - LTTM[j]->Source + LTTM[j]->Target;
                found = true;
            }
        }
        if (found){temp = temp2;}
        found = false;
        //to humidity
        cout << temp2 << endl;
        for(long long j = 0; j < TTTM.size(); j++){
            if(temp2 >= TTTM[j]->Source && temp2 < TTTM[j]->Source + TTTM[j]->size && !found){
                temp2 = temp + TTTM[j]->Target - TTTM[j]->Source;
                found = true;
            }
        }
        if (found){temp = temp2;}
        found = false;
        cout << temp2 << endl;
        //to location
        for(long long j = 0; j < HTLM.size(); j++){
            if(temp2 >= HTLM[j]->Source && temp2 < HTLM[j]->Source + HTLM[j]->size && !found){
                temp2 = temp - HTLM[j]->Source + HTLM[j]->Target;
                found = true;
            }
        }
        if (found){temp = temp2;}
        cout << temp << endl;
        cout << endl;
        if (temp < Lowest){
            Lowest = temp;
        }
    }
    //836040384
    //220787924 10834440
    cout << Lowest << endl;
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

    getLocation();
    return 0;
}