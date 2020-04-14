/*
   ���� �� ���ϱ�
   https://www.acmicpc.net/problem/2042

   ���׸�Ʈ Ʈ���� ����Ͽ� ������ ���� ���� ã�ų� �����ϴ� �����̴�.

   ���� ���� int ������ �Ѿ �� �ֱ� ������ ���� ���� �����ϴ� ���� range_sum�� Ÿ���� long long���� �����Ѵ�.

   �� �ϳ��� �����ϴ� update �Լ��� ���� �յ� ��������� �ϹǷ�
   idx�� ���� ����� ���� [node_left, node_right]�� �����, ���� �� range_sum[node]�� �����Ѵ�.
   idx�� ���� ������ �� ��쿡�� range_sum[node]�� ���ο� ������ ���� �� �����Ѵ�.
   
   ���� ���� ã�� query �Լ��� left�� right�� ���ԵǴ� ������ ���� ���ؾ��ϹǷ�,
   left�� right�� ���� ����� ���� [node_left, node_right]�� �����, 0�� �����Ѵ�.
   left�� right�� ���� ����� ���� [node_left, node_right]�� ���ԵǸ�, range_sum[node]�� �����Ѵ�.
*/
#include <vector>
#include <iostream>

using namespace std;

enum Command
{
	ZERO,
	CHANGE,
	PRINT
};

struct SegmentTree
{
	int n;
	vector<long long> range_sum;
	SegmentTree(const vector<long long> &arr)
	{
		n = arr.size();
		range_sum.resize(n * 4);
		init(arr, 0, n - 1, 1);
	}

	long long init(const vector<long long> &arr, int left, int right, int node)
	{
		if (left == right)
			return range_sum[node] = arr[left];
		int mid = (left + right) / 2;
		long long left_sum = init(arr, left, mid, node * 2);
		long long right_sum = init(arr, mid + 1, right, node * 2 + 1);
		return range_sum[node] = left_sum + right_sum;
	}

	long long query(int left, int right, int node, int node_left, int node_right)
	{
		if (right < node_left || node_right < left)
			return 0;
		if (left <= node_left && node_right <= right)
			return range_sum[node];
		int mid = (node_left + node_right) / 2;
		return query(left, right, node * 2, node_left, mid) + query(left, right, node * 2 + 1, mid + 1, node_right);
	}

	long long query(int left, int right)
	{
		return query(left, right, 1, 0, n - 1);
	}

	long long update(int idx, long long new_val, int node, int node_left, int node_right)
	{
		if (idx < node_left || node_right < idx)
			return range_sum[node];
		if (node_left == node_right)
			return range_sum[node] = new_val;
		int mid = (node_left + node_right) / 2;
		return range_sum[node] = update(idx, new_val, node * 2, node_left, mid) + update(idx, new_val, node * 2 + 1, mid + 1, node_right);
	}

	long long update(int idx, long long new_val)
	{
		return update(idx, new_val, 1, 0, n - 1);
	}
};

int N, M, K;

vector<long long> nums;

void init()
{
	cin >> N >> M >> K;
	int num;
	for (int i = 0; i < N; ++i)
	{
		cin >> num;
		nums.push_back(num);
	}
}

void solve()
{
	int a, b;
	long long c;
	SegmentTree st(nums);
	for (int i = 0; i < M + K; ++i)
	{
		cin >> a >> b >> c;
		switch (a)
		{
		case CHANGE:
			st.update(b - 1, c);
			break;
		case PRINT:
			cout << st.query(b - 1, c - 1) << '\n';
			break;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();

	return 0;
}