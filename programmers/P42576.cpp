/*
	완주하지 못한 선수
	https://programmers.co.kr/learn/courses/30/lessons/42576

	-	트라이노드에 완주한 사람들을 입력하고, 참가자 중에서 트라이노드에서
		못 찾은 참가자는 완주하지 못한 참가자이다.
	-	동명이인이 있을 수 있기 때문에 완주한 사람들을 입력할 때 이름의 마지막 글자라면
		cnt 값을 1 증가시켜서 해당 이름을 가진 사람의 수를 표시했다.
    -   트라이노드에서 참가자들을 찾을 때, 해당 이름의 cnt 값이 1 이상일 때만
		true를 리턴하고 해당 이름의 cnt를 1 감소시켰다.
		리턴 값이 false인 이름은 완주하지 못한 참가자이기 때문에 해당 이름을 answer에 대입한다.
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
	TrieNode *children[26];
	int cnt;

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
		else
		{
			int next = toNum(*key);
			if (children[next] == NULL)
				children[next] = new TrieNode();
			children[next]->insert(key + 1);
		}
	}

	bool find(const char *key)
	{
		if (*key == 0)
		{
			if (cnt > 0)
			{
				--cnt;
				return true;
			}
			else
				return false;
		}

		int next = toNum(*key);
		if (children[next] == 0)
			return false; // 여기에는 올 일 없을 듯
		return children[next]->find(key + 1);
	}
};

string solution(vector<string> participant, vector<string> completion)
{
	string answer = "";
	TrieNode *root = new TrieNode();
	for (size_t i = 0; i < completion.size(); ++i)
	{
		root->insert(completion[i].c_str());
	}

	for (size_t i = 0; i < participant.size(); ++i)
	{
		if (root->find(participant[i].c_str()))
		{
		}
		else
		{
			answer = participant[i];
		}
	}
	return answer;
}