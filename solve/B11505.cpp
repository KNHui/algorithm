/*
	구간 곱 구하기
	https://www.acmicpc.net/problem/11505

	배열의 요소를 바꾸거나, 주어지는 구간의 곱을 출력하는 문제다.

	구간의 조회와 요소의 업데이트가 많이 일어나는데,
	세그먼트 트리를 이용하면 O(logN) 만에 각 명령어를 해결할 수 있다.
	오버플로우를 방지하기 위해 구간 곱을 저장하는 range_multi를 long long으로 선언했다.
	출력할 때는 구간의 곱을 1,000,000,007로 나눈 나머지를 출력하기 때문에
	곱 연산이 일어날 때마다 1,000,000,007로 나머지 연산을 하여 오버플로우를 방지했다.
*/
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

constexpr auto DENOMINATOR = 1000000007;

int N, M, K;
vector<int> nums;

struct SegmentTree
{
	int n;
	int tree_size;
	vector<ll> range_multi;
	SegmentTree()
	{
		n = nums.size();
		int height = (int)ceil(log2(n));
		tree_size = (1 << (height + 1));
		range_multi.resize(tree_size);
		init(0, n - 1, 1);
	}

	ll init(int left, int right, int node)
	{
		if (left == right)
			return range_multi[node] = (ll)nums[left];
		int mid = (left + right) / 2;
		ll left_result = init(left, mid, node * 2);
		ll right_result = init(mid + 1, right, node * 2 + 1);
		return range_multi[node] = (left_result * right_result) % DENOMINATOR;
	}

	ll query(int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 1;
		if (left <= node_left && node_right <= right)
			return range_multi[node];
		int mid = (node_left + node_right) / 2;
		ll left_result = query(left, right, node * 2, node_left, mid);
		ll right_result = query(left, right, node * 2 + 1, mid + 1, node_right);
		return (left_result * right_result) % DENOMINATOR;
	}

	ll query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}

	ll update(int idx, int new_val, int node, int node_left, int node_right)
	{
		if (idx < node_left || node_right < idx)
			return range_multi[node];
		if (node_left == node_right)
			return range_multi[node] = (ll)new_val;
		int mid = (node_left + node_right) / 2;
		ll left_result = update(idx, new_val, node * 2, node_left, mid);
		ll right_result = update(idx, new_val, node * 2 + 1, mid + 1, node_right);
		return range_multi[node] = (left_result * right_result) % DENOMINATOR;
	}

	ll update(int idx, int new_val)
	{
		return update(idx, new_val, 1, 0, n - 1);
	}
};

void input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		int num;
		cin >> num;
		nums.push_back(num);
	}
}

void solve()
{
	SegmentTree st;
	for (int i = 0; i < M + K; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		switch (a)
		{
		case 1:
			st.update(b - 1, c);
			break;
		case 2:
			cout << st.query(b - 1, c - 1) << '\n';
			break;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	input();
	solve();
	return 0;
}