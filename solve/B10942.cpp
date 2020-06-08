#include <cstring>
#include <iostream>

using namespace std;

constexpr int MAX_N = 2000 + 1;
constexpr int MAX_M = 1000000 + 1;

int N, M;
int nums[MAX_N];
int cache[MAX_N][MAX_N];
pair<int, int> questions[MAX_M];

void init(void)
{
	cin >> N;
	for (int i = 1; i <= N; ++i)
		cin >> nums[i];
	cin >> M;
	for (int i = 0; i < M; ++i)
		cin >> questions[i].first >> questions[i].second;
	memset(cache, -1, sizeof(cache));
}

int is_palindrome(int start, int end)
{
	int &ret = cache[start][end];
	if (ret != -1)
		return ret;

	if (start == end)
		return ret = 1;
	if (nums[start] != nums[end])
		return ret = 0;
	if (start + 1 == end)
		return ret = 1;
	return ret = is_palindrome(start + 1, end - 1);
}

void solve(void)
{
	for (int i = 0; i < M; i++)
		cout << is_palindrome(questions[i].first, questions[i].second) << '\n';
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	init();
	solve();
	return 0;
}