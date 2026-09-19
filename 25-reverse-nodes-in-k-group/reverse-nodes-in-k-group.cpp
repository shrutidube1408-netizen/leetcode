class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr || k == 1) return head;

        ListNode dummy(0, head);
        ListNode* groupPrev = &dummy;

        while (true) {
            // Check if there are at least k nodes remaining
            ListNode* kth = getKthNode(groupPrev, k);
            if (kth == nullptr) break;

            ListNode* groupNext = kth->next;
            ListNode* prev = groupNext;
            ListNode* curr = groupPrev->next;

            // Reverse current group of k nodes
            while (curr != groupNext) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }

            ListNode* newGroupHead = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = newGroupHead;
        }

        return dummy.next;
    }

private:
    ListNode* getKthNode(ListNode* curr, int k) {
        while (curr != nullptr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
    }
};