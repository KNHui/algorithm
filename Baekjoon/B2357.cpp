/*
    �ּڰ��� �ִ�
    https://www.acmicpc.net/problem/2357

    �ּڰ��� �ִ��� �� �� ���ؾ� �ϴ� ������.

    ���� �ּ� Ʈ���� �����Ͽ� �� ������ �ּڰ��� �ִ��� ��� �������� �Ͽ���.
    �׸��� �ּڰ��� �ִ��� ���� �Լ��� ���� ������־���.

    �ԷµǴ� �������� 1 �̻� 1,000,000,000 ������ ���� ������.
    �׷��� �ִ��� ã�� query_max �Լ������� ������ ����� 0�� �����ϰ�,
    �ּڰ��� ã�� query_min �Լ������� ������ ����� 1,000,000,001�� �����Ѵ�.
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