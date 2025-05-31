/*
problem: https://codeforces.com/problemset/problem/932/F
*/

struct LINE
{
    long long a, b;
    inline LINE()
    {
        a = 1e9;
        b = 9e18;
    }
    inline LINE(long long new_a, long long new_b)
    {
        a = new_a;
        b = new_b;
    }
    inline long long Val(long long x)
    {
        return a * x + b;
    }
};

struct NODE
{
    LINE v = LINE();
    int l, r;
};

struct LICHAOTREE
{
    int sz_tree = 0;
    NODE tree[100000];
    vector<int> empty_node;
    inline int New(LINE inp)
    {
        int ind;
        if (!empty_node.empty())
        {
            ind = empty_node.back();
            empty_node.pop_back();
        }
        else
        {
            ind = sz_tree++;
        }
        tree[ind].l = tree[ind].r = -1;
        tree[ind].v = inp;
        return ind;
    }
    inline void Release(int ind)
    {
        empty_node.push_back(ind);
    }
    inline void Update(int &ind, int l, int r, LINE inp)
    {
        if (ind == -1)
        {
            ind = New(inp);
            return;
        }
        int m = (l + r) / 2;
        if (inp.Val(m) < tree[ind].v.Val(m))
        {
            swap(inp, tree[ind].v);
        }
        if (l < r)
        {
            if (inp.Val(l) < tree[ind].v.Val(l))
            {
                Update(tree[ind].l, l, m, inp);
            }
            if (inp.Val(r) < tree[ind].v.Val(r))
            {
                Update(tree[ind].r, m + 1, r, inp);
            }
        }
    }
    inline long long Get(int ind, int l, int r, long long x)
    {
        if (ind == -1)
        {
            return 9e18;
        }
        if (l == r)
        {
            return tree[ind].v.Val(x);
        }
        int m = (l + r) / 2;
        if (x <= m)
        {
            return min(tree[ind].v.Val(x), Get(tree[ind].l, l, m, x));
        }
        return min(tree[ind].v.Val(x), Get(tree[ind].r, m + 1, r, x));
    }
    inline void Merge(int &ind, int oth, int l, int r)
    {
        if (ind == -1 || oth == -1)
        {
            ind = (ind == -1 ? oth : ind);
            return;
        }
        int m = (l + r) / 2;
        Update(ind, l, r, tree[oth].v);
        Merge(tree[ind].l, tree[oth].l, l, m);
        Merge(tree[ind].r, tree[oth].r, m + 1, r);
        Release(oth);
    }
};
