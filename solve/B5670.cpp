/*
	휴대폰 자판
	https://www.acmicpc.net/problem/5670

	[입력]
	입력을 받는 테스트 케이스의 수가 주어지지 않으므로, while (cin >> N) {}을 통해
	입력이 성공했다면 계속해서 테스트 케이스를 진행한다.

	[풀이]
	트라이의 노드에 isSolo를 넣고 해당 노드의 자식이 하나(true)인지 여럿(false)인지 표시한다.
	타이핑 수를 계산하는 type 함수에서 isSolo가 true라면 타이핑 수를 증가시키지 않고
	재귀를 진행한다.

	트라이에 입력할 때, 현재 노드의 자식 노드 중에 현재 글자(*key)의 노드 외에
	다른 노드가 NULL이 아니라면, 다른 글자로 트라이가 갈라진다는 뜻이므로
	isSolo를 false로 만들어준다.

	[출력]
	정답을 출력할 때는 "cout << fixed;"와 "cout.precision(2);"를 사용하여
	소수 점을 고정시키고 둘 째자리 까지 반올림하여 출력한다.
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