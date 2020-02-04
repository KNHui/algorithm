/*
	[2020카카오공채] 가사 검색
	https://programmers.co.kr/learn/courses/30/lessons/60060

	입력된 가사 단어를 이용하여 일치하는 검색 키워드를 찾는 문제이기에,
	간단한 트라이 자료구조 문제인 줄 알았으나,
	'?' 때문에 모든 단어를 끝까지 찾게 되면 시간 초과로 효율성 테스트를 통과 못 한다.

	그래서 가사 단어를 입력할 때, 단어의 접두사를 공통으로 가지는 수를 cnt에 저장한다.
	검색 키워드를 트라이에서 찾을 때 '?'가 나온다면,
	생성된 children들의 cnt를 더해서 반환한다.

	그리고 서로 다른 길이를 가지면서, 같은 접두사를 가지는 가사 단어의 중복을 피하기위해
	Trie *root[]를 선언하고, 크기는 가사 단어의 최대 길이인 10000 + 1로 정했다.

	그리고 '?'는 검색 키워드의 앞 또는 뒤에서만 나타난다.
	'?'가 뒤에서 나오는 경우는 공통 접두사를 가지는 단어의 수를 찾으면 되는데,
	'?'가 앞에서 나오는 경우에는 공통 접미사를 가지는 단어의 수를 찾아야 한다.
	이를 위해서 가사 단어를 뒤집어서 입력받는 Trie *root[]를 선언했다.
*/
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

int to_num(char c)
{
	return (int)(c - 'a');
}

typedef struct Trie
{
	Trie *children[26];
	bool terminal;
	int cnt;

	Trie() : terminal(false), cnt(0)
	{
		for (int i = 0; i < 26; ++i)
			children[i] = 0;
	}

	~Trie()
	{
		for (int i = 0; i < 26; ++i)
			if (children[i])
				delete children[i];
	}

	void insert(const char *key)
	{
		if (!*key)
		{
			terminal = true;
			return;
		}

		int next = to_num(*key);
		if (!children[next])
			children[next] = new Trie();
		++(children[next]->cnt);
		children[next]->insert(key + 1);
	}

	int find(const char *key)
	{
		int ret = 0;
		if (*key == '?')
		{
			for (int next = 0; next < 26; ++next)
				if (children[next])
					ret += children[next]->cnt;
		}
		else
		{
			int next = to_num(*key);
			if (!children[next])
				return ret;
			else
				ret += children[next]->find(key + 1);
		}
		return ret;
	}
} Trie;

Trie *root[10001];
Trie *rev_root[10001];

vector<int> solution(vector<string> words, vector<string> queries)
{
	vector<int> answer;
	for (string word : words)
	{
		int size = word.size();

		if (!root[size])
			root[size] = new Trie();
		root[size]->insert(word.c_str());

		if (!rev_root[size])
			rev_root[size] = new Trie();
		reverse(word.begin(), word.end());
		rev_root[size]->insert(word.c_str());
	}
	for (string query : queries)
	{
		int cnt = 0;
		int size = query.size();

		if (query[size - 1] == '?')
		{
			if (root[size])
				cnt = root[size]->find(query.c_str());
		}
		else
		{
			if (rev_root[size])
			{
				reverse(query.begin(), query.end());
				cnt = rev_root[size]->find(query.c_str());
			}
		}

		answer.push_back(cnt);
	}
	return answer;
}