#include "../Allreference.h"
int mod(int n, int m) {
  return ((n % m) + m) % m;
}

int main() {
  ifstream inputFile("input.txt");
  if (!inputFile) {
    throw runtime_error("Failed to open input file");
  }

  vector<string> rawMap;
  string line;
  while (getline(inputFile, line)) {
    rawMap.push_back(line);
  }

  map<string, int> map1;
  string start;
  int width = rawMap[0].length();
  int height = rawMap.size();
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      char c = rawMap[y][x];
      if (c == '.' || c == 'S') {
        map1[to_string(x) + ", " + to_string(y)] = 0;
        if (c == 'S') {
          start = to_string(x) + ", " + to_string(y);
        }
      }
    }
  }

  map<string, int> toVisit;
  toVisit[start] = 0;
  int needed = 26501365;
  int afterNeeded = needed + 1;
  int twoWidth = width * 2;
  int modulo = afterNeeded % twoWidth;
  int good = 0;
  int onestep = 0;
  int validationRounds = 2;
  for (const auto& value : toVisit) {
    string point = value.first;
    int step = value.second;
    if (onestep < step && step > (width * 2)) {
      vector<int> uv;
      for (const auto& entry : map1) {
        if (entry.second != 0) {
          uv.push_back(entry.second);
        }
      }
      sort(uv.begin(), uv.end());
      map<int, int> groups;
      for (const auto& entry : map1) {
        if (entry.second != 0) {
          if (groups.find(entry.second) == groups.end()) {
            groups[entry.second] = 1;
          } else {
            groups[entry.second]++;
          }
        }
      }
      if (uv.size() == 2) {
        int seed = floor((2 * ((step) / twoWidth)));
        int conjecture = (seed * seed) * groups[seed * seed] + (seed * seed - seed) * groups[seed * seed - seed];
        if (conjecture != good) {
          throw runtime_error("bad conjecture");
        }
        if (seed > validationRounds && (step % twoWidth == modulo)) {
          int neededSeed = (modulo == width) ? (floor((2 * (afterNeeded / twoWidth))) - 1) : floor((2 * (afterNeeded / twoWidth)));
          vector<int> groupKeys;
          for (const auto& entry : groups) {
            groupKeys.push_back(entry.first);
          }
          cout << "SOLUTION" << endl;
          cout << groups[groupKeys[0]] * (neededSeed * neededSeed) + groups[groupKeys[1]] * (neededSeed * neededSeed - neededSeed) << endl;
          return 0;
        }
      } else if (uv.size() == 3) {
        int seed = (step % twoWidth == width) ? (floor((2 * ((step) / twoWidth))) - 1) : floor((2 * ((step) / twoWidth)));
        int conjecture = (seed * seed) * groups[seed * seed] + (seed * seed + seed) * groups[seed * seed + seed] + (seed * seed + seed + seed + 1) * groups[seed * seed + seed + seed + 1];
        if (conjecture != good) {
          throw runtime_error("bad conjecture");
        }
        if (seed > validationRounds && (step % twoWidth == modulo)) {
          int neededSeed = (modulo == width) ? (floor((2 * (afterNeeded / twoWidth))) - 1) : floor((2 * (afterNeeded / twoWidth)));
          vector<int> groupKeys;
          for (const auto& entry : groups) {
            groupKeys.push_back(entry.first);
          }
          cout << "SOLUTION" << endl;
          cout << groups[groupKeys[0]] * (neededSeed * neededSeed) + groups[groupKeys[1]] * (neededSeed * neededSeed + neededSeed) + groups[groupKeys[2]] * (neededSeed * neededSeed + neededSeed + neededSeed + 1) << endl;
          return 0;
        }
      } else {
        throw runtime_error("cant solve");
      }
      onestep = step;
    }
    string::size_type pos = point.find(", ");
    int curX = stoi(point.substr(0, pos));
    int curY = stoi(point.substr(pos + 2));
    if (step % 2 == 1) {
      good++;
      int realX = mod(curX, width);
      int realY = mod(curY, height);
      map1[to_string(realX) + ", " + to_string(realY)]++;
    }
    vector<pair<int, int> > direction;
    direction.push_back(make_pair(1, 0));
    direction.push_back(make_pair(-1, 0));
    direction.push_back(make_pair(0, 1));
    direction.push_back(make_pair(0, -1));
    for (const auto& change : direction) {
      int xChange = change.first;
      int yChange = change.second;
      int nextX = curX + xChange;
      int nextY = curY + yChange;
      string nextPoint = to_string(nextX) + ", " + to_string(nextY);
      int realX = mod(nextX, width);
      int realY = mod(nextY, height);
      if (map1.find(to_string(realX) + ", " + to_string(realY)) != map1.end() && toVisit.find(nextPoint) == toVisit.end()) {
        toVisit[nextPoint] = step + 1;
      }
    }
  }
  cout << good << endl;

  return 0;
}