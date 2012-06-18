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

void printUsage(const char* name)
{
    cerr << "Usage : " << name << " number" << endl;
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    if (argc != 2) {
        printUsage(argv[0]);
        return 0;
    }
    int n = atoi(argv[1]);
    vector<vi> d(n + 1, vi(n + 1));
    d[0][0] = 1;
    cerr << "Allocation done" << endl;
    for (int i = 1; i <= n; ++i) {
        d[i][i] = 1;
        for (int k = i - 1; k >= 1; --k) {
            if (i - k >= k) {
                d[i][k] +=d[i - k][k];
            }
            d[i][k] += d[i][k + 1];
            d[i][k] %= 1000000;
        }
        if (d[i][1] == 0) {
            cout << i << endl;
        }
    }
    return 0;
}
