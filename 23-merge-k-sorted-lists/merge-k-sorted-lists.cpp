class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto compare = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(compare)> minHeap(compare);

        for (ListNode* list : lists) {
            if (list != nullptr) {
                minHeap.push(list);
            }
        }

        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (!minHeap.empty()) {
            ListNode* top = minHeap.top();
            minHeap.pop();

            curr->next = top;
            curr = curr->next;

            if (top->next != nullptr) {
                minHeap.push(top->next);
            }
        }

        return dummy.next;
    }
};