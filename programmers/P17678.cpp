/*
    [1차] 셔틀버스
    https://programmers.co.kr/learn/courses/30/lessons/17678

    0.  풀이 전 세팅
            - 입력되는 시간을 분으로 바꿔서 저장했다.
            - 크루들의 도착시간을 오름차순으로 정렬했다.
    1.  t 분마다 현재 시각(now) 이하에 도착한 m 명의 크루들을 버스에 태웠다.
    2.  다음으로 버스에 탈 크루가 마지막 버스보다 늦게 도착한다면,
        정답을 마지막 버스의 도착 시간으로 해주었다.
    3.  2번과 같이 마지막 버스가 자리가 남는 경우에는
        정답은 마지막 버스의 도착 시간이다.
    4.  마지막 버스의 자리가 남지 않았을 때는
        정답은 마지막으로 탄 크루의 시간 - 1분이다.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> numTable;
string answer = "";

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

// 0. n == 0 일 때 마지막 버스
// 1. 마지막 버스가 자리가 남았을 때 : 마지막 버스 도착 시간
// 2. 마지막 버스가 자리가 남지 않았을 때 : 버스에 마지막으로 채운 크루 -1 분
void sovle(int n, int t, int m)
{
    int i = n;
    int now = 540 - t;
    int last = 0; // 마지막으로 탄 크루의 탑승 시각
    size_t idx = 0;

    while (i--)
    {
        now += t;
        int spare = m; // 남은 좌석

        if (numTable[idx] > now + i * t)
        {
            answer = toTime(540 + (n - 1) * t);
            return;
        }

        for (; idx < numTable.size(); ++idx)
        {
            if (numTable[idx] <= now && spare > 0)
            {
                --spare;
                last = numTable[idx];
            }
            else
            {
                break;
            }
        }

        if (i == 0)
        {
            if (spare > 0)
            {
                answer = toTime(540 + (n - 1) * t);
            }
            else
            {
                answer = toTime(last - 1);
            }
        }
    }
}

string solution(int n, int t, int m, vector<string> timetable)
{

    for (size_t i = 0; i < timetable.size(); ++i)
    {
        numTable.push_back(toNum(timetable[i]));
    }
    sort(numTable.begin(), numTable.end());

    sovle(n, t, m);

    return answer;
}