/*
	Kth Smallest Element in a BST
	https://leetcode.com/problems/kth-smallest-element-in-a-bst/

	이진 탐색 트리에서 'k' 번째로 작은 원소를 찾는 문제다.

	이진 탐색 트리에서 좌측 노드는 부모보다 작은 값, 우측 노드는 부모보다 큰 값이 들어간다.
	그래서 중위 순회를 하게 되면, 오름차순으로 정렬된 순서대로 노드를 방문한다.

	노드를 방문할 때, 'int _cnt'를 증가시켜서 노드가 몇 번째 작은 원소를 가졌는지 확인한다.
	만약 '_cnt'가 'k'와 같다면, 현재 노드의 원소가 'k' 번째로 작은 원소다.
*/

class Solution
{
private:
	int _ans;
	int _cnt;
public:
	void inorder(TreeNode* root, int k)
	{
		if (!root)
			return;
		if (_ans != 0)
			return;
		inorder(root->left, k);
		if (k == ++_cnt)
		{
			_ans = root->val;
			return;
		}
		inorder(root->right, k);
	}

	int kthSmallest(TreeNode* root, int k)
	{
		inorder(root, k);
		return _ans;
	}
};