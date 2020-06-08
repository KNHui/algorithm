/*
	Wildcard
	https://algospot.com/judge/problem/read/WILDCARD

	와일드카드에 매치되는 파일 이름을 구하는 문제다.

	"외발 뛰기" 문제처럼 "메모이제이션"을 사용했다.
	(https://github.com/KNHui/algorithm/blob/master/ALGOSPOT/JUMPGAME.cpp)

	함수 "int match(int w, int fn, int idx)"는 와일드카드와 파일 이름이 매치되는지 확인한다.
	한 테스트 케이스에서 파일 이름은 여러개가 나올 수 있기 때문에 idx로 몇 번째 파일 이름인지 표시했다.
	- w		: 와일드카드 문자열의 시작 위치
	- fn	: 파일 이름 문자열의 시작 위치
	- idx	: 파일 이름의 인덱스

	1. 와일드카드의 문자가 '?'이거나 와일드 카드의 문자가 같은 경우
		1) 두 문자열의 다음 글자가 매치되는지 확인한다.
	2. 와일드카드를 끝까지 탐색한 경우
		1) 파일 이름도 끝까지 탐색했다면, 와일드카드와 파일 이름은 매치된다.
		2) 그렇지 않다면, 와일드카드와 파일 이름은 매치되지 않는다.
	3. 와일드카드의 문자가 '*'인 경우
		1) '*'와 파일 이름의 문자를 0 글자부터 최대 글자까지 대응시켜본다.
*/
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

constexpr int MAX = 100 + 1;

int				N;
int				cache[MAX][MAX];
string			W;
vector<string>	answer;
vector<string>	file_name;

void input(void)
{
	cin >> W;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		string ip;

		cin >> ip;
		file_name.push_back(ip);
	}
}

int match(int w, int fn, int idx)
{
	if (cache[w][fn] != -1)
		return cache[w][fn];
	if (w < W.size() && fn < file_name[idx].size() &&
		(W[w] == '?' || W[w] == file_name[idx][fn]))
		return cache[w][fn] = match(w + 1, fn + 1, idx);
	if (w == W.size())
		return cache[w][fn] = (fn == file_name[idx].size());
	if (W[w] == '*')
		if (match(w + 1, fn, idx) || (fn < file_name[idx].size() && match(w, fn + 1, idx)))
			return cache[w][fn] = 1;
	return cache[w][fn] = 0;
}

void solve(void) 
{
	for (size_t i = 0; i < file_name.size(); i++)
	{
		for (size_t j = 0; j < W.size() + 1; ++j)
			fill(cache[j], cache[j] + file_name[i].size() + 1, -1);
		if (match(0, 0, i))
			answer.push_back(file_name[i]);
	}
	sort(answer.begin(), answer.end());
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int C;

	cin >> C;
	for (int tcn = 1; tcn <= C; ++tcn)
	{
		input();
		solve();
		for (size_t i = 0; i < answer.size(); i++)
			cout << answer[i] << '\n';
		answer.clear();
		file_name.clear();
	}
	return 0;
}