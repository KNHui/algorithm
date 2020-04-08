/*
	전화번호 목록
	https://www.acmicpc.net/problem/5052

	다른 전화번호의 접두어가 되는 전화번호가 있는지 찾는 문제다.

	"트라이 자료구조"를 사용해서 풀었다.
	모든 전화번호를 트라이에서 찾고 삽입하면서 일관성이 있는지 확인했다.
	"bool find(char* key)" 함수에서 다음과 같은 과정으로 전화 번호의 일관성을 확인한다.

	1. 전화 번호의 마지막인 'NULL'까지 온 경우
		현재 전화번호가 다른 전화번호의 접두어이므로 'false' 반환
	2. 'terminal'이 참인 경우
		다른 전화번호가 현재 전화번호의 접두어이므로 'false' 반환
	3. 다음 노드가 'NULL'인 경우
		'true' 반환
	4. 다음 노드가 'NULL'이 아닌 경우
		다음 글자에 대해 1단계부터 다시 수행
*/
#include<iostream>

using namespace std;

constexpr int NUM_LEN = 10;

struct TrieNode
{
	bool		terminal;
	TrieNode*	children[NUM_LEN];

	TrieNode() : terminal(false)
	{
		for (int i = 0; i < NUM_LEN; ++i)
			children[i] = 0;
	}

	~TrieNode()
	{
		for (int i = 0; i < NUM_LEN; ++i)
			if (children[i]) delete children[i];
	}

	void insert(char* key)
	{
		if (*key == NULL)
		{
			terminal = true;
			return;
		}

		int next = *key - '0';

		if (children[next] == NULL)
			children[next] = new TrieNode();
		children[next]->insert(key + 1);		
	}

	bool find(char* key)
	{
		if (*key == NULL)
			return false;
		if (terminal)
			return false;

		int next = *key - '0';

		if (children[next] == nullptr)
			return true;
		return children[next]->find(key + 1);
	}
};

int			n;
string		ans;
TrieNode*	root;

void	init()
{
	cin >> n;
	ans = "YES";
	delete root;
	root = new TrieNode();
}

void	solve()
{
	char ip[11];

	init();
	for (int i = 0; i < n; ++i)
	{
		cin >> ip;
		if (ans == "YES")
		{
			if (root->find(ip))
				root->insert(ip);
			else
				ans = "NO";
		}
	}
}

int		main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int t;

	cin >> t;
	for (int tcn = 1; tcn <= t; ++tcn)
	{
		solve();
		cout << ans << '\n';
	}
	return 0;
}