/*
	Cousins in Binary Tree
	https://leetcode.com/problems/cousins-in-binary-tree/

	이진 트리와 두 값이 주어질 때, 두 값에 해당하는 두 노드의 사촌 여부를 구하는 문제다.

	큐를 이용해 "TreeNode* root"를 너비 우선 탐색을 하면서 두 값의 깊이와 부모를 구했다.
	그리고 두 값이 같은지, 부모가 다른지 비교하여 사촌인지 확인했다.
*/
class Solution
{
public:

	bool isCousins(TreeNode* root, int x, int y)
	{
		if (!root)
			return false;
		int						xDepth, xParent;
		int						yDepth, yParent;
		queue<TreeNode*>		tq;
		queue<pair<int, int> >	dpq;

		tq.push(root);
		dpq.push({ 0,  root->val});
		while (!tq.empty())
		{
			TreeNode*	cur = tq.front();
			int			depth = dpq.front().first;
			int			parent = dpq.front().second;
			tq.pop();
			dpq.pop();

			if (!cur)
				continue;
			if (cur->val == x)
			{
				xDepth = depth;
				xParent = parent;
			}
			if (cur->val == y)
			{
				yDepth = depth;
				yParent = parent;
			}
			tq.push(cur->left);
			dpq.push({ depth + 1, cur->val });
			tq.push(cur->right);
			dpq.push({ depth + 1, cur->val });
		}
		return xDepth == yDepth && xParent != yParent;
	}
};