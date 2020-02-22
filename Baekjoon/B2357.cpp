/*
    최솟값과 최댓값
    https://www.acmicpc.net/problem/2357

    최솟값과 최댓값을 둘 다 구해야 하는 문제다.

    구간 최소 트리를 수정하여 각 구간의 최솟값과 최댓값을 모두 가지도록 하였다.
    그리고 최솟값과 최댓값을 위한 함수를 따로 만들어주었다.

    입력되는 정수들은 1 이상 1,000,000,000 이하의 값을 가진다.
    그래서 최댓값을 찾는 query_max 함수에서는 구간을 벗어나면 0을 리턴하고,
    최솟값을 찾는 query_min 함수에서는 구간을 벗어나면 1,000,000,001을 리턴한다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct SegmentTree
{
	int n;
	vector<int> range_max;
	vector<int> range_min;
	SegmentTree(const vector<int> &arr)
	{
		n = arr.size();
		range_max.resize(n * 4);
		range_min.resize(n * 4);
		init_max(arr, 0, n - 1, 1);
		init_min(arr, 0, n - 1, 1);
	}

	int init_max(const vector<int> &arr, int left, int right, int node)
	{
		if (left == right)
			return range_max[node] = arr[left];
		int mid = (left + right) / 2;
		int left_max = init_max(arr, left, mid, node * 2);
		int right_max = init_max(arr, mid + 1, right, node * 2 + 1);
		return range_max[node] = max(left_max, right_max);
	}

	int init_min(const vector<int> &arr, int left, int right, int node)
	{
		if (left == right)
			return range_min[node] = arr[left];
		int mid = (left + right) / 2;
		int left_min = init_min(arr, left, mid, node * 2);
		int right_min = init_min(arr, mid + 1, right, node * 2 + 1);

		return range_min[node] = min(left_min, right_min);
	}

	int query_max(int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 0;
		if (left <= node_left && node_right <= right)
			return range_max[node];
		int mid = (node_left + node_right) / 2;
		int left_max = query_max(left, right, node * 2, node_left, mid);
		int right_max = query_max(left, right, node * 2 + 1, mid + 1, node_right);
		return max(left_max, right_max);
	}

	int query_max(int left, int right)
	{
		return query_max(left, right, 1, 0, n - 1);
	}

	int query_min(int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 1000000001;
		if (left <= node_left && node_right <= right)
			return range_min[node];
		int mid = (node_left + node_right) / 2;
		int left_min = query_min(left, right, node * 2, node_left, mid);
		int right_min = query_min(left, right, node * 2 + 1, mid + 1, node_right);
		return min(left_min, right_min);
	}

	int query_min(int left, int right)
	{
		return query_min(left, right, 1, 0, n - 1);
	}
};

int N, M;

void init(vector<int> &nums)
{
	cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		int num;
		cin >> num;
		nums.push_back(num);
	}
}

void solve(const vector<int> &nums)
{
	SegmentTree st(nums);
	for (int i = 0; i < M; ++i)
	{
		int left, right;
		cin >> left >> right;
		cout << st.query_min(left - 1, right - 1) << ' ' << st.query_max(left - 1, right - 1) << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> nums;
	init(nums);
	solve(nums);
	return 0;
}