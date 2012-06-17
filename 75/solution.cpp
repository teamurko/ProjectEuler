#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
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


void solve()
{
    const ll MAXL = 1500 * 1000;
    vector<set<ll> > triples(MAXL + 1);
    for (ll n = 1; 2 * n * (n + 1) <= MAXL; ++n) {
        for (ll m = n + 1; ; ++m) {
            ll s = 2 * m * m + 2 * n * m;
            if (s > MAXL) break;
            for (int k = 1; k * s <= MAXL; ++k) {
                triples[k * s].insert(k * (m * m + n * n));
            }
        }
    }
    ll ans = 0;
    for (ll i = 0; i <= MAXL; ++i) {
        if (triples[i].size() == 1) {
            ++ans;
        }
    }
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
