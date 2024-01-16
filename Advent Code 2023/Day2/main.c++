#include "../Allreference.h"

struct database{
    vector<string> ID;
    vector<struct cubes*> cb;
};

struct cubes{
    int red;
    int blue;
    int green;
};

struct database * newDb = new(database);

int readFiles(istream & input, const char * argv){
    string block;
    while(getline(input, block)){
        //Take Id
        string Id = "";
        int posPunct = block.find(":");
        int firstSpace = block.find(" ");
        Id = block.substr(firstSpace + 1, posPunct - firstSpace - 1);
        newDb->ID.push_back(Id);
        //Take the bag
        // 4 red, 3 blue; 6 blue, 16 green; 9 blue, 13 green, 1 red; 10 green, 4 red, 6 blue
        string temp = block.substr(posPunct + 2);
        int index = -1;
        int maxRed = 0;
        int maxBlue = 0;
        int maxGreen = 0;
        for (int i = posPunct + 2; i < block.length(); i++){
            int pointComa = block.find(";", i);
            int coma = block.find(",", i);
            if (coma == -1){coma = block.length();}
            if (isdigit(block[i])){
                //info about single color
                int minValue = min(pointComa, coma);
                if (minValue == -1){minValue = max(pointComa, coma);}
                string tempBeforeComa = block.substr(i, minValue - i);//4 red
                int space = tempBeforeComa.find(" ", 0);
                string tempColor = tempBeforeComa.substr(space + 1, minValue - i);//red
                int value = stoi(block.substr(i, space));//4
                index = minValue;
                //Insert data
                if (tempColor.find("red") != string::npos && value > maxRed){
                    maxRed = value;
                } else if(tempColor.find("blue") != string::npos && value > maxBlue){
                    maxBlue = value;
                } else if(tempColor.find("green") != string::npos && value > maxGreen){
                    maxGreen = value;
                }
                i = index + 1;
            } 

            if (pointComa != string::npos && index > pointComa){
                i = pointComa;
            }
        }
        struct cubes * newCubes = new(cubes);
        newCubes->blue = maxBlue;
        newCubes->green = maxGreen;
        newCubes->red = maxRed;
        newDb->cb.push_back(newCubes);
    }
    return 1;
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

    //max value (quelli richiesti)
    //only 12 red cubes, 13 green cubes, and 14 blue cubes
    int sumId = 0;
    for (int i = 0; i < newDb->cb.size(); i++){
        /*if (newDb->cb[i]->blue <= 14 && newDb->cb[i]->red <= 12  && newDb->cb[i]->green <= 13){
            sumId += stoi(newDb->ID[i]);
        }*/
        sumId += newDb->cb[i]->blue * newDb->cb[i]->red * newDb->cb[i]->green;
    }
    cout << sumId << endl;
    return 1;
}