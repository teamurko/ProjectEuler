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
            assert(false); \
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

const long long MIN_LIMIT = 20000;
long long maxK = 12000;

vector<long long> minNumberK;

void rec(vector<int>& a, long long prod, long long sum)
{
    REQUIRE(!a.empty(), "There should be at least 1 summand");
    if (a.size() >= 2) {
        long long diff = prod * a.back() - sum - a.back();
        long long k = diff + static_cast<long long>(a.size());
        if (diff >= 0 && k <= maxK) {
            minNumberK[k]= min(minNumberK[k], prod * a.back());
        }
    }
    ll diff = prod * a.back() - sum - a.back();
    if (diff > maxK) return;
    if (a.size() == 1 && a.back() >= MIN_LIMIT) return;
    ++a.back();
    rec(a, prod, sum);
    --a.back();
    a.push_back(a.back());
    prod *= a.back();
    sum += a.back();
    rec(a, prod, sum);
    a.pop_back();
}

void solve()
{
    vector<int> a(1, 2);
    minNumberK.resize(maxK+1, INF);
    rec(a, 1, 0);
    set<long long> ans;
    for (long long i = 2; i <= maxK; ++i) {
        REQUIRE(minNumberK[i] != INF,
                "Representation for " << i << " is not found.");
        ans.insert(minNumberK[i]);
    }
    long long sum = 0;
    for (auto x : ans) {
        sum += x;
    }
    cout << "Sum : " << sum << endl;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    if (argc != 2) {
        cerr << "Usage : " << argv[0] << " mink" << endl;
        return 1;
    }
    maxK = atoi(argv[1]);
    solve();
    return 0;
}
