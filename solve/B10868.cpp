/*
	최솟값
	https://www.acmicpc.net/problem/10868

	N 개의 수를 입력받고, M 개의 구간을 주면,
	해당 구간의 최솟값을 구하는 문제다.

	완전 탐색으로 구간에서 최솟값을 찾으면, O(N)으로 오랜 시간이 걸린다.
	세그먼트 트리를 사용하여 최솟값을 찾으면, O(logN)의 시간이 걸리기에 문제를 해결할 수 있다.

	입력으로 주어지는 각각의 정수들은 1 이상 1,000,000,000 이하의 값을 가진다.
	그래서 최솟값을 구하는 query 함수에서 구간을 벗어났을 때 버리는 값은 1,000,000,001로 했다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr auto MAX = 1000000001;
int N, M;

struct SegmentTree
{
	int n;
	vector<int> range_min;
	SegmentTree(const vector<int> &nums)
	{
		n = nums.size();
		range_min.resize(n * 4);
		init(nums, 0, n - 1, 1);
	}

	int init(const vector<int> &nums, int left, int right, int node)
	{
		if (left == right)
			return range_min[node] = nums[left];
		int mid = (left + right) / 2;
		int left_min = init(nums, left, mid, node * 2);
		int right_min = init(nums, mid + 1, right, node * 2 + 1);
		return range_min[node] = min(left_min, right_min);
	}

	int query(const vector<int> &nums, int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return MAX;
		if (left <= node_left && node_right <= right)
			return range_min[node];
		int mid = (node_left + node_right) / 2;
		int left_min = query(nums, left, right, node * 2, node_left, mid);
		int right_min = query(nums, left, right, node * 2 + 1, mid + 1, node_right);
		return min(left_min, right_min);
	}

	int query(const vector<int> &nums, int left, int right)
	{
		return query(nums, left, right, 1, 0, n - 1);
	}
};

void input(vector<int> &nums)
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
		cout << st.query(nums, left - 1, right - 1) << '\n';
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	vector<int> nums;
	input(nums);
	solve(nums);
	return 0;
}
