// 给定一个已排序的链表的头 head ， 删除所有重复的元素，使每个元素只出现一次 。返回 已排序的链表 。
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 我的方法，不是排序的链表也成立
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head != nullptr) {
            ListNode *it = head;
            ListNode *it_n, *it_n_n;
            while (it != NULL) {
                it_n = it;
                while(it_n->next != NULL) {
                    if(it_n->next->val == it->val) {
                        it_n_n = it_n->next;
                        it_n->next = it_n_n->next;
                        delete it_n_n;
                    } else {
                        it_n = it_n->next;
                    }
                }
                it = it->next;
            }
        }
        return head;
    }
};

// 官方解法
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }

        ListNode* cur = head;
        while (cur->next) {
            if (cur->val == cur->next->val) {
                cur->next = cur->next->next;
            }
            else {
                cur = cur->next;
            }
        }

        return head;
    }
};

// 双指针法
// 定义双指针l,r,同时指向head
// 先移动r, 直到r的值和l值不相等, 让l的下一个节点指向r,并将l指向l的下一个节点.
// 最后将l的next置为空,去掉最后多个相同的数.
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head){
            return nullptr;
        }
        ListNode * l=head, *r=head;
        while(r->next){
            r=r->next;
            if(l->val==r->val){
                continue;
            }
            l->next=r;
            l=r;
        }
        l->next=nullptr;
        
        return head;
    }
};
