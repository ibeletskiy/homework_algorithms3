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
using Ld = long double;
using Str = std::string;
using Pll = std::pair<Ll, Ll>;

const Ll cMax = 1e17 + 1;
// const Ll cMin = -1e17 - 1;
// const Ll cPow = 42;
// const Ll c_mod = 1e9 + 7;
// const Ll cLg = 20;
// const int cMaxn = 1e6 + 10;

Ll Sum(Ll a, Ll b, Ll c_mod) { return (a + b) % c_mod; }

Ll Sub(Ll a, Ll b, Ll c_mod) {
  a -= b;
  while (a < 0) {
    a += c_mod;
  }
  return a;
}

Ll Mul(Ll a, Ll b, Ll c_mod) { return (a * b) % c_mod; }

Ll Binpow(Ll a, Ll n, Ll c_mod) {
  Ll ans = 1;
  while (n != 0) {
    if ((n & 1) != 0) {
      ans = Mul(ans, a, c_mod);
    }
    a = Mul(a, a, c_mod);
    n = n >> 1;
  }
  return ans;
}

void Solve() {
  Ll p;
  Ll b;
  Ll n;
  while (std::cin >> p >> b >> n) {
    Ll c_root = static_cast<Ll>(sqrt(static_cast<Ld>(p)) + 1);
    Ll ans = cMax;
    std::unordered_map<Ll, Ll> value;
    for (Ll i = c_root; i >= 1; --i) {
      value[Binpow(b, i * c_root, p)] = i;
    }
    for (Ll i = 0; i <= c_root; ++i) {
      Ll now = Mul(Binpow(b, i, p), n, p);
      if (value.find(now) != value.end()) {
        Ll tmp = value[now] * c_root - i;
        ans = std::min(tmp, ans);
      }
    }
    if (ans == cMax) {
      std::cout << "no solution\n";
    } else {
      std::cout << ans << '\n';
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
