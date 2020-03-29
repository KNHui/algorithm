/*
	H-Index
	https://programmers.co.kr/learn/courses/30/lessons/42747
	
	citations을 오름차순으로 정렬하고, 	citations을 앞에서부터 순회하면서
	citations[i]가 answer보다 작으면 H 기준 미달이므로 answer를 줄이고 탐색을 계속하고,
	citations[i]가 answer보다 크면 H 기준 충족이므로 answer를 리턴한다.
*/
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations)
{
	int answer = citations.size();

	sort(citations.begin(), citations.end());
	for (size_t i = 0; i < citations.size(); ++i)
		if (citations[i] >= answer)
			break;
		else
			--answer;
	return answer;
}