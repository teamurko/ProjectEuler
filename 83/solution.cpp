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

typedef vector<vi> Matrix;

void readData(Matrix& matrix)
{
    int n; cin >> n;
    forn(i, n) {
        matrix.pb(vi());
        forn(j, n) {
            matrix[i].pb(0);
            cin >> matrix[i][j];
        }
    }
}

const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};

void solve()
{
    Matrix matrix;
    readData(matrix);
    const int INF = 1e8;
    const int n = matrix.size();
    Matrix d(n, vi(n, INF));
    d[0][0] = matrix[0][0];
    forn(it, n * n) {
        forn(x, n) {
            forn(y, n) {
                forn(i, 4) {
                    int xx = x + dx[i];
                    int yy = y + dy[i];
                    if (xx >= 0 && yy >= 0 && xx < n && yy < n) {
                        d[xx][yy] = min(d[xx][yy], d[x][y] + matrix[xx][yy]);
                    }
                }
            }
        }
    }
    cout << d[n - 1][n - 1] << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
