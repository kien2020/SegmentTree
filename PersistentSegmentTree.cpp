/*
Author: chikien2009

This code solve the problem "Range Queries and Copies" on CSES
Problem Link: https://cses.fi/problemset/task/1737/
*/
#include <bits/stdc++.h>

using namespace std;

template <typename container_data_type, typename input_data_type>
class PERSISTENT_SEGMENT_TREE
{
private:
    struct NODE
    {
        int left_index, right_index;
        container_data_type sum;
    };
    vector<NODE> nodes;
    vector<input_data_type> base;
    vector<int> root;
    int latest_index, len;
    inline void Build(int l, int r)
    {
        int current_index = latest_index++;
        nodes.push_back({0, 0, 0});
        nodes[current_index].left_index = -1;
        nodes[current_index].right_index = -1;
        if (l == r)
        {
            nodes[current_index].sum = base[l];
            return;
        }
        int m = (l + r) >> 1;
        nodes[current_index].left_index = latest_index;
        Build(l, m);
        nodes[current_index].right_index = latest_index;
        Build(m + 1, r);
        nodes[current_index].sum = nodes[nodes[current_index].left_index].sum +
                                   nodes[nodes[current_index].right_index].sum;
    }
    inline container_data_type Get(int ind, int l, int r, int x, int y)
    {
        if (x <= l && r <= y)
        {
            return nodes[ind].sum;
        }
        if (r < x || y < l)
        {
            return 0;
        }
        int m = (l + r) >> 1;
        container_data_type current_sum = 0;
        if (max(l, x) <= min(m, y))
        {
            current_sum += Get(nodes[ind].left_index, l, m, x, y);
        }
        if (max(m + 1, x) <= min(r, y))
        {
            current_sum += Get(nodes[ind].right_index, m + 1, r, x, y);
        }
        return current_sum;
    }
    inline void Update(int ind, int l, int r, int p, int x)
    {
        int current_index = latest_index++;
        nodes.push_back(nodes[ind]);
        if (l == r)
        {
            nodes[current_index].sum = x;
            return;
        }
        int m = (l + r) >> 1;
        if (l <= p && p <= m)
        {
            nodes[current_index].left_index = latest_index;
            Update(nodes[ind].left_index, l, m, p, x);
        }
        else
        {
            nodes[current_index].right_index = latest_index;
            Update(nodes[ind].right_index, m + 1, r, p, x);
        }
        nodes[current_index].sum = nodes[nodes[current_index].left_index].sum +
                                   nodes[nodes[current_index].right_index].sum;
    }

public:
    inline PERSISTENT_SEGMENT_TREE(vector<input_data_type> inp)
    {
        nodes.clear();
        base = inp;
        len = inp.size();
        base.insert(base.begin(), 0);
        latest_index = 0;
        Build(1, len);
        root.clear();
        root.push_back(0);
    }
    inline container_data_type Get(int k, int x, input_data_type y)
    {
        return Get(root[k], 1, len, x, y);
    }
    inline void Add(int parrent_version)
    {
        root.push_back(root[parrent_version]);
    }
    inline void Update(int k, int p, int x)
    {
        int new_root = latest_index;
        Update(root[k], 1, len, p, x);
        root[k] = new_root;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q, a, b, c, mode;
    vector<int> v;
    cin >> n >> q;
    v.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    PERSISTENT_SEGMENT_TREE<long long, int> segment_tree(v);
    while (q--)
    {
        cin >> mode;
        if (mode == 1)
        {
            cin >> a >> b >> c;
            segment_tree.Update(a - 1, b, c);
        }
        else if (mode == 2)
        {
            cin >> a >> b >> c;
            cout << segment_tree.Get(a - 1, b, c) << "\n";
        }
        else
        {
            cin >> a;
            segment_tree.Add(a - 1);
        }
    }
    return 0;
}
