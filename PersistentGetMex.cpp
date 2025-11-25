struct NODE
{
    int l = 0, r = 0, val = 0;
};
 
struct SEGMENT_TREE
{
    int sz = 1;
    vector<NODE> tree;
    inline void Init(int n)
    {
        tree.resize(22 * n, NODE());
    }
    inline int Update(int ind, int l, int r, int x, int v)
    {
        int new_ind = ind;
        if (r < x || x < l)
        {
            return new_ind;
        }
        new_ind = sz++;
        tree[new_ind] = tree[ind];
        if (l == r)
        {
            tree[new_ind].val = v;
            return new_ind;
        }
        int m = (l + r) >> 1;
        tree[new_ind].l = Update(tree[new_ind].l, l, m, x, v);
        tree[new_ind].r = Update(tree[new_ind].r, m + 1, r, x, v);
        tree[new_ind].val = min(tree[tree[new_ind].l].val, tree[tree[new_ind].r].val);
        return new_ind;
    }
    inline int Get(int ind, int l, int r, int x)
    {
        if (l == r)
        {
            return l;
        }
        int m = (l + r) >> 1;
        if (tree[tree[ind].l].val < x)
        {
            return Get(tree[ind].l, l, m, x);
        }
        return Get(tree[ind].r, m + 1, r, x);
    }
};
