template <typename container_type, typename value_type>
class SEGMENT_TREE
{
private:
    struct NODE
    {
        container_type max_prefix_sum, max_suffix_sum, max_sum, entire_sum;
        inline NODE operator+(const NODE &inp)
        {
            NODE result;
            result.max_prefix_sum = max(this->max_prefix_sum, this->entire_sum + inp.max_prefix_sum);
            result.max_suffix_sum = max(inp.max_suffix_sum, inp.entire_sum + this->max_suffix_sum);
            result.max_sum = max({this->max_sum, inp.max_sum, this->max_suffix_sum + inp.max_prefix_sum});
            result.entire_sum = this->entire_sum + inp.entire_sum;
            return result;
        }
    };
    int tree_size;
    vector<NODE> tree;
    vector<value_type> base;
    inline void Build(int ind, int l, int r)
    {
        if (l == r)
        {
            tree[ind].entire_sum = base[l];
            tree[ind].max_prefix_sum = max(0, base[l]);
            tree[ind].max_suffix_sum = max(0, base[l]);
            tree[ind].max_sum = max(0, base[l]);
            return;
        }
        int m = (l + r) >> 1;
        Build(ind << 1, l, m);
        Build(ind << 1 | 1, m + 1, r);
        tree[ind] = tree[ind << 1] + tree[ind << 1 | 1];
    }
    inline void Update(int ind, int l, int r, int pos, value_type val)
    {
        if (pos < l || r < pos)
        {
            return;
        }
        if (l == r)
        {
            tree[ind].entire_sum = val;
            tree[ind].max_suffix_sum = max(0, val);
            tree[ind].max_prefix_sum = max(0, val);
            tree[ind].max_sum = max(0, val);
            return;
        }
        int m = (l + r) >> 1;
        Update(ind << 1, l, m, pos, val);
        Update(ind << 1 | 1, m + 1, r, pos, val);
        tree[ind] = tree[ind << 1] + tree[ind << 1 | 1];
    }

public:
    inline void Init(vector<value_type> inp)
    {
        tree.clear();
        base.clear();
        tree_size = inp.size();
        tree.resize(tree_size << 2);
        base = inp;
        base.insert(base.begin(), 0);
        Build(1, 1, tree_size);
    }
    inline void Update(int pos, value_type val)
    {
        Update(1, 1, tree_size, pos, val);
    }
    inline container_type MaxSum()
    {
        return tree[1].max_sum;
    }
};
