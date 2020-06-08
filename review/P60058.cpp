/*
	[2020카카오공채] 괄호 변환
	https://programmers.co.kr/learn/courses/30/lessons/60058

	 "균형 잡힌 괄호 문자열"을 "올바른 괄호 문자열"로 변환하는 문제다.

	 변환하는 과정은 재귀적으로 1단계를 다시 수행한다.
	 1단계부터 시작하여 2, 3, 4단계를 수행하는 재귀 함수 "void first_step(string &p)"을 만들었다.
	 이때, 1단계가 기저 조건이 되어 무한 반복을 방지한다.
*/
#include <string>
#include <vector>

using namespace std;

void set_opposite_direction(string &str)
{
	int idx = -1;

	while (str[++idx])
	{
		if (str[idx] == '(')
			str[idx] = ')';
		else if (str[idx] == ')')
			str[idx] = '(';
	}
}
bool split(string &u, string &v, const string &p)
{
	int left = 0;
	int right = 0;
	bool proper = true;

	for (size_t idx = 0; p[idx]; ++idx)
	{
		if (p[idx] == '(')
			++left;
		if (p[idx] == ')')
			++right;
		if (right > left)
			proper = false;
		u += p[idx];
		if (left == right)
		{
			v = p.substr(idx + 1, string::npos);
			break;
		}
	}
	return proper;
}

void first_step(string &p)
{
	if (p.empty())
		return;
	string u = "";
	string v = "";

	if (split(u, v, p))
	{
		first_step(v);
		p = u + v;
	}
	else
	{
		first_step(v);
		p = "(" + v + ")";
		u = u.substr(1, u.length() - 2);
		set_opposite_direction(u);
		p += u;
	}
}

string solution(string p)
{
	string answer = "";

	first_step(p);
	answer = p;
	return answer;
}