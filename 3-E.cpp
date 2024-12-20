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

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define v std::vector

using Ll = long long;
using Ld = long double;
using Str = std::string;
using Pll = std::pair<Ll, Ll>;

// const Ll cMax = 1e17 + 1;
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

Ll Getrnd(Ll l, Ll r) { return l + rnd() % (r - l + 1); }

Pll Pairmul(Pll f, Pll s, Ll p, Ll a, Ll n) {
  Pll ans;
  ans.first =
      Sum(Mul(f.first, s.first, p),
          Mul(Mul(f.second, s.second, p), Sub(Mul(a, a, p), n, p), p), p);
  ans.second = Sum(Mul(f.first, s.second, p), Mul(f.second, s.first, p), p);
  return ans;
}

Pll Pairbinpow(Pll first, Ll pow, Ll p, Ll a, Ll n) {
  Pll ans = {1, 0};
  while (pow != 0) {
    if ((pow & 1) != 0) {
      ans = Pairmul(ans, first, p, a, n);
    }
    first = Pairmul(first, first, p, a, n);
    pow = pow >> 1;
  }
  return ans;
}

void Solve() {
  Ll a;
  Ll p;
  std::cin >> a >> p;
  if (p == 2) {
    std::cout << a << '\n';
    return;
  }
  if (Binpow(a, (p - 1) / 2, p) == p - 1) {
    std::cout << "IMPOSSIBLE\n";
    return;
  }
  Ll non = -1;
  if (a == 0) {
    std::cout << 0;
    return;
  }
  while (non == -1) {
    Ll may = Getrnd(0, p - 1);
    if (Binpow(Sub(Mul(may, may, p), a, p), (p - 1) / 2, p) == p - 1) {
      non = may;
      break;
    }
  }
  Pll now = {non, 1};
  Pll ans = Pairbinpow(now, (p + 1) / 2, p, non, a);
  std::cout << ans.first << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::fixed;
  Ll t;
  std::cin >> t;
  for (int i = 0; i < t; ++i) {
    Solve();
  }
}