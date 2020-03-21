/*
	완주하지 못한 선수
	https://programmers.co.kr/learn/courses/30/lessons/42576

	트라이노드에 완주자를 입력한다.
	트라이노드에 없는 참가자는 미완주자다.	
	동명이인을 처리하기 위해 'int cnt'로 해당 이름을 가진 사람의 수를 표시했다.
	완주자을 입력할 때 'NULL'에 도착하면, 'cnt'를 1 증가시켰다. 
	
	트라이노드에서 참가자가 완주자인지 확인하는 것은 다음과 같다.
	1. 이름의 'cnt'가 0 초과인 경우
		1) 해당 이름의 'cnt' 1 감소
		2) 완주자이므로 'true'를 리턴
	2. 이름의 'cnt'가 0 이하인 경우
		1) 미완주자이므로 'false'를 리턴
*/
#include <string>
#include <vector>

using namespace std;

int toNum(char next)
{
	return next - 'a';
}

struct TrieNode
{
	int cnt;
	TrieNode *children[26];

	TrieNode() : cnt(0)
	{
		for (int i = 0; i < 26; ++i)
		{
			children[i] = 0;
		}
	}

	void insert(const char *key)
	{
		if (*key == 0)
		{
			++cnt;
			return;
		}

		int next = toNum(*key);
		if (children[next] == NULL)
			children[next] = new TrieNode();
		children[next]->insert(key + 1);
	}

	bool find(const char *key)
	{
		if (*key == 0)
		{
			if (cnt-- > 0)
				return true;
			else
				return false;
		}

		int next = toNum(*key);
		if (children[next] == 0)
			return false;
		return children[next]->find(key + 1);
	}
};

string solution(vector<string> participant, vector<string> completion)
{
	string answer = "";
	TrieNode *root = new TrieNode();

	for (size_t i = 0; i < completion.size(); ++i)
		root->insert(completion[i].c_str());

	for (size_t i = 0; i < participant.size(); ++i)
	{
		if (!root->find(participant[i].c_str()))
		{
			answer = participant[i];
			break;
		}
	}
	return answer;
}