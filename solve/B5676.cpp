/*
	음주 코딩
	https://www.acmicpc.net/problem/5676

	곱셈 명령이 주어지면 결과에 따라 '+', '0', '-'를 출력하는 문제다.

	문제에서 원하는 결과는 양수, 0, 음수인지만 판가름하면 되므로,
	세그먼트 트리의 노드들을 get_val 함수로 초기화와 업데이트를 한다.
	이렇게 하면, 문제에서 원하는 구간 곱을 부호만을 사용하여 int 형으로도 오버플로우 없이 구현할 수 있다.
	'P' 명령어가 주어지면, print_val 함수를 통하여 부호나 0을 출력한다.
*/
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

int get_val(int num)
{
	if (num > 0)
		return 1;
	else if (num < 0)
		return -1;
	else
		return 0;
}

void print_val(int num)
{
	if (num > 0)
		cout << '+';
	else if (num < 0)
		cout << '-';
	else
		cout << '0';
}

struct SegmentTree
{
	int n;
	int tree_size;
	vector<int> range_multi;
	SegmentTree(const vector<int>& nums)
	{
		n = nums.size();
		int height = (int)ceil(log2(n));
		tree_size = (1 << (height + 1));
		range_multi.resize(tree_size);
		init(nums, 0, n - 1, 1);
	}

	int init(const vector<int>& nums, int left, int right, int node)
	{
		if (left == right)
			return range_multi[node] = get_val(nums[left]);
		int mid = (left + right) / 2;
		int left_ret = init(nums, left, mid, node * 2);
		int right_ret = init(nums, mid + 1, right, node * 2 + 1);
		return range_multi[node] = get_val(left_ret * right_ret);
	}

	int query(const vector<int>& nums, int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 1;
		if (left <= node_left && node_right <= right)
			return range_multi[node];
		int mid = (node_left + node_right) / 2;
		int left_ret = query(nums, left, right, node * 2, node_left, mid);
		int right_ret = query(nums, left, right, node * 2 + 1, mid + 1, node_right);
		return get_val(left_ret * right_ret);
	}

	int query(const vector<int>& nums, int left, int right)
	{
		return query(nums, left, right, 1, 0, n - 1);
	}

	int update(const vector<int>& nums, int idx, int new_val, int node, int node_left, int node_right)
	{
		if (idx < node_left || node_right < idx)
			return range_multi[node];
		if (node_left == node_right)
			return range_multi[node] = get_val(new_val);
		int mid = (node_left + node_right) / 2;
		int left_ret = update(nums, idx, new_val, node * 2, node_left, mid);
		int right_ret = update(nums, idx, new_val, node * 2 + 1, mid + 1, node_right);
		return range_multi[node] = get_val(left_ret * right_ret);
	}

	int update(const vector<int>& nums, int idx, int new_val)
	{
		return update(nums, idx, new_val, 1, 0, n - 1);
	}
};

int N, K;

void input(vector<int>& nums)
{
	for (int i = 0; i < N; ++i)
	{
		int tmp;
		cin >> tmp;
		nums.push_back(tmp);
	}
}

void solve(const vector<int>& nums)
{
	char cmd;
	int first, second;
	SegmentTree st(nums);
	for (int i = 0; i < K; ++i)
	{
		cin >> cmd >> first >> second;
		switch (cmd)
		{
		case 'C':
			st.update(nums, first - 1, second);
			break;
		case 'P':
			print_val(st.query(nums, first - 1, second - 1));
			break;
		}
	}
	cout << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (cin >> N)
	{
		cin >> K;
		vector<int> nums;
		input(nums);
		solve(nums);
	}
	return 0;
}