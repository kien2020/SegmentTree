/*
problem: https://oj.vnoi.info/problem/jewelnb
*/

#include <bits/stdc++.h>

using namespace std;

void setup()
{
#ifndef ONLINE_JUDGE
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}

struct LINE
{
    long long a = -2e9, b = -2e9;
    inline long long Val(long long x)
    {
        return a * x + b;
    }
};

struct LICHAO_TREE
{
    LINE tree[800000];
    inline void Add(int ind, int l, int r, LINE v)
    {
        int m = (l + r) >> 1;
        if (tree[ind].Val(m) < v.Val(m))
        {
            swap(tree[ind], v);
        }
        if (l < r)
        {
            if (tree[ind].Val(l) < v.Val(l))
            {
                Add(ind << 1, l, m, v);
            }
            if (tree[ind].Val(r) < v.Val(r))
            {
                Add(ind << 1 | 1, m + 1, r, v);
            }
        }
    }
    inline void Update(int ind, int l, int r, int x, int y, LINE v)
    {
        if (r < x || y < l)
        {
            return;
        }
        if (x <= l && r <= y)
        {
            Add(ind, l, r, v);
            return;
        }
        int m = (l + r) >> 1;
        Update(ind << 1, l, m, x, y, v);
        Update(ind << 1 | 1, m + 1, r, x, y, v);
    }
    inline long long Get(int ind, int l, int r, int x)
    {
        if (l == r)
        {
            return tree[ind].Val(x);
        }
        int m = (l + r) >> 1;
        if (x <= m)
        {
            return max(tree[ind].Val(x), Get(ind << 1, l, m, x));
        }
        return max(tree[ind].Val(x), Get(ind << 1 | 1, m + 1, r, x));
    }
} lichao;

long long n, m, a, b, c, d;

int main()
{
    setup();

    cin >> n >> m;
    while (m--)
    {
        cin >> a >> b >> d >> c;
        lichao.Update(1, 1, 2e5, a, b, {c, d - c * a});
    }
    for (int i = 1; i <= n; ++i)
    {
        a = lichao.Get(1, 1, 2e5, i);
        cout << (a == i * -2e9 - 2e9 ? 0 : a) << "\n";
    }
    return 0;
}
