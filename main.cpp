#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using pll = pair<ll, ll>;
using vp = vector<pll>;

ll N, M, H;
bool used[31][11];
bool found = false;

bool Check(ll s) {
  auto now = s;
  auto h = 1;
  while (h <= H) {
    if (used[h][now]) {
      now += 1;
      ++h;
    } else if (now > 0 && used[h][now - 1]) {
      now -= 1;
      ++h;
    } else {
      ++h;
    }
  }

  return s == now;
}
bool CheckDone() {
  for (auto s = 1; s <= N; ++s) {
    if (!Check(s)) return false;
  }

  return true;
}
void solve(ll t, ll max_t) {
  if (t == max_t) {
    if (CheckDone()) {
      found = true;
    }

    return;
  }

  for (auto j = 1; j < N; ++j) {
    for (auto h = 1; h <= H; ++h) {
      if (used[h][j] || used[h][j - 1] || used[h][j + 1]) continue;

      used[h][j] = true;
      solve(t + 1, max_t);
      used[h][j] = false;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M >> H;
  for (auto h = 0; h < 31; ++h) {
    for (auto n = 0; n < 11; ++n) {
      used[h][n] = false;
    }
  }

  for (auto i = 0; i < M; ++i) {
    ll a, b;
    cin >> a >> b;

    used[a][b] = true;
  }

  for (auto i = 0; !found && i < 4; ++i) {
    solve(0, i);
    if (found) {
      cout << i;
      return 0;
    }
  }

  cout << -1;

  return 0;
}