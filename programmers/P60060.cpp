/*
	[2020īī����ä] ���� �˻�
	https://programmers.co.kr/learn/courses/30/lessons/60060

	�Էµ� ���� �ܾ �̿��Ͽ� ��ġ�ϴ� �˻� Ű���带 ã�� �����̱⿡,
	������ Ʈ���� �ڷᱸ�� ������ �� �˾�����,
	'?' ������ ��� �ܾ ������ ã�� �Ǹ� �ð� �ʰ��� ȿ���� �׽�Ʈ�� ��� �� �Ѵ�.

	�׷��� ���� �ܾ �Է��� ��, �ܾ��� ���λ縦 �������� ������ ���� cnt�� �����Ѵ�.
	�˻� Ű���带 Ʈ���̿��� ã�� �� '?'�� ���´ٸ�,
	������ children���� cnt�� ���ؼ� ��ȯ�Ѵ�.

	�׸��� ���� �ٸ� ���̸� �����鼭, ���� ���λ縦 ������ ���� �ܾ��� �ߺ��� ���ϱ�����
	Trie *root[]�� �����ϰ�, ũ��� ���� �ܾ��� �ִ� ������ 10000 + 1�� ���ߴ�.

	�׸��� '?'�� �˻� Ű������ �� �Ǵ� �ڿ����� ��Ÿ����.
	'?'�� �ڿ��� ������ ���� ���� ���λ縦 ������ �ܾ��� ���� ã���� �Ǵµ�,
	'?'�� �տ��� ������ ��쿡�� ���� ���̻縦 ������ �ܾ��� ���� ã�ƾ� �Ѵ�.
	�̸� ���ؼ� ���� �ܾ ����� �Է¹޴� Trie *root[]�� �����ߴ�.
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