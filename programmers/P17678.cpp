/*
	[1차] 셔틀버스
	https://programmers.co.kr/learn/courses/30/lessons/17678

	0.  풀이 전 세팅
			- 입력되는 시간을 분으로 바꿔서 저장했다.
			- 크루들의 도착시간을 오름차순으로 정렬했다.
	1.  t 분마다 현재 시각(now) 이하에 도착한 m 명의 크루들을 버스에 태운다.
		1)  마지막 버스의 자리가 남는 경우
			a. 정답은 마지막 버스의 도착 시간이다.
		2)  마지막 버스의 자리가 남지 않는 경우
			a. 정답은 마지막으로 탄 크루의 시간 - 1분이다.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int toNum(string &t)
{
	int hour = (t[0] - '0') * 10 + t[1] - '0';
	int minute = (t[3] - '0') * 10 + t[4] - '0';
	return hour * 60 + minute;
}

string toTime(int num)
{
	string hour, minute;
	string share = to_string(num / 60);
	string remainder = to_string(num % 60);

	if (num >= 600)
		hour = share;
	else
		hour = "0" + share;

	if (num % 60 >= 10)
		minute = remainder;
	else
		minute = "0" + remainder;

	return hour + ":" + minute;
}

string sovle(int n, int t, int m, vector<int> &numTable)
{
	int		i = n;
	int		now = 540 - t;
	int		last_boarding_time = 0;
	size_t	idx = 0;
	string	answer = "";

	while (i--)
	{
		int vacancy = m;
		now += t;

		if (numTable[idx] > now + i * t)
		{
			answer = toTime(540 + (n - 1) * t);
			return;
		}
		for (; idx < numTable.size(); ++idx)
		{
			if (numTable[idx] <= now && vacancy > 0)
			{
				--vacancy;
				last_boarding_time = numTable[idx];
			}
			else
				break;
		}
		if (i == 0)
		{
			if (vacancy > 0)
				answer = toTime(540 + (n - 1) * t);
			else
				answer = toTime(last_boarding_time - 1);
		}
	}
	return answer;
}

string solution(int n, int t, int m, vector<string> timetable)
{

	for (size_t i = 0; i < timetable.size(); ++i)
		numTable.push_back(toNum(timetable[i]));
	sort(numTable.begin(), numTable.end());
	return sovle(n, t, m, numTable);
}