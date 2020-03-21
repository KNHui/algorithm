/*
	위장
	https://programmers.co.kr/learn/courses/30/lessons/42578

	옷을 입는 경우의 수를 구하는 문제이다.

 	각 종류 별로 가지고 있는 의상의 수를 모두 곱해주면 정답을 구할 수 있다.
	이때, 공집합을 포함하기 위해 "의상의 수 + 1"을 곱해준다.
*/
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes)
{
	int answer = 1;
	unordered_map<string, int> clothes_hash;

	for (size_t i = 0; i < clothes.size(); ++i)
		++clothes_hash[clothes[i][1]];
	for (auto iter = clothes_hash.begin(); iter != clothes_hash.end(); ++iter)
		answer *= iter->second + 1;
	return answer - 1;
}