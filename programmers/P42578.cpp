/*
    ����
    https://programmers.co.kr/learn/courses/30/lessons/42578

    ���� ���� �� �ִ� ������ ���� ���ϴ� �����̴�.

    DFS �˰����� ����ϸ� ���� �� ������, �ð��� ���� �ɸ��� ������ ������� �� �Ѵ�.
    �׷��� ����� ���� ����Ͽ� Ǯ��� �Ѵ�.
    
    �ǻ��� ���� ���� ���� �� �ִ� ����� ����
    '���� �� �ִ� ���� �ٸ� �ǻ��� �� + �ƹ� �͵� �� �Դ� ����� ��'�ε�
    �� ���� ���� ������ �ִ� ����� ���� ��� �����ָ� ��� ������ ���� ���� �� �ִ�.
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