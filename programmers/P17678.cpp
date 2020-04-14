/*
    [1��] ��Ʋ����
    https://programmers.co.kr/learn/courses/30/lessons/17678

    0.  Ǯ�� �� ����
            - �ԷµǴ� �ð��� ������ �ٲ㼭 �����ߴ�.
            - ũ����� �����ð��� ������������ �����ߴ�.
    1.  t �и��� ���� �ð�(now) ���Ͽ� ������ m ���� ũ����� ������ �¿���.
    2.  �������� ������ Ż ũ�簡 ������ �������� �ʰ� �����Ѵٸ�,
        ������ ������ ������ ���� �ð����� ���־���.
    3.  2���� ���� ������ ������ �ڸ��� ���� ��쿡��
        ������ ������ ������ ���� �ð��̴�.
    4.  ������ ������ �ڸ��� ���� �ʾ��� ����
        ������ ���������� ź ũ���� �ð� - 1���̴�.
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

// 0. n == 0 �� �� ������ ����
// 1. ������ ������ �ڸ��� ������ �� : ������ ���� ���� �ð�
// 2. ������ ������ �ڸ��� ���� �ʾ��� �� : ������ ���������� ä�� ũ�� -1 ��
void sovle(int n, int t, int m)
{
    int i = n;
    int now = 540 - t;
    int last = 0; // ���������� ź ũ���� ž�� �ð�
    size_t idx = 0;

    while (i--)
    {
        now += t;
        int spare = m; // ���� �¼�

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