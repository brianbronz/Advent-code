#include "../Allreference.h"

struct position{
    int x1, x2;
    int y1, y2;
    int z1, z2;
};

vector<struct position *> ps;
string replaceTilde(string block){
    for(int i = 0; i < block.size(); i++){
        if(block[i] == '~'){
            block[i] = ' ';
        }
    }
    return block;
}

string replaceComa(string block){
    for(int i = 0; i < block.size(); i++){
        if(block[i] == ','){
            block[i] = ' ';
        }
    }
    return block;
}

bool compareValue(struct position * &a, struct position * &b){
   return a->z1 < b->z1;
}

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        block = replaceTilde(block);
        block = replaceComa(block);
        cout << block << endl;
        stringstream ss(block);
        vector<string> coords;
        string temp;
        while(ss >> temp){
            coords.push_back(temp);
        }
        struct position * newPs = new(position);
        newPs->x1 = stoi(coords[0]);
        newPs->y1 = stoi(coords[1]);
        newPs->z1 = stoi(coords[2]);
        newPs->x2 = stoi(coords[3]);
        newPs->y2 = stoi(coords[4]);
        newPs->z2 = stoi(coords[5]);
        ps.push_back(newPs);
    } 
    sort(ps.begin(), ps.end(), compareValue);
    return -1;
}

void movement(){
    for(int i = 0; i < ps.size(); i++){
        int maxZ = 1;
        for(int j = 0; j < i; j++){
            int maxX1 = max(ps[i]->x1, ps[j]->x1);
            int minX2 = min(ps[i]->x2, ps[j]->x2);
            int maxY1 = max(ps[i]->y1, ps[j]->y1);
            int minY2 = min(ps[i]->y2, ps[j]->y2);
            if(maxX1 <= minX2 && maxY1 <= minY2){
                maxZ = max(maxZ, ps[j]->z2 + 1);
            }
        }
        ps[i]->z2 -= ps[i]->z1 - maxZ;
        ps[i]->z1 = maxZ;
    }
    sort(ps.begin(), ps.end(), compareValue);
}
void part1(){
    int res = 0;
    vector<set<int> > supports;
    vector<int> supported;
    for(int i = 0; i < ps.size(); i++){
        supports.push_back(set<int>());
        supported.push_back(0);
    }

    for(int i = 0; i < ps.size(); i++){
        for(int j = 0; j < i; j++){
            int maxX1 = max(ps[i]->x1, ps[j]->x1);
            int minX2 = min(ps[i]->x2, ps[j]->x2);
            int maxY1 = max(ps[i]->y1, ps[j]->y1);
            int minY2 = min(ps[i]->y2, ps[j]->y2);
            if(maxX1 <= minX2 && maxY1 <= minY2){
                supports[j].insert(i);
                supported[i]++;
            }
        }
    }

    for (int i = 0; i < ps.size(); i++){
        int ok = 1;
        for (auto x : supports[i]){
            if (supported[x] < 2){
                ok = 0;
                break;
            }
        }
        res += ok;
    }

    cout << res << endl;
}

void part2(){
    int sol = 0;
    vector<set<int> > supports;
    vector<int> supported;
    for(int i = 0; i < ps.size(); i++){
        supports.push_back(set<int>());
        supported.push_back(0);
    }
    for (int i = 0; i < ps.size(); i++){
        for (int j = 0; j < i; j++){
            int maxX1 = max(ps[i]->x1, ps[j]->x1);
            int minX2 = min(ps[i]->x2, ps[j]->x2);
            int maxY1 = max(ps[i]->y1, ps[j]->y1);
            int minY2 = min(ps[i]->y2, ps[j]->y2);
            if(maxX1 <= minX2 && maxY1 <= minY2){
                supports[j].insert(i);
                supported[i]++;
            }
        }
    }

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

    movement();
    part1();
    return 0;
}