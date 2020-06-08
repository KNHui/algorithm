/*
	Quantization
	https://www.algospot.com/judge/problem/read/QUANTIZE

	주어진 수열을 최대 S 개의 수로 양자화할 때, 오차 제곱의 합의 최솟값을 구하는 문제다.

	수열을 하나의 수로 양자화할 때, 오차 제곱의 합의 최솟값을 구하는 방법은 평균으로 양자화하는 것이다.
	평균으로 양자화하면 오차가 줄어들고, 오차 제곱 또한 줄어들기 때문이다.
	이때, 양자화된 숫자는 자연수이기 때문에 평균을 소수점 첫째 자리에서 반올림 해줘야 한다.

	오차 제곱의 합은 부분합과 부분 제곱합을 알면 시간 복잡도 O(1) 만에 알 수 있다.
	"부분합[idx]"와 "부분 제곱합[idx]"는 'nums' 수열의 구간 "[0, idx]"의 부분합과 부분 제곱합을 나타낸다.
	이때, 구간 "[A, B]"의 부분합은 "부분합[B] - 부분합[A - 1]"이고,
	부분 제곱합은 "부분 제곱합[B] - 부분 제곱합[A - 1]"이다.

	오차 "num - 평균"의 제곱은 "num^2 - 2 * 평균 * num + 평균^2"이 된다.
	위 식를 이용해 구간 "[A, B]"의 오차 제곱의 합을 구할 수 있다.
	'num^2'은 구간 "[A, B]"의 부분 제곱 합이 되고,
	'num'은 구간 "[A, B]"의 부분합이 되기 때문이다.
	'평균^2'에는 구간의 크기 "B - A + 1"을 곱해주면 된다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int INF = 987654321;
constexpr int MAX_N = 100 + 1;
constexpr int MAX_S = 10 + 1;

int			N, S;
int			prtl_sum[MAX_N];
int			prtl_sqr_sum[MAX_N];
int			cache[MAX_N][MAX_S];
vector<int>	nums;

void input(void)
{
	cin >> N >> S;
	nums.resize(N);
	for (int i = 0; i < N; ++i)
		cin >> nums[i];
}

void init(void)
{
	prtl_sum[0] = nums[0];
	prtl_sqr_sum[0] = nums[0] * nums[0];
	for (int i = 1; i < N; ++i)
	{
		prtl_sum[i] = prtl_sum[i - 1] + nums[i];
		prtl_sqr_sum[i] = prtl_sqr_sum[i - 1] + nums[i] * nums[i];
	}
	for (int i = 0; i < N + 1; ++i)
		fill(cache[i], cache[i] + S + 1, -1);
}

int		min_err(int start, int end)
{
	int sum = prtl_sum[end] - (start == 0 ? 0 : prtl_sum[start - 1]);
	int sqr_sum = prtl_sqr_sum[end] - (start == 0 ? 0 : prtl_sqr_sum[start - 1]);

	int aver = int((double)sum / (end - start + 1) + 0.5);
	return sqr_sum - (2 * aver * sum) + (aver * aver * (end - start + 1));
}


int		quantitize(int start, int parts)
{
	int& ret = cache[start][parts];
	if (ret != -1)
		return ret;
	if (start == N)
		return ret = 0;
	if (parts == 0)
		return ret = INF;

	ret = INF;
	for (int end = start; end < N; ++end)
		ret = min(ret, min_err(start, end) + quantitize(end + 1, parts - 1));
	return ret;
}

int		solve(void)
{
	sort(nums.begin(), nums.end());
	init();
	return quantitize(0, S);
}

int		main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;
	cin >> C;
	for (int tcn = 1; tcn <= C; ++tcn)
	{
		input();
		cout << solve() << '\n';
	}
	return 0;
}