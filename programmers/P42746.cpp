/*
    가장 큰 수
    https://programmers.co.kr/learn/courses/30/lessons/42746

    처음에는 주어진 수열에서 가장 큰 자릿수에 맞춰서 수를 조정하였는데,
    {121, 12}가 주어질 경우, {121, 121}로 조정하여서 "12121"이 아닌 "12112"를 리턴하였다.

    그래서 numbers 요소의 최대 자릿수인 4자리에 맞춰서 수들을 조정하였고,
    조정된 수들에 -1을 곱하고 인덱스와 함께 저장하였다.
    그리고 오름차순으로 정렬하여 절댓값이 큰 순서대로 answer에 담기도록 하였다.
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

    // numbers의 수들을 4 자릿수로 맞춤
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