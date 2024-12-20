#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define v std::vector

using Ll = long long;
using Str = std::string;
using Pll = std::pair<Ll, Ll>;

// const Ll cMax = 1e17 + 1, cMin = -1e17 - 1;
// const Ll cPow = 42;
// const Ll cMod = 1234567891;
// const Ll cLg = 20;
// const int cMaxn = 1e6 + 10;

void Solve() {
  Ll n;
  std::cin >> n;
  std::map<Str, std::vector<Ll>> count;
  std::map<Str, std::vector<Ll>> rev;
  v<Str> list(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> list[i];
    Ll size = static_cast<int>(list[i].size());
    Str now;
    now += list[i][0];
    for (int j = 1; j < size; ++j) {
      bool check = true;
      for (int k = 0; k <= (size - j) / 2; ++k) {
        if (list[i][size - 1 - k] != list[i][j + k]) {
          check = false;
        }
      }
      if (check) {
        count[now].push_back(i);
      }
      now += list[i][j];
    }
    count[now].push_back(i);
    std::reverse(all(list[i]));
    now = "";
    now += list[i][0];
    for (int j = 1; j < size; ++j) {
      bool check = true;
      for (int k = 0; k <= (size - j) / 2; ++k) {
        if (list[i][size - 1 - k] != list[i][j + k]) {
          check = false;
        }
      }
      if (check) {
        rev[now].push_back(i);
      }
      now += list[i][j];
    }
    rev[now].push_back(i);
    std::reverse(all(list[i]));
  }
  std::set<Pll> ans;
  for (int i = 0; i < n; ++i) {
    Str now = list[i];
    for (auto value : rev[now]) {
      if (value != i) {
        ans.insert({i + 1, value + 1});
      }
    }
    std::reverse(all(now));
    for (auto value : count[now]) {
      if (value != i) {
        ans.insert({value + 1, i + 1});
      }
    }
  }
  std::cout << ans.size() << '\n';
  for (auto [f, s] : ans) {
    std::cout << f << ' ' << s << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::fixed;
  Solve();
}