/*
    �޴��� ����
    https://www.acmicpc.net/problem/5670

	[�Է�]
	�Է��� �޴� �׽�Ʈ ���̽��� ���� �־����� �����Ƿ�, while (cin >> N) {}�� ����
	�Է��� �����ߴٸ� ����ؼ� �׽�Ʈ ���̽��� �����Ѵ�.

	[Ǯ��]
	Ʈ������ ��忡 isSolo�� �ְ� �ش� ����� �ڽ��� �ϳ�(true)���� ����(false)���� ǥ���Ѵ�.
	Ÿ���� ���� ����ϴ� type �Լ����� isSolo�� true��� Ÿ���� ���� ������Ű�� �ʰ�
	��͸� �����Ѵ�.

	Ʈ���̿� �Է��� ��, ���� ����� �ڽ� ��� �߿� ���� ����(*key)�� ��� �ܿ�
	�ٸ� ��尡 NULL�� �ƴ϶��, �ٸ� ���ڷ� Ʈ���̰� �������ٴ� ���̹Ƿ�
	isSolo�� false�� ������ش�.

	[���]
	������ ����� ���� "cout << fixed;"�� "cout.precision(2);"�� ����Ͽ�
	�Ҽ� ���� ������Ű�� �� °�ڸ� ���� �ݿø��Ͽ� ����Ѵ�.

*/
#include <iostream>

using namespace std;

constexpr auto ALPHABET = 26;

int getLength(char *src)
{
	int len = 0;
	for (int i = 0; i < 81; ++i)
	{
		if (src[i] == 0)
			return len;
		++len;
	}
	return len;
}
struct TrieNode
{
	TrieNode *children[ALPHABET];
	bool terminal;
	bool isSolo; // �� ��� ���� �ܾ 1�� ���ΰ�

	TrieNode() : terminal(false), isSolo(true)
	{
		for (int i = 0; i < ALPHABET; ++i)
		{
			children[i] = 0;
		}
	}

	~TrieNode()
	{
		for (int i = 0; i < ALPHABET; ++i)
		{
			if (children[i])
				delete children[i];
		}
	}

	void insert(char *key)
	{
		if (*key == 0)
		{
			terminal = true;
		}
		else
		{
			int next = *key - 'a';

			for (int i = 0; i < 26; ++i)
			{
				if (children[i] != NULL)
				{
					if (i != next)
					{
						isSolo = false;
					}
				}
			}

			if (children[next] == NULL)
			{
				children[next] = new TrieNode();
			}
			children[next]->insert(key + 1);
		}
	}

	int type(char *key)
	{
		if (*key == 0)
			return 0;

		int next = *key - 'a';
		if (isSolo && !terminal)
			return children[next]->type(key + 1);
		else
			return 1 + children[next]->type(key + 1);
	}
};

int N;
char ip[100001][81];

double ans;
TrieNode *root;

void input()
{
	for (int i = 0; i < N; ++i)
	{
		cin >> ip[i];
		root->insert(ip[i]);
	}
	root->isSolo = false;
}

void solve()
{
	int result;
	for (int i = 0; i < N; ++i)
	{
		result = root->type(ip[i]);
		ans += result;
	}
	ans /= N;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	while (cin >> N)
	{
		ans = 0;
		delete root;
		root = new TrieNode();

		input();
		solve();

		cout << fixed;
		cout.precision(2);
		cout << ans << '\n';
	}

	return 0;
}