/*
	����
	https://www.acmicpc.net/problem/7578

	A ���� ���Ұ� ������ ������ B ���� �ְ�, ���� ���� ���Ҹ� ���̺�� �������� ��,
	���� �����ϴ� ���̺� ���� ������ ���ϴ� ������.

	A ���� ��ȣ�� B ���� ��ȣ�� �湮�ϰ�,
	B ���� ��ȣ �����ʿ� �ִ� ��ȣ �߿��� ������ �湮�� ��ȣ�� ���� ret �� �����ְ�,
	���� �� ret �� ����ϴ� Inversion Counting ������.

	Inversion Counting�� ���Ͽ� vector A_col(A ��)���� �ĺ���ȣ�� �����ϰ�,
	int B_col[MAX_IDX](B ��)���� �ĺ���ȣ�� �ε����� �ϰ�, �� ��°������ ������ �����Ѵ�.

	�湮�� ��ȣ�� ���� ������ ���ϱ� ���Ͽ� SegmentTree�� ����ߴ�.
	query �Լ����� ���� B_col[A_col[i]](��ȣ�� B �� ��° ��) ~ N - 1(������ ��)�� �ִ� �湮�� ��ȣ�� ���� ���Ѵ�.
	update �Լ����� ����� �ĺ���ȣ�� �ش��ϴ� ���� ���� �θ� ������ �����Ѵ�.
*/
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

constexpr auto MAX_IDX = 1000001;

struct SegmentTree
{
    int n;
    int tree_size;
    vector<long long> range_right_visit_cnt;
    SegmentTree(const vector<int> &idxs)
    {
        n = idxs.size();
        int height = (int)ceil(log2(n));
        tree_size = (1 << (height + 1));
        range_right_visit_cnt.resize(tree_size);
        init(0, n - 1, 1);
    }

    long long init(int left, int right, int node)
    {
        if (left == right)
            return range_right_visit_cnt[left] = 0;
        int mid = (left + right) / 2;
        init(left, mid, node * 2);
        init(mid + 1, right, node * 2 + 1);
        return range_right_visit_cnt[left] = 0;
    }

    long long query(int left, int right, int node, int node_left, int node_right)
    {
        if (right < node_left || node_right < left)
            return 0;
        if (left <= node_left && node_right <= right)
            return range_right_visit_cnt[node];
        int mid = (node_left + node_right) / 2;
        long long left_cnt = query(left, right, node * 2, node_left, mid);
        long long right_cnt = query(left, right, node * 2 + 1, mid + 1, node_right);
        return left_cnt + right_cnt;
    }

    long long query(int left)
    {
        return query(left, n - 1, 1, 0, n - 1);
    }

    long long update(int left, int right, int node, int idx)
    {
        if (idx < left || right < idx)
            return range_right_visit_cnt[node];
        if (left == right)
            return range_right_visit_cnt[node] = 1;
        int mid = (left + right) / 2;
        long long left_cnt = update(left, mid, node * 2, idx);
        long long right_cnt = update(mid + 1, right, node * 2 + 1, idx);
        return range_right_visit_cnt[node] = left_cnt + right_cnt;
    }

    long long update(int idx)
    {
        return update(0, n - 1, 1, idx);
    }
};

int N;
int B_col[MAX_IDX];

void input(vector<int> &A_col)
{
    cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int idx;
        cin >> idx;
        A_col.push_back(idx);
    }
    for (int i = 0; i < N; ++i)
    {
        int idx;
        cin >> idx;
        B_col[idx] = i;
    }
}

long long solve(const vector<int> &A_col)
{
    long long ret = 0;
    SegmentTree st(A_col);
    for (int i = 0; i < N; ++i)
    {
        ret += st.query(B_col[A_col[i]]);
        st.update(B_col[A_col[i]]);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> A_col;
    input(A_col);
    long long ans = solve(A_col);
    cout << ans;
    return 0;
}