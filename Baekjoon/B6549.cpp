/*
	������׷����� ���� ū ���簢��
	https://www.acmicpc.net/problem/6549

	���� ������ ���Ͽ� ���� �ð��� ���� ū ���簢���� ���ϴ� ������.

	���׸�Ʈ Ʈ���� ����Ͽ� query_area �Լ����� ���� �� ���� ū ���簢���� ���Ѵ�.
	�̶�, query_idx �Լ��� ����Ͽ� ���� �� ���� ���� ������ ��ġ idx�� ���ϰ�,
	idx�� ����, ���� ����, idx�� ������ �� ���� ū ���簢���� ���̸� ��ȯ�Ѵ�.
	�� ������ ���� ���� ���̰� �ִ� idx�� �����ϰ� idx�� ����� �������� Ȯ���Ͽ�,
	�� ���� ���� ���簢���� �ִ��� ã�� ���ؼ���.

	query_idx �Լ������� ������ ��� ��� MAX_IDX( = 100001)�� ��ȯ�Ѵ�.
	�� �������� ���� vector<int>& arr�� �ε����� ����� �� �����Ƿ�,
	���ǹ��� ����Ͽ� ������.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
constexpr auto MAX_IDX = 100001;

struct SegmentTree
{
    int n;
    vector<int> range_idx;
    SegmentTree(const vector<int> &arr)
    {
        n = arr.size();
        range_idx.resize(n * 4);
        init(arr, 0, n - 1, 1);
    }

    int init(const vector<int> &arr, int left, int right, int node)
    {
        if (left == right)
            return range_idx[node] = left;
        int mid = (left + right) / 2;
        int left_idx = init(arr, left, mid, node * 2);
        int right_idx = init(arr, mid + 1, right, node * 2 + 1);
        return range_idx[node] = arr[left_idx] < arr[right_idx] ? left_idx : right_idx;
    }

    int query_idx(const vector<int> &arr, int left, int right, int node, int node_left, int node_right)
    {
        if (right < node_left || node_right < left)
            return MAX_IDX;
        if (left <= node_left && node_right <= right)
            return range_idx[node];
        int mid = (node_left + node_right) / 2;
        int left_idx = query_idx(arr, left, right, node * 2, node_left, mid);
        int right_idx = query_idx(arr, left, right, node * 2 + 1, mid + 1, node_right);
        if (left_idx == MAX_IDX)
            return right_idx;
        else if (right_idx == MAX_IDX)
            return left_idx;
        return arr[left_idx] < arr[right_idx] ? left_idx : right_idx;
    }

    int query_idx(const vector<int> &arr, int left, int right)
    {
        return query_idx(arr, left, right, 1, 0, n - 1);
    }

    ll query_area(const vector<int> &arr, ll left, ll right)
    {
        ll idx = (ll)query_idx(arr, (int)left, (int)right);
        ll area = (ll)arr[(int)idx] * (right - left + 1);
        if (left <= idx - 1)
        {
            ll left_area = query_area(arr, left, idx - 1);
            area = max(area, left_area);
        }
        if (idx + 1 <= right)
        {
            ll right_area = query_area(arr, idx + 1, right);
            area = max(area, right_area);
        }
        return area;
    }
};

void input(vector<int> &rects, const int &n)
{
    for (int i = 0; i < n; ++i)
    {
        int rect;
        cin >> rect;
        rects.push_back(rect);
    }
}

void solve()
{
    int n;

    cin >> n;
    while (n)
    {
        vector<int> rects;
        input(rects, n);
        SegmentTree st(rects);
        cout << st.query_area(rects, 0, (ll)rects.size() - 1) << '\n';
        cin >> n;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}