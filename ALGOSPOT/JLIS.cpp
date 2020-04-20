/*
	합친 LIS
	https://www.algospot.com/judge/problem/read/JLIS

	주어진 두 수열의 'JLIS'를 구하는 문제다.

	'LIS' 문제 해법을 변형해서 풀었다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/LIS.cpp)

	"int jlis(int idx_a, int idx_b)" 함수는 "A [idx_a, n)"과 "B [idx_b, m)"의 'JLIS' 길이를 반환한다.
	"jlis(-1, -1)"와 같이 한 번의 호출로 'JLIS'의 길이를 구할 수 있다.
	시작 인덱스가 '-1'로 넘어갔기 때문에 '-1'보다 큰 인덱스들을 모두 시도해보기 때문이다.
	생성된 부분 수열의 맨 뒤에 있는 값보다 큰 수를 부분 수열에 넣어보면서 'JLIS'의 길이를 구한다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX = 100 + 1;

int				n, m;
int				cache[MAX][MAX];
vector<int>		A, B;

void init(void)
{
	cin >> n;
	cin >> m;
	A.resize(n);
	B.resize(m);
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	for (int i = 0; i < m; ++i)
		cin >> B[i];
	for (int i = 0; i < MAX; ++i)
		fill(cache[i], cache[i] + MAX, -1);
}

int	jlis(int idx_a, int idx_b)
{
	int& ret = cache[idx_a + 1][idx_b + 1];
	if (ret != -1)
		return ret;

	long long a = (idx_a == -1 ? numeric_limits<long long>::min() : A[idx_a]);
	long long b = (idx_b == -1 ? numeric_limits<long long>::min() : B[idx_b]);
	long long max_ele = max(a, b);
	ret = 2;
	for (int next_a = idx_a + 1; next_a < n; ++next_a)
		if (max_ele < A[next_a])
			ret = max(ret, jlis(next_a, idx_b) + 1);
	for (int next_b = idx_b + 1; next_b < m; ++next_b)
		if (max_ele < B[next_b])
			ret = max(ret, jlis(idx_a, next_b) + 1);
	return ret;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int c;

	cin >> c;
	for (int tcn = 1; tcn <= c; ++tcn)
	{
		init();
		cout << jlis(-1, -1) - 2 << '\n';
	}
	return 0;
}