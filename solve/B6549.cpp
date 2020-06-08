/*
	히스토그램에서 가장 큰 직사각형
	https://www.acmicpc.net/problem/6549
	분할 정복을 통하여 빠른 시간에 가장 큰 직사각형을 구하는 문제다.

	세그먼트 트리를 사용하여 query_area 함수에서 구간 내 가장 큰 직사각형을 구한다.
	이때, query_idx 함수를 사용하여 구간 내 가장 낮은 높이의 위치 idx를 구하고,
	idx의 왼편, 현재 구간, idx의 오른편 중 가장 큰 직사각형의 넓이를 반환한다.
	그 이유는 가장 낮은 높이가 있는 idx를 제외하고 idx의 왼편과 오른편을 확인하여,
	더 높고 넓은 직사각형이 있는지 찾기 위해서다.

	query_idx 함수에서는 구간을 벗어난 경우 MAX_IDX( = 100001)을 반환한다.
	이 버려지는 값은 vector<int>& arr에 인덱스로 사용할 수 없으므로,
	조건문을 사용하여 버린다.
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