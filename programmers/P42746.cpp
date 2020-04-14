/*
    ���� ū ��
    https://programmers.co.kr/learn/courses/30/lessons/42746

    ó������ �־��� �������� ���� ū �ڸ����� ���缭 ���� �����Ͽ��µ�,
    {121, 12}�� �־��� ���, {121, 121}�� �����Ͽ��� "12121"�� �ƴ� "12112"�� �����Ͽ���.

    �׷��� numbers ����� �ִ� �ڸ����� 4�ڸ��� ���缭 ������ �����Ͽ���,
    ������ ���鿡 -1�� ���ϰ� �ε����� �Բ� �����Ͽ���.
    �׸��� ������������ �����Ͽ� ������ ū ������� answer�� ��⵵�� �Ͽ���.
*/

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int getDigit(int number)
{
    int digit = 0;

    while (number > 0)
    {
        number /= 10;
        ++digit;
    }
    return digit;
}

string solution(vector<int> numbers)
{
    string answer = "";
    vector<int> digits;
    vector<pair<int, int>> newNumbers;

    for (size_t i = 0; i < numbers.size(); ++i)
    {
        int digit = getDigit(numbers[i]);
        digits.push_back(digit);
    }

    // numbers�� ������ 4 �ڸ����� ����
    for (size_t i = 0; i < numbers.size(); ++i)
    {
        string temp = to_string(numbers[i]);
        for (int j = 0; 4 - digits[i] > 0; ++j)
        {
            temp += temp[j];
            ++digits[i];
        }
        newNumbers.push_back({atoi(temp.c_str()) * -1, i});
    }

    sort(newNumbers.begin(), newNumbers.end());
    for (size_t i = 0; i < newNumbers.size(); ++i)
        answer += to_string(numbers[newNumbers[i].second]);

    if (atoi(answer.c_str()) == 0)
        answer = "0";
    return answer;
}