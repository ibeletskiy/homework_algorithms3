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

void MakeSuf(const Str& s, v<Ll>& a, v<Ll>& c) {
  v<std::pair<char, Ll>> tmp;
  Ll n = s.size();
  a.resize(n);
  c.resize(n);
  for (int i = 0; i < n; ++i) {
    tmp.push_back({s[i], i});
  }
  std::sort(all(tmp));
  v<Ll> first(n);
  Ll cc = -1;
  for (int i = 0; i < n; ++i) {
    a[i] = tmp[i].second;
    if (i == 0 || tmp[i].first != tmp[i - 1].first) {
      ++cc;
      first[cc] = i;
    }
    c[a[i]] = cc;
  }
  v<Ll> a1(n);
  v<Ll> c1(n);
  Ll len = 1;
  while (len < n) {
    for (int i = 0; i < n; ++i) {
      Ll j = (a[i] - len + n) % n;
      a1[first[c[j]]++] = j;
    }
    a = a1;
    Ll cc = -1;
    for (int i = 0; i < n; ++i) {
      if (i == 0 || c[a[i]] != c[a[i - 1]] ||
          c[(a[i] + len + n) % n] != c[(a[i - 1] + len + n) % n]) {
        ++cc;
        first[cc] = i;
      }
      c1[a[i]] = cc;
    }
    c = c1;
    len *= 2;
  }
}

void Solve() {
  Str s;
  std::cin >> s;
  v<Ll> a;
  v<Ll> c;
  Ll n = s.size();
  MakeSuf(s, a, c);
  for (int i = 0; i < n; ++i) {
    std::cout << s[(a[i] + n - 1) % n];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::fixed;
  Solve();
}