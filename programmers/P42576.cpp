/*
	�������� ���� ����
	https://programmers.co.kr/learn/courses/30/lessons/42576

	-	Ʈ���̳�忡 ������ ������� �Է��ϰ�, ������ �߿��� Ʈ���̳�忡��
		�� ã�� �����ڴ� �������� ���� �������̴�.
	-	���������� ���� �� �ֱ� ������ ������ ������� �Է��� �� �̸��� ������ ���ڶ��
		cnt ���� 1 �������Ѽ� �ش� �̸��� ���� ����� ���� ǥ���ߴ�.
    -   Ʈ���̳�忡�� �����ڵ��� ã�� ��, �ش� �̸��� cnt ���� 1 �̻��� ����
		true�� �����ϰ� �ش� �̸��� cnt�� 1 ���ҽ��״�.
		���� ���� false�� �̸��� �������� ���� �������̱� ������ �ش� �̸��� answer�� �����Ѵ�.
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
			return false; // ���⿡�� �� �� ���� ��
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