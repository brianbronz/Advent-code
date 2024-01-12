#include <iostream>
#include <deque>
#include <unordered_map>
#include <cmath>
#include <set>
#include <numeric>

#include "../Allreference.h"
template<typename T>
T lcm(T a, T b) {
    return lcm(a, b);
}
class Module {
public:
    string id;
    vector<string> connections;
    bool enabled;
    unordered_map<string, bool> inputs;

    Module(string id, vector<string> connections, bool enabled) {
        this->id = id;
        this->connections = connections;
        this->enabled = enabled;
    }

    virtual bool updateState(bool input, string inputId) = 0;
};

class BroadCaster : public Module {
public:
    BroadCaster(vector<string> connections) : Module("broadcaster", connections, true) {}

    bool updateState(bool input, string inputId) override {
        return input;
    }
};

class FlipFlop : public Module {
public:
    FlipFlop(string id, vector<string> connections) : Module(id, connections, false) {}

    bool updateState(bool input, string inputId) override {
        if (input) {
            return NULL;
        }
        this->enabled = !this->enabled;
        return this->enabled;
    }
};
struct ComparePredicate {
    bool operator()(const pair<string, bool>& p) const {
        return p.second == true;
    }
};
class Conjunction : public Module {
public:
    Conjunction(string id, vector<string> connections) : Module(id, connections, true) {}
    bool compareV(const pair<string, bool> p){
        return p.second == true;
    }
    bool updateState(bool input, string inputId) override {
        this->inputs[inputId] = input;
        return !(all_of(this->inputs.begin(), this->inputs.end(), ComparePredicate()));
    }
};

pair<int, int> solve(unordered_map<string, Module*>& modules) {
    int high = 0;
    int low = 0;
    int part1 = 0;
    unordered_map<string, int> moduleRx;
    for (int i = 0; i < 5000; i++) {
        if (i == 1000) {part1 = high * low;}
        low += 1;
        Module* currentModule = modules["broadcaster"];
        bool signal = currentModule->updateState(0, "");
        deque<pair<Module*, bool> > q;
        q.push_back(make_pair(currentModule, signal));
        while (!q.empty()) {
            currentModule = q.front().first;
            signal = q.front().second;
            q.pop_front();
            for (const auto& con : currentModule->connections) {
                if (signal) {
                    high += 1;
                }
                else {
                    low += 1;
                }
                if (modules.find(con) != modules.end()) {
                    if (signal && modules[con]->id == "zp") {
                        if (moduleRx.find(currentModule->id) == moduleRx.end()) {
                            moduleRx[currentModule->id] = i + 1;
                        }
                        auto set1 = set<pair<string, int> >(moduleRx.begin(), moduleRx.end());
                        auto set2 = set<pair<string, int> >(modules[con]->inputs.begin(), modules[con]->inputs.end());

                        if (set1 == set2) {
                            return make_pair(part1, lcm(moduleRx.begin()->second, prev(moduleRx.end())->second));
                            //return make_pair(part1, lcm(moduleRx.begin()->second, moduleRx.rbegin()->second));
                        }
                    }
                    bool newSignal = modules[con]->updateState(signal, currentModule->id);
                    if (newSignal != NULL) {
                        q.push_back(make_pair(modules[con], newSignal));
                    }
                }
            }
        }
    }
    return make_pair(high * low, 1);
}

void parseInput(string inputFile, unordered_map<string, Module*>& modules, void (*callback)(unordered_map<string, Module*>&, string, string, vector<string>&)) {
    ifstream file("input.txt");
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string module;
        string connections;
        size_t delimiterPos = line.find(" -> ");
        if (delimiterPos != string::npos) {
            module = line.substr(0, delimiterPos);
            connections = line.substr(delimiterPos + 4);
        }

        vector<string> connectionsVec;
        size_t start = 0;
        size_t end = connections.find(", ");

        while (end != string::npos) {
            string connection = connections.substr(start, end - start);
            connectionsVec.push_back(connection);
            start = end + 2; // 2 è la lunghezza di ", "
            end = connections.find(", ", start);
        }

        string lastConnection = connections.substr(start);
        connectionsVec.push_back(lastConnection);

        string id = module.substr(0, module.find_first_of("&%"));
        callback(modules, module, id, connectionsVec);
    }
    file.close();
}

void initModules(unordered_map<string, Module*>& modules, string module, string id, vector<string>& connections) {
    if (module.find("%") != string::npos) {
        modules[id] = new FlipFlop(id, connections);
    }
    else if (module.find("&") != string::npos) {
        modules[id] = new Conjunction(id, connections);
    }
    else {
        modules[id] = new BroadCaster(connections);
    }
}

void initInputs(unordered_map<string, Module*>& modules, string module, string id, vector<string>& connections) {
    for (const auto& con : connections) {
        if (modules.find(con) != modules.end()) {
            modules[con]->inputs[id] = false;
        }
    }
}

pair<int, int> day20() {
    string inputFile = "2023/inputs/day20.txt";
    unordered_map<string, Module*> modules;
    parseInput(inputFile, modules, initModules);
    parseInput(inputFile, modules, initInputs);
    return solve(modules);
}

int main() {
    pair<int, int> result = day20();
    cout << result.first << endl;
    cout << result.second << endl;
    return 0;
}


