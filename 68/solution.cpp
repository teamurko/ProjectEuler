#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <utility>
#include <cassert>
#include <numeric>
using namespace std;

#define REQUIRE(cond, message) \
    do { \
        if (!(cond)) { \
            std::cerr << message << std::endl; \
        } \
    } while (false)

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define for1(i, n) for (int i = 1; i <= int(n); ++i)
#define forv(i, v) forn(i, v.size())
#define pb push_back
#define mp make_pair
#define all(v) v.begin(), v.end()

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> pii;
typedef vector<string> vs;
typedef long double ld;
typedef pair<double, double> point;

double getX(const point& pt) { return pt.first; }
double getY(const point& pt) { return pt.second; }

const int INF = std::numeric_limits<int>::max();

string ans;

void finishPlacement(vi cells, int n)
{
    assert(cells.size() == 6);
    int sum = cells.back() + cells[0] + cells[1];
    int mask = 0;
    forv(i, cells) mask |= 1 << cells[i];
    for1(i, 4) {
        int num = sum  - cells[i] - cells[(i + 1) % 5];
        if (num < 0 || num >= n) return;
        if (mask & (1 << num)) return;
        mask |= 1 << num;
        cells.pb(num);
    }
    int start = 0;
    for1(i, 4) {
        if (cells[5 + start] > cells[5 + i]) start = i;
    }
    ostringstream os;
    forn(i, 5) {
        int idx = (start + i) % 5;
        os << cells[idx + 5] + 1 << cells[idx] + 1
           << cells[(idx + 1) % 5] + 1;
    }
    string s(os.str());
    if (s.size() == 16 && s > ans) ans = s;
}

void genPlacement(vi& cells, int usedMask, int n, int rest)
{
    if (rest == 0) {
        finishPlacement(cells, n);
        return;
    }
    forn(i, n) {
        if (usedMask & (1 << i)) continue;
        cells.pb(i);
        genPlacement(cells, usedMask | (1 << i), n, rest - 1);
        cells.pop_back();
    }
}

void solve()
{
    vi cells;
    genPlacement(cells,  0, 10, 6);
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
