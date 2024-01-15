#include "../Allreference.h"

vector<vector<vector<int> > > splitInput(const string& input) {
    vector<vector<vector<int> > > blocks;
    vector<string> lines;
    string line;
    for (char c : input) {
        if (c == '\n') {
            lines.push_back(line);
            line = "";
        } else {
            line += c;
        }
    }
    for (const string& line : lines) {
        vector<vector<int> > block;
        vector<string> parts;
        string part;
        for (char c : line) {
            if (c == '~') {
                parts.push_back(part);
                part = "";
            } else if (c == ',') {
                part += c;
            } else {
                part += c;
            }
        }
        parts.push_back(part);
        for (const string& part : parts) {
            vector<int> coordinates;
            string coordinate;
            for (char c : part) {
                if (c == ',') {
                    coordinates.push_back(stoi(coordinate));
                    coordinate = "";
                } else {
                    coordinate += c;
                }
            }
            coordinates.push_back(stoi(coordinate));
            block.push_back(coordinates);
        }
        blocks.push_back(block);
    }
    return blocks;
}

string getState(const vector<vector<vector<int> > >& blocks) {
    string state = "";
    for (const vector<vector<int> >& block : blocks) {
        state += to_string(block[1][2]) + ",";
    }
    state.pop_back();
    return state;
}

void fall(vector<vector<vector<int> > >& blocks) {
    for (int i = 0; i < blocks.size(); i++) {
        vector<vector<int> >& b = blocks[i];
        if (b[0][2] <= 1) continue;
        int z = b[0][2] - 1;
        bool canFall = true;
        for (int x = b[0][0]; x <= b[1][0]; x++) {
            for (int y = b[0][1]; y <= b[1][1]; y++) {
                for (int j = 0; j < blocks.size(); j++) {
                    if (i != j) {
                        const vector<vector<int> >& o = blocks[j];
                        if (o[0][0] <= x && o[1][0] >= x && o[0][1] <= y && o[1][1] >= y && o[0][2] <= z && o[1][2] >= z) {
                            canFall = false;
                            break;
                        }
                    }
                }
                if (!canFall) break;
            }
            if (!canFall) break;
        }
        if (canFall) {
            b[1][2]--;
            b[0][2]--;
        }
    }
}

void computeSupports(vector<vector<vector<int> > >& blocks) {
    for (int i = 0; i < blocks.size(); i++) {
        vector<vector<int> >& b = blocks[i];
        if (b[0][2] <= 1) continue;
        vector<int> supports;
        int z = b[0][2];
        bool found = false;
        while (z > 1 && !found) {
            z--;
            for (int x = b[0][0]; x <= b[1][0]; x++) {
                for (int y = b[0][1]; y <= b[1][1]; y++) {
                    for (int sId = 0; sId < blocks.size(); sId++) {
                        const vector<vector<int> >& o = blocks[sId];
                        if (i != sId && o[0][0] <= x && o[1][0] >= x && o[0][1] <= y && o[1][1] >= y && o[0][2] <= z && o[1][2] >= z) {
                            if (find(supports.begin(), supports.end(), sId) == supports.end()) {
                                supports.push_back(sId);
                            }
                            found = true;
                        }
                    }
                }
            }
        }
        b[2] = supports;
        for (int supId : supports) {
            if (find(blocks[supId][3].begin(), blocks[supId][3].end(), i) == blocks[supId][3].end()) {
                blocks[supId][3].push_back(i);
            }
        }
    }
}

string fallFull(vector<vector<vector<int> > >& blocks) {
    string state = "";
    string currentState = getState(blocks);
    while (state != currentState) {
        state = currentState;
        fall(blocks);
        currentState = getState(blocks);
    }
    return state;
}
bool areAllBlocksValid(const vector<int>& blocks, const vector<int>& brokenSupports) {
    for (int k : blocks) {
        if (find(brokenSupports.begin(), brokenSupports.end(), k) == brokenSupports.end()) {
            return false;
        }
    }
    return true;
}

void sumSupporteds(vector<vector<vector<int> > >& blocks, int i, vector<int>& brokenSupports) {
    for (int j : blocks[i][3]) {
        if (areAllBlocksValid(blocks[j][2], brokenSupports)) {
            brokenSupports.push_back(j);
            sumSupporteds(blocks, j, brokenSupports);
        }
    }
}
int countValidElements(const vector<vector<vector<int> > >& blocks) {
    int count = 0;

    for (const auto& o : blocks) {
        if (o[3].empty()) {
            count++;
        } else {
            bool isValid = true;
            for (int sId : o[3]) {
                if (blocks[sId][2].size() != 1) {
                    isValid = false;
                    break;
                }
            }
            if (isValid) {
                count++;
            }
        }
    }

    return count;
}

int accumulateBlocks(vector<vector<vector<int> > >& blocks) {
    int result = 0;
    for (const auto& o : blocks) {
        vector<int> brokenSupports;
        brokenSupports.push_back(&o - &blocks[0]);
        sumSupporteds(blocks, &o - &blocks[0], brokenSupports);
        result += brokenSupports.size() - 1;

    }
    return result;
}

int main() {
    string input;
    getline(cin, input);
    vector<vector<vector<int> > > blocks = splitInput(input);
    fallFull(blocks);
    computeSupports(blocks);
    int p1 = countValidElements(blocks);
    cout << "p1 " << p1 << endl;
    int p2 = accumulateBlocks(blocks);
    cout << "p2 " << p2 << endl;
    return 0;
}