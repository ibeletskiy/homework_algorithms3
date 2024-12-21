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

// const Ll cMax = 1e9 + 1;
// const Ll cMin = -1e17 - 1;
const Ld cPi = std::acos(-1);
// const Ll cPow = 42;
// const Ll c_mod = 1e9 + 7;
// const Ll cLg = 20;
// const int cMaxn = 1e6 + 10;
const Ld cPrec = 10;
const Ld cEps = 1e-12;

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

struct Line {
  Ld a;
  Ld b;
  Ld c;

  Line(Vec f, Vec s) {
    a = (s.y - f.y);
    b = (f.x - s.x);
    c = -f.x * s.y + f.y * s.x;
  }
};

struct Seg {
  Vec f;
  Vec s;

  Seg(Vec f, Vec s) : f(f), s(s) {}
};

Ld LineDist(Line now, Vec p) {
  return std::abs((now.a * p.x + now.b * p.y + now.c)) /
         sqrtl(now.a * now.a + now.b * now.b);
}

Ld SegDist(Seg now, Vec p) {
  if (Vec(now.f, p) * Vec(now.f, now.s) < cEps) {
    return Vec(p, now.f).Size();
  }
  if (Vec(p, now.s) * Vec(now.f, now.s) < cEps) {
    return Vec(p, now.s).Size();
  }
  return LineDist(Line(now.f, now.s), p);
}

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

v<Vec> Diff(const v<Vec>& now) {
  Ll n = now.size();
  v<Vec> ans(n);
  for (int i = 0; i < n; ++i) {
    if (i == n - 1) {
      ans[i] = Vec(now[i], now[0]);
    } else {
      ans[i] = Vec(now[i], now[i + 1]);
    }
  }
  return ans;
}

v<Vec> operator-(const v<Vec>& now) {
  v<Vec> ans = now;
  for (auto& i : ans) {
    i = Vec(-i.x, -i.y);
  }
  return ans;
}

v<Vec> operator+(const v<Vec>& a, const v<Vec>& b) {
  v<Vec> da = Diff(a);
  v<Vec> db = Diff(b);
  v<Vec> dc;
  merge(all(da), all(db), back_inserter(dc),
        [](Vec x, Vec y) { return (x ^ y) > 0; });
  v<Vec> c = {a[0] + b[0]};
  for (auto now : dc) {
    c.push_back(c.back() + now);
  }
  c.pop_back();
  return c;
}

bool CheckIn(v<Vec>& hull, Vec p) {
  if (p.y < hull[0].y) {
    return false;
  }
  Ll lhs = 1;
  Ll rhs = hull.size();
  while (rhs - lhs > 1) {
    Ll mid = lhs + (rhs - lhs) / 2;
    if ((Vec(hull[0], p) ^ Vec(hull[0], hull[mid])) < 0) {
      lhs = mid;
    } else {
      rhs = mid;
    }
  }
  if (rhs == static_cast<Ll>(hull.size())) {
    return false;
  }
  Ll sum = std::abs(Vec(p, hull[0]) ^ Vec(p, hull[lhs])) +
           std::abs(Vec(p, hull[lhs]) ^ Vec(p, hull[rhs])) +
           std::abs(Vec(p, hull[rhs]) ^ Vec(p, hull[0]));
  return (Vec(hull[0], hull[lhs]) ^ Vec(hull[0], hull[rhs])) == sum;
}

void Solve() {
  Ll n;
  std::cin >> n;
  v<Vec> f(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> f[i].x >> f[i].y;
  }
  Ll m;
  std::cin >> m;
  v<Vec> s(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> s[i].x >> s[i].y;
  }
  Ll k;
  std::cin >> k;
  v<Vec> t(k);
  for (int i = 0; i < k; ++i) {
    std::cin >> t[i].x >> t[i].y;
  }
  v<Vec> ft = MakeCh(f);
  v<Vec> st = MakeCh(s);
  v<Vec> tt = MakeCh(t);
  v<Vec> ans = MakeCh((ft + st) + tt);
  Ll q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    Vec p;
    std::cin >> p.x >> p.y;
    p.x *= 3;
    p.y *= 3;
    std::cout << (CheckIn(ans, p) ? "YES" : "NO") << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  std::cout << std::fixed << std::setprecision(cPrec);
  Solve();
}