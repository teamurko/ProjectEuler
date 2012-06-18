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

bool isPrime(ll x)
{
    if (x <= 1) return false;
    for (ll y = 2; y * y <= x; ++y) {
        if (x % y == 0) return false;
    }
    return true;
}

void solve()
{
    vector<ll> primes;
    forn(i, 100000) {
        if (isPrime(i)) primes.pb(i);
    }
    const int n = 200;
    vector<vector<ll> > sumRepr(n, vector<ll>(n, 0));
    forv(i, primes) {
        ll p = primes[i];
        if (p >= n) break;
        sumRepr[p][i] = 1;
    }
    forn(i, n) {
        for (int j = 0; primes.at(j) < i; ++j) {
            for (int k = 0; k <= j; ++k) {
                sumRepr[i][j] += sumRepr[i - primes[j]][k];
            }
        }
    }
    forn(i, n) {
        ll sum = 0;
        for (int j = 0; primes[j] <= i; ++j) {
            sum += sumRepr[i][j];
        }
        if (sum > 5000) {
            cout << i << endl;
            break;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
