/*
	[2020카카오공채] 가사 검색
	https://programmers.co.kr/learn/courses/30/lessons/60060

	입력된 가사 단어를 이용하여 일치하는 검색 키워드를 찾는 문제다.

	가사 단어를 트라이에 입력할 때, 공통 접두사의 수를 'int cnt'에 저장한다.
	검색 키워드를 트라이에서 찾을 때 '?'가 나온다면, 자식 노드의 'cnt' 합을 반환한다.

	서로 다른 길이를 가지면서, 같은 접두사를 가지는 가사 단어가 있을 수 있다.
	그래서 단어 길이마다 다른 트라이에 저장했다.

	'?'는 검색 키워드의 앞 또는 뒤에서만 나타난다.
	'?'가 앞에서 나타나면 가사 단어를 뒤집어서 공통 접미사를 찾도록 했다.
	1. '?'가 뒤에서 나오는 경우
		1) '?'를 제외한 키워드를 공통 접두사로 가지는 단어의 수 반환
	2. '?'가 앞에서 나오는 경우
		1) '?'를 제외한 키워드를 공통 접미사로 가지는 단어의 수 반환
*/
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int to_num(char c)
{
	return (int)(c - 'a');
}

typedef struct Trie
{
	int		cnt;
	bool	terminal;
	Trie	*children[26];

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