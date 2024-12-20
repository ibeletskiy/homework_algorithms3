#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <complex>
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
// const Ld cPi = std::acos(-1);
// const Ll cPow = 42;
// const Ll c_mod = 1e9 + 7;
// const Ll cLg = 20;
// const int cMaxn = 1e6 + 10;
const Ld cPrec = 1;
// const Ld cEps = 1e-5;
const Ld cTwo = 2.0;

struct Vec {
  Ll x;
  Ll y;

  Vec() {}

  Vec(Vec a, Vec b) : x(b.x - a.x), y(b.y - a.y) {}

  Vec(Ll x, Ll y) : x(x), y(y) {}

  Vec operator+(Vec other) const {
    Vec now = other;
    now.x += x;
    now.y += y;
    return now;
  }

  Ll operator*(Vec other) const { return x * other.x + y * other.y; }

  Ll operator^(Vec other) const { return x * other.y - y * other.x; }

  Ld Size() const { return sqrtl(x * x + y * y); }
};

v<Vec> MakeCh(v<Vec> p) {
  Ll n = p.size();
  Ll min = 0;
  for (int i = 1; i < n; ++i) {
    if (p[i].y < p[min].y) {
      min = i;
    } else if (p[i].y == p[min].y && p[i].x < p[min].x) {
      min = i;
    }
  }
  std::swap(p[0], p[min]);
  std::sort(p.begin() + 1, p.end(), [&p](Vec a, Vec b) {
    return (Vec(p[0], a) ^ Vec(p[0], b)) > 0 ||
           ((Vec(p[0], a) ^ Vec(p[0], b)) == 0 &&
            (Vec(p[0], a) * Vec(p[0], a)) < (Vec(p[0], b) * Vec(p[0], b)));
  });
  v<Vec> ch;
  if (p.size() <= 2) {
    ch = p;
    return ch;
  }
  for (int i = 0; i < n; ++i) {
    while (ch.size() >= 2 &&
           (Vec(ch.end()[-2], ch.back()) ^ Vec(ch.back(), p[i])) <= 0) {
      ch.pop_back();
    }
    ch.push_back(p[i]);
  }
  return ch;
}

void Solve() {
  Ll n;
  std::cin >> n;
  v<Vec> p(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> p[i].x >> p[i].y;
  }
  v<Vec> ch = MakeCh(p);
  Ll ans_size = static_cast<Ll>(ch.size());
  Ll s = 0;
  for (int i = 2; i < ans_size; ++i) {
    s += (Vec(ch[0], ch[i - 1]) ^ Vec(ch[0], ch[i]));
  }
  std::cout << ans_size << '\n';
  for (int i = 0; i < ans_size; ++i) {
    std::cout << ch[i].x << ' ' << ch[i].y << '\n';
  }
  std::cout << s / cTwo << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cout << std::fixed << std::setprecision(cPrec);
  Solve();
}