/*
	Construct Binary Search Tree from Preorder Traversal
	https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

	이진 탐색 트리를 전위 순회한 결과물로 동일한 이진 탐색 트리를 만드는 문제다.

	전위 순회 결과물로 주어지는 배열을 순회하면서 노드를 추가한다.
	자식 노드를 추가할 때는 이진 탐색 트리를 만족하도록 탐색하는 과정을 거친다.
	그리고 'null'인 노드가 발견되면, 해당 노드에 배열의 원소를 넣는다.
*/

class Solution
{
public:
	void construct(TreeNode* parent, int value)
	{
		if (parent->val > value)
			if (parent->left)
				construct(parent->left, value);
			else
				parent->left = new TreeNode(value);
		else
			if (parent->right)
				construct(parent->right, value);
			else
				parent->right = new TreeNode(value);
	}

	TreeNode* bstFromPreorder(vector<int>& preorder)
	{
		TreeNode* ret;
		ret = new TreeNode(preorder[0]);

		for (size_t i = 1; i < preorder.size(); ++i)
			construct(ret, preorder[i]);
		return ret;
	}
};