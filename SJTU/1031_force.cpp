#include <iostream>
#include <algorithm>
#include <vector>

//本题并不符合最优子结构的情况
//1 高度差最小的路径并不一定包含高度差最小的路径
//2 和出发点，终点高度差最小也不符合情况
//3

//简单的单源最短路径方法并不能解决本题，因为存在相同最大路径差，但是上下界不同的情况。

using namespace std;

struct spot
{
    int x;
    int y;
    int h_max;
    int h_min;
    spot(int a, int b, int c, int d) : x(a), y(b), h_max(c), h_min(d){};
};

int result = 120;
int mout_max_h[110][110] = {-1};
int mout_min_h[110][110] = {-1};

void dfs(int x, int y, int max_h, int min_h, int N, bool (*vis)[110], int (*mout)[110])
{
    if (x < 0 || x >= N || y < 0 || y >= N || vis[x][y])
        return;
    max_h = max(max_h, mout[x][y]);
    min_h = min(min_h, mout[x][y]);
    if (max_h - min_h >= result)
        return;
    if (mout_max_h[x][y] != -1 && mout_max_h[x][y] <= max_h && mout_min_h[x][y] >= min_h)
        return;
    if ((mout_max_h[x][y] == -1 || mout_max_h[x][y] >= max_h) && mout_min_h[x][y] <= min_h)
    {
        mout_min_h[x][y] = min_h;
        mout_max_h[x][y] = max_h;
    }

    if (x == N - 1 && y == N - 1)
    {
        result = min(result, max_h - min_h);
        return;
    }
    vis[x][y] = 1;
    dfs(x + 1, y, max_h, min_h, N, vis, mout);
    dfs(x - 1, y, max_h, min_h, N, vis, mout);
    dfs(x, y + 1, max_h, min_h, N, vis, mout);
    dfs(x, y - 1, max_h, min_h, N, vis, mout);
    vis[x][y] = 0;
    return;
};

int main()
{
    int N;

    cin >> N;
    int mout[110][110];
    bool vis[110][110] = {0};

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> mout[i][j];
        }
    }

    dfs(0, 0, mout[0][0], mout[0][0], N, vis, mout);

    cout << result << endl;
    return 0;
}