/*
	모의고사
	https://programmers.co.kr/learn/courses/30/lessons/42840

	수포자들이 찍는 패턴을 파악하고 가장 많은 문제를 맞힌 사람들을 찾는 문제다.

	수포자들의 패턴이 고정되어 있기 때문에 패턴의 기점과 종점으로 배열을 만들었다.
	그 후, answers와 수포자들의 답을 비교하여 cnt 배열에 수포자들의 점수를 매겼다.
*/
#include <string>
#include <vector>

using namespace std;

constexpr int one[] = { 1, 2, 3, 4, 5 };
constexpr int two[] = { 2, 1, 2, 3, 2, 4, 2, 5 };
constexpr int three[] = { 3, 3, 1, 1, 2, 2, 4, 4, 5, 5 };
constexpr auto one_size = 5;
constexpr auto two_size = 8;
constexpr auto three_size = 10;

void set_cnt(const vector<int>& answers, vector<int>& cnt)
{
	for (size_t i = 0; i < answers.size(); ++i)
	{
		if (answers[i] == one[i % one_size])
			++cnt[1];
		if (answers[i] == two[i % two_size])
			++cnt[2];
		if (answers[i] == three[i % three_size])
			++cnt[3];
	}
}

vector<int> solution(vector<int> answers)
{
	vector<int> answer;
	vector<int> cnt(4, 0);

	set_cnt(answers, cnt);
	int winner = 0;
	for (size_t i = 1; i <= 3; ++i)
		if (cnt[winner] < cnt[i])
			winner = i;
	for (size_t i = 1; i <= 3; ++i)
		if (cnt[winner] == cnt[i])
			answer.push_back(i);
	return answer;
}