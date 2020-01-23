/*
	안녕히, 그리고 물고기는 고마웠어요!
	https://www.algospot.com/judge/problem/read/SOLONG#

	트라이 알고리즘을 사용하여, 사전에 저장된 단어들을 저장하고, 입력해야 하는 횟수를 구한다.

	사전에 저장된 단어들을 입력받고 나서, 출현 빈도 내림차순으로 정렬하고, 출현 빈도가 같다면 사전 순으로 정렬한다.
	정렬 후에 트라이에 단어들을 삽입하는데,
	각 노드의 first에는 해당 노드에서 탭 키를 누르면 완성되는 단어의 인덱스가 들어가고,
	terminal에는 해당 노드에서 끝난 단어의 인덱스가 들어간다.

	타이핑해야 하는 문자열의 각 단어가 트라이에 없다면 단어의 길이를 answer에 더하고,
	트라이에 있다면, type 함수를 사용하여 최소 타이핑 수를 구한다.
	type 함수에서는 현재 노드에서 first의 인덱스가 자신의 인덱스라면
	탭 키를 누르면 자동완성이 되므로, 1을 리턴한다
	그렇지 않다면 다음 문자의 노드로 넘어가면서 문자 하나를 타이핑해야 하므로 결괏값에 1을 더해준다.
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

    // 해당 노드에서 idx의 단어를 치기위해 몇 번 더 타이핑 해야하는가
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

    answer = M - 1; // 스페이스바
    for (int i = 0; i < N; ++i)
    {
        cin >> ip >> weight;
        dict.push_back(make_pair(-weight, ip));
    }

    // 정렬 후 트라이 생성
    sort(dict.begin(), dict.end());
    for (int i = 0; i < N; ++i)
    {
        root.insert(dict[i].second.c_str(), i);
    }
    root.first = -1;

    // 타이핑 수 구하기
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