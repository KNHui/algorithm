/*
	�ȳ���, �׸��� ������ �������!
	https://www.algospot.com/judge/problem/read/SOLONG#

	Ʈ���� �˰����� ����Ͽ�, ������ ����� �ܾ���� �����ϰ�, �Է��ؾ� �ϴ� Ƚ���� ���Ѵ�.

	������ ����� �ܾ���� �Է¹ް� ����, ���� �� ������������ �����ϰ�, ���� �󵵰� ���ٸ� ���� ������ �����Ѵ�.
	���� �Ŀ� Ʈ���̿� �ܾ���� �����ϴµ�,
	�� ����� first���� �ش� ��忡�� �� Ű�� ������ �ϼ��Ǵ� �ܾ��� �ε����� ����,
	terminal���� �ش� ��忡�� ���� �ܾ��� �ε����� ����.

	Ÿ�����ؾ� �ϴ� ���ڿ��� �� �ܾ Ʈ���̿� ���ٸ� �ܾ��� ���̸� answer�� ���ϰ�,
	Ʈ���̿� �ִٸ�, type �Լ��� ����Ͽ� �ּ� Ÿ���� ���� ���Ѵ�.
	type �Լ������� ���� ��忡�� first�� �ε����� �ڽ��� �ε������
	�� Ű�� ������ �ڵ��ϼ��� �ǹǷ�, 1�� �����Ѵ�
	�׷��� �ʴٸ� ���� ������ ���� �Ѿ�鼭 ���� �ϳ��� Ÿ�����ؾ� �ϹǷ� �ᱣ���� 1�� �����ش�.
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int toNum(char ch)
{
    return ch - 'A';
}

typedef struct TrieNode
{
    TrieNode *child[26];
    int first;
    int terminal;

    TrieNode() : first(-1), terminal(-1)
    {
        memset(child, 0, sizeof(child));
    }

    ~TrieNode()
    {
        for (int i = 0; i < 26; ++i)
        {
            if (child[i])
            {
                delete child[i];
            }
        }
    }

    void insert(const char *key, const int idx)
    {
        if (first == -1)
        {
            first = idx;
        }

        if (*key == 0)
        {
            terminal = idx;
        }
        else
        {
            int next = toNum(*key);
            if (child[next] == NULL)
            {
                child[next] = new TrieNode();
            }
            child[next]->insert(key + 1, idx);
        }
    }

    TrieNode *find(const char *key)
    {
        if (*key == 0)
        {
            return this;
        }

        int next = toNum(*key);
        if (child[next] == NULL)
        {
            return NULL;
        }
        else
        {
            return child[next]->find(key + 1);
        }
    }

    // �ش� ��忡�� idx�� �ܾ ġ������ �� �� �� Ÿ���� �ؾ��ϴ°�
    int type(const char *key, int idx)
    {
        if (*key == 0)
        {
            return 0;
        }

        if (first == idx)
        {
            return 1;
        }

        int next = toNum(*key);
        return 1 + child[next]->type(key + 1, idx);
    }
} tn;

int C, N, M;

int solve()
{
    int weight;
    char ip[11];

    int answer;
    vector<pair<int, string>> dict;
    tn root;

    answer = M - 1; // �����̽���
    for (int i = 0; i < N; ++i)
    {
        cin >> ip >> weight;
        dict.push_back(make_pair(-weight, ip));
    }

    // ���� �� Ʈ���� ����
    sort(dict.begin(), dict.end());
    for (int i = 0; i < N; ++i)
    {
        root.insert(dict[i].second.c_str(), i);
    }
    root.first = -1;

    // Ÿ���� �� ���ϱ�
    tn *node;
    int result;
    for (int i = 0; i < M; ++i)
    {
        cin >> ip;
        node = root.find(ip);
        if (node == NULL || node->terminal == -1)
        {
            result = strlen(ip);
        }
        else
        {
            result = root.type(ip, node->terminal);
        }
        answer += result;
    }

    return answer;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C;
    for (int tcn = 0; tcn < C; ++tcn)
    {
        cin >> N >> M;

        int answer;
        answer = solve();

        cout << answer << '\n';
    }

    return 0;
}