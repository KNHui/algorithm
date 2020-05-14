/*
	Implement Trie (Prefix Tree)
	https://leetcode.com/problems/implement-trie-prefix-tree/

	트라이 자료구조를 구현하는 문제다.

	'insert' 명령어는 단어를 트라이에 삽입한다.
	만약, 글자 노드가 'NULL'이라면 'new'를 통해 해당 노드를 동적 할당한다.
	단어의 마지막 노드에서는 'bool _terminal'을 'true'로 만들면서 해당 노드에서 단어가 끝났음을 알린다.

	'search' 명령어는 단어가 트라이에 존재하는지 확인한다.
	단어의 모든 글자 노드가 'NULL'이 아니고, 마지막 노드의 '_terminal'이 'true'면 'true'를 반환한다.

	'startsWith' 명령어는 접두어로 시작하는 단어가 트라이에 있는지 확인한다.
	접두어의 모든 글자 노드가 'NULL'이 아니라면, 'true'를 반환한다.
*/

constexpr int LETTER_LEN = 26;

class Trie
{
private:
	struct TrieNode {
		bool		_terminal;
		TrieNode*	_children[LETTER_LEN];

		TrieNode() :_terminal(false)
		{
			for (int i = 0; i < LETTER_LEN; ++i)
				_children[i] = 0;
		}

		int toNum(char c)
		{
			return c - 'a';
		}

		void insert(const char* key)
		{
			if (*key == NULL)
			{
				_terminal = true;
				return;
			}

			int next = toNum(*key);
			if (_children[next] == NULL)
				_children[next] = new TrieNode();
			_children[next]->insert(key + 1);
		}

		bool search(const char* key)
		{
			if (*key == NULL)
			{
				if (_terminal)
					return true;
				else
					return false;
			}

			int next = toNum(*key);
			if (_children[next] == NULL)
				return false;
			return _children[next]->search(key + 1);
		}

		bool startsWith(const char* key)
		{
			if (*key == NULL)
				return true;

			int next = toNum(*key);
			if (_children[next] == NULL)
				return false;
			return _children[next]->startsWith(key + 1);
		}
	};

	TrieNode* _root;
public:
	Trie() : _root(new TrieNode()) {}

	void insert(string word)
	{
		_root->insert(word.c_str());
	}
	
	bool search(string word)
	{
		return _root->search(word.c_str());
	}

	bool startsWith(string prefix)
	{
		return _root->startsWith(prefix.c_str());
	}
};
