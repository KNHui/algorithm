/*
    위장
    https://programmers.co.kr/learn/courses/30/lessons/42578

    옷을 입을 수 있는 조합의 수를 구하는 문제이다.

    DFS 알고리즘을 사용하면 구할 수 있으나, 시간이 오래 걸리기 때문에 통과하지 못 한다.
    그래서 경우의 수를 계산하여 풀어야 한다.
    
    의상의 종류 마다 입을 수 있는 경우의 수는
    '입을 수 있는 서로 다른 의상의 수 + 아무 것도 안 입는 경우의 수'인데
    각 종류 별로 가지고 있는 경우의 수를 모두 곱해주면 모든 조합의 수를 구할 수 있다.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<vector<string>> clothes)
{
    int answer = 1;
    unordered_map<string, int> clothes_hash;

    for (size_t i = 0; i < clothes.size(); ++i)
    {
        ++clothes_hash[clothes[i][1]];
    }

    for (auto iter = clothes_hash.begin(); iter != clothes_hash.end(); ++iter)
    {
        answer *= iter->second + 1;
    }

    return answer - 1;
}