/*
	커피숍2
	https://www.acmicpc.net/problem/1275

	백준 2042번 "구간 합 구하기"와 같은 "세그먼트 트리" 문제다.
	(https://github.com/KNHui/algorithm/blob/260b30312ba7b00b1e1effebf2df305c50b3f3c4/Baekjoon/B2042.cpp)

	백준의 노트 부분을 읽어보면, 구간 "[x, y]"에서 'x'가 'y'보다 클 수도 있다고 한다.
	따라서 "x > y"인 경우, 'x' 와 'y'를 교환하고 진행했다.
*/
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

int N, Q;

struct SegmentTree
{
	int			n;
	int			tree_size;
	vector<ll>	range_sum;

	SegmentTree(const vector<int> &nums)
	{
		n = nums.size();
		int height = (int)ceil(log2(n));
		tree_size = (1 << (height + 1));
		range_sum.resize(tree_size);
		init(nums, 0, n - 1, 1);
	}

	ll init(const vector<int> &nums, int left, int right, int node)
	{
		if (left == right)
			return range_sum[node] = nums[left];
		int	mid = (left + right) / 2;
		ll	left_sum = init(nums, left, mid, node * 2);
		ll	right_sum = init(nums, mid + 1, right, node * 2 + 1);

		return range_sum[node] = left_sum + right_sum;
	}

	ll query(int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 0;
		if (left <= node_left && node_right <= right)
			return range_sum[node];
		int	mid = (node_left + node_right) / 2;
		ll	left_sum = query(left, right, node * 2, node_left, mid);
		ll	right_sum = query(left, right, node * 2 + 1, mid + 1, node_right);

		return left_sum + right_sum;
	}

	ll query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}

	ll update(int idx, int new_val, int node, int node_left, int node_right)
	{
		if (idx < node_left || node_right < idx)
			return range_sum[node];
		if (node_left == node_right)
			return range_sum[node] = new_val;
		int	mid = (node_left + node_right) / 2;
		ll	left_sum = update(idx, new_val, node * 2, node_left, mid);
		ll	right_sum = update(idx, new_val, node * 2 + 1, mid + 1, node_right);

		return range_sum[node] = left_sum + right_sum;
	}

	ll update(int idx, int new_val)
	{
		return update(idx, new_val, 1, 0, n - 1);
	}
};

void input(vector<int> &nums)
{
	cin >> N >> Q;
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
	for (int i = 0; i < Q; ++i)
	{
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		if (x > y)
			swap(x, y);
		cout << st.query(x - 1, y - 1) << '\n';
		st.update(a - 1, b);
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