/*
	Odd Even Linked List
	https://leetcode.com/problems/odd-even-linked-list/

	홀수 번째 노드와 짝수 번째 노드를 그룹화시켜서 모으는 문제다.
	이때, 상대적 순서는 유지되어야 한다.

	시간 복잡도 O(N), 공간 복잡도 O(1)을 만족시키기 위해 다음과 같은 알고리즘을 사용했다.
	'''
	ListNode* odd : 홀수 번째 노드
	ListNode* even : 짝수 번째 노드
	ListNode* even_start : 첫 짝수 번째 노드
	'''

	1. 'even->next'는 홀수 번째 노드다.
	2. 그래서 'even->next'를 'odd->next'에 넣어 홀수 노드를 모은다.
	3. 이제 'odd->next->next'는 짝수 번째 노드이므로, 'even->next'에 넣는다.
	4. 다음 홀수 번째 노드를 가져오기 위해 'odd->next->next'에 'even_start'를 넣는다. 
	5. 'even'에 'even->next'를, 'odd'에 'odd->next'를 넣어 다음 목표로 넘어간다.
	6. 'even->next->next'와 'odd->next->next'가 'nullptr'이 아니라면 1번으로 돌아간다.
*/

class Solution
{
public:
	ListNode* oddEvenList(ListNode* head)
	{
		if (!head)
			return head;
		if (!head->next)
			return head;
		if (!head->next->next)
			return head;
		ListNode* odd = head;
		ListNode* even = head->next;
		ListNode* even_start = head->next;

		while (odd->next->next && even->next)
		{
			odd->next = even->next;
			if (!even->next->next)
			{
				even->next = NULL;
				odd->next->next = even_start;
				break;
			}
			even->next = odd->next->next;
			odd->next->next = even_start;
			odd = odd->next;
			even = even->next;
		}
		return head;
	}
};