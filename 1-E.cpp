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

using Ll = int;
using Str = std::string;
using Pll = std::pair<Ll, Ll>;

// const Ll cMax = 1e17 + 1, cMin = -1e17 - 1;
// const Ll cPow = 42;
const Ll cTen = 10;
// const Ll cMod = 1234567891;
// const Ll cLg = 20;
// const int cMaxn = 1e6 + 10;

struct Node {
  int f, b;
  Ll sum;

  Node(Ll f, Ll b) : f(f), b(b), sum(0) {}
  std::unordered_map<Ll, Ll> to;
};

std::vector<Node> nodes;

void Add(std::string s, Ll t) {
  Ll n = static_cast<Ll>(s.size());
  for (int i = 0; i < n; ++i) {
    Ll now = (s[i] - '0') * cTen + (s[n - 1 - i] - '0');
    nodes[t].sum += 1;
    if (nodes[t].to[now] == 0) {
      nodes[t].to[now] = nodes.size();
      nodes.push_back(Node(s[i] - '0', s[n - 1 - i] - '0'));
    }
    t = nodes[t].to[now];
  }
  nodes[t].sum += 1;
}

v<Ll> ans;

void Find(Ll t, Ll d, Ll k) {
  if (nodes[t].sum >= k) {
    ans[d] += 1;
  }
  for (auto [key, val] : nodes[t].to) {
    Find(val, d + 1, k);
  }
}

void Solve() {
  Ll n;
  Ll k;
  std::cin >> n >> k;
  nodes.assign(1, Node(0, 0));
  Ll root = 0;
  Ll max = 0;
  for (int i = 0; i < n; ++i) {
    Str a;
    std::cin >> a;
    Add(a, root);
    max = std::max(max, static_cast<Ll>(a.size()));
  }
  ans.assign(max + 1, 0);
  Find(root, 0, k);
  Ll q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    Ll l;
    std::cin >> l;
    if (l >= static_cast<Ll>(ans.size())) {
      std::cout << 0 << '\n';
    } else {
      std::cout << ans[l] << '\n';
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::fixed;
  Solve();
}
