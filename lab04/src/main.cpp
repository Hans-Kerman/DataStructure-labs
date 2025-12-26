#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <functional>

using namespace std;

struct state {
  bool Farmer;  // 8
  bool Wolf;    // 4
  bool Goat;    // 2
  bool Cabbage; // 1
};

// 比较函数，用于set
struct stateCompare {
  bool operator()(const state& a, const state& b) const {
    if (a.Farmer != b.Farmer) return a.Farmer < b.Farmer;
    if (a.Wolf != b.Wolf) return a.Wolf < b.Wolf;
    if (a.Goat != b.Goat) return a.Goat < b.Goat;
    return a.Cabbage < b.Cabbage;
  }
};

bool isvalid(state s);
int state2id(state s);
void makestate(state s);
void findAllPaths(state from, state to);
void printState(state s);
void printAllPaths();
void dfs(state current, state goal, vector<state>& path, vector<vector<state>>& allPaths);

set<state, stateCompare> visited;
vector<state> states[16];
vector<vector<state>> allPaths; // 存储所有路径

int main() {
  state initial = {0, 0, 0, 0};
  state goal = {1, 1, 1, 1};
  
  // 生成所有可能的状态
  makestate(initial);
  
  // 寻找所有路径
  findAllPaths(initial, goal);
  
  // 输出结果
  printAllPaths();
  
  return 0;
}

bool isvalid(state s) {
  if (s.Wolf == s.Goat && s.Farmer != s.Wolf)
    return false;
  if (s.Goat == s.Cabbage && s.Farmer != s.Goat)
    return false;
  return true;
}

int state2id(state s) {
  int ans = 0;
  if (s.Farmer)
    ans += 8;
  if (s.Wolf)
    ans += 4;
  if (s.Goat)
    ans += 2;
  if (s.Cabbage)
    ans += 1;
  return ans;
}

void makestate(state s) {
  if (visited.find(s) != visited.end())
    return;
  visited.insert(s);

  vector<state> nextStates;

  // 农夫单独过河
  {
    state next = s;
    next.Farmer = !next.Farmer;
    if (isvalid(next)) {
      nextStates.push_back(next);
    }
  }

  // 农夫带狼过河
  if (s.Wolf == s.Farmer) {
    state next = s;
    next.Farmer = !next.Farmer;
    next.Wolf   = !next.Wolf;
    if (isvalid(next)) {
      nextStates.push_back(next);
    }
  }

  // 农夫带山羊过河
  if (s.Goat == s.Farmer) {
    state next = s;
    next.Farmer = !next.Farmer;
    next.Goat   = !next.Goat;
    if (isvalid(next)) {
      nextStates.push_back(next);
    }
  }

  // 农夫带卷心菜过河
  if (s.Cabbage == s.Farmer) {
    state next = s;
    next.Farmer  = !next.Farmer;
    next.Cabbage = !next.Cabbage;
    if (isvalid(next)) {
      nextStates.push_back(next);
    }
  }

  states[state2id(s)] = nextStates;

  for (const auto& nextState : nextStates) {
    if (visited.find(nextState) == visited.end()) {
      makestate(nextState);
    }
  }
}


void dfs(state current, state goal, vector<state>& path, vector<vector<state>>& allPaths, vector<bool>& inPath) {
  path.push_back(current);
  inPath[state2id(current)] = true;
  
  if (state2id(current) == state2id(goal)) {
    allPaths.push_back(path);
  } else {
    int currentId = state2id(current);
    for (const auto& nextState : states[currentId]) {
      int nextId = state2id(nextState);
      if (!inPath[nextId]) {
        dfs(nextState, goal, path, allPaths, inPath);
      }
    }
  }
  
  path.pop_back();
  inPath[state2id(current)] = false;
}

void findAllPaths(state from, state to) {
  vector<state> path;
  vector<bool> inPath(16, false); // 标记状态是否在当前路径中
  
  dfs(from, to, path, allPaths, inPath);
}

void printState(state s) {
  cout << "农夫: " << (s.Farmer ? "右岸" : "左岸") << ", ";
  cout << "狼: " << (s.Wolf ? "右岸" : "左岸") << ", ";
  cout << "山羊: " << (s.Goat ? "右岸" : "左岸") << ", ";
  cout << "卷心菜: " << (s.Cabbage ? "右岸" : "左岸") << endl;
}

void printAllPaths() {
  cout << "共找到 " << allPaths.size() << " 条解决方案：" << endl;
  
  for (int i = 0; i < allPaths.size(); i++) {
    cout << "\n解决方案 " << (i + 1) << " (共" << allPaths[i].size() << "步):" << endl;
    for (int j = 0; j < allPaths[i].size(); j++) {
      cout << "步骤 " << j << ": ";
      printState(allPaths[i][j]);
    }
  }
  
  // 找到最短路径
  int minLength = allPaths[0].size();
  int minIndex = 0;
  for (int i = 1; i < allPaths.size(); i++) {
    if (allPaths[i].size() < minLength) {
      minLength = allPaths[i].size();
      minIndex = i;
    }
  }
  
  cout << "\n=== 最短解决方案 (共" << minLength << "步) ===" << endl;
  for (int j = 0; j < allPaths[minIndex].size(); j++) {
    cout << "步骤 " << j << ": ";
    printState(allPaths[minIndex][j]);
  }
}